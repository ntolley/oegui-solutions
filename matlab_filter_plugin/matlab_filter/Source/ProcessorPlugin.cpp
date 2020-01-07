#include "ProcessorPlugin.h"
#include <chrono>
#include <thread>

using namespace ProcessorPluginSpace;



ProcessorPlugin::ProcessorPlugin() : GenericProcessor("Processor Name")
{
	Engine *ep;
	ep = engOpen("");

	//Initialization script only run during construction
	std::ifstream initFile{ "D:\\Borton Lab\\cpp_mat_func\\matlabFilter_init.txt" }; //reads .txt into string variable
	initString = { std::istreambuf_iterator<char>(initFile), std::istreambuf_iterator<char>() };
	initChar = initString.c_str(); //must convert to const char array for matlab engine


	//Function Script to run on every loop when process() is called
	std::ifstream funcFile{ "D:\\Borton Lab\\cpp_mat_func\\matlabPlugin.txt" }; //reads .txt into string variable
	funcString = { std::istreambuf_iterator<char>(funcFile), std::istreambuf_iterator<char>() };
	funcChar = funcString.c_str(); //must convert to const char array for matlab engine





}

ProcessorPlugin::~ProcessorPlugin()
{
	engEvalString(ep, "close all");

}

void ProcessorPlugin::process(AudioSampleBuffer& buffer)
{
	// Load data for buffer
	int numChannels = getNumOutputs();
	//int numChannels = 10;

	int nSamples = buffer.getNumSamples();

	//Start matlab engine and read .txt file containing matlab commands on first call to process
	if (count == 1) {

		ep = engOpen("");
		engEvalString(ep, funcChar); //reads matlab script from .txt file


		//engEvalString(ep, "decode_param = rand(98,1);");
		//engEvalString(ep, "load('D:\Borton Lab\Blackrock\open_ephys_decoding\decode_param.mat')");
		//engEvalString(ep, "figure");
		//engEvalString(ep, "hold on");
		//engEvalString(ep, "xlim([0 100000]");
		//engEvalString(ep, "b = [];");

		//Create mxArrays that will be passed to matlab engine
		mxArray *nS, *nC;
		nS = mxCreateDoubleScalar(nSamples);
		nC = mxCreateDoubleScalar(numChannels);
		engPutVariable(ep, "nSamples", nS);
		engPutVariable(ep, "numChannels", nC);
		mxDestroyArray(nS);
		mxDestroyArray(nC);

		count = count + 1;

	}



	//Dynamic arrays, flattens individual channels (chanBuf) in one long array
	double* allBuf = new double[nSamples*numChannels]; //all channel data from unaltered buffer stored here
	double* resBuf = new double[nSamples*numChannels]; //all matlab processed data stored here
	float* floatChanBuf = new float[nSamples]; //open ephys stores data as floats, loads single channel float data here
	double* doubleChanBuf = new double[nSamples]; //single channel data stores here after converting from float to double


	//Iterate over every channel 
	for (int chan = 0; chan < numChannels; chan++) {
		const float* reBufPtr = buffer.getReadPointer(chan);
		memcpy((void *)floatChanBuf, (void *)reBufPtr, nSamples * sizeof(float));
		std::copy(floatChanBuf, floatChanBuf + nSamples, doubleChanBuf); //Implicitly converts float to double

		//Places single channel in one long array
		memcpy((void *)(allBuf + (chan*nSamples)), (void *)doubleChanBuf, nSamples * sizeof(double));

	}

	//Create mxArrays that will be passed to matlab engine
	mxArray *T;

	T = mxCreateDoubleMatrix(1, numChannels*nSamples, mxREAL);

	//Write buffer data to mxArray
	double* ptr = mxGetPr(T);
	memcpy((void*)ptr, (void*)allBuf, nSamples*numChannels * sizeof(double));

	//Send array to matlab workspace
	engPutVariable(ep, "T", T);




	//*** Do not change ***
	engEvalString(ep, "T_original = T;");
	engEvalString(ep, "T = reshape(T,[nSamples,numChannels])';");
	engEvalString(ep, "X = T';");
	//**********************

	//<---Add script here--->

	engEvalString(ep, funcChar); //reads matlab script from .txt file


	//<------------------------>

	//*** Do not change ****
	engEvalString(ep, "R = X(:)';");
	//***********************





	//Get array back from matlab and write to resBuf
	mxArray *resVar;
	resVar = engGetVariable(ep, "R");
	double* resPtr = mxGetPr(resVar);
	memcpy((void *)resBuf, (void *)resPtr, numChannels*nSamples * sizeof(double));

	//Single channel output data stored here to write back into buffer
	float* floatResBufChan = new float[nSamples];
	double* doubleResBufChan = new double[nSamples];

	//Write result to buffer
	for (int chan = 0; chan < numChannels; chan++) {
		float* bufPtr = buffer.getWritePointer(chan);

		memcpy((void *)doubleResBufChan, (void *)(resBuf + (chan*nSamples)), nSamples * sizeof(double));
		std::copy(doubleResBufChan, doubleResBufChan + nSamples, floatResBufChan);

		memcpy((void *)bufPtr, (void *)floatResBufChan, nSamples * sizeof(float));


	}

	//clear memory
	mxDestroyArray(T);
	mxDestroyArray(resVar);


	delete[] allBuf;
	delete[] resBuf;
	delete[] doubleChanBuf;
	delete[] floatChanBuf;
	delete[] floatResBufChan;
	delete[] doubleResBufChan;

}
