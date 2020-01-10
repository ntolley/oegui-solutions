#include "matlabFilter.h"
#include "matlabFilterEditor.h"
#include <chrono>
#include <thread>

matlabFilter::matlabFilter() : GenericProcessor("Matlab Filter")
{
	setProcessorType(PROCESSOR_TYPE_FILTER);
	setEnabledState(false);

	StringArray extensions = getSupportedExtensions();

	const int numExtensions = extensions.size();
	for (int j = 0; j < numExtensions; ++j)
	{
		supportedExtensions.set(extensions[j].toLowerCase(), j+1);
	}

	fileString = "D:\\Github\\oegui-solutions\\matlab_filter_plugin\\matlab_filter\\Source\\matlabFilter_init.txt";

	// Matlab Engine Initialization
	Engine *ep;
	ep = engOpen("");

	//Initialization script only run during construction
	std::ifstream initFile{fileString.toStdString()}; //reads .txt into string variable
	initString = { std::istreambuf_iterator<char>(initFile), std::istreambuf_iterator<char>() };
	initChar = initString.c_str(); //must convert to const char array for matlab engine


	//Function Script to run on every loop when process() is called
	std::ifstream funcFile{ "D:\\Github\\oegui-solutions\\matlab_filter_plugin\\matlab_filter\\Source\\matlabFilter_func.m" }; //reads .txt into string variable
	funcString = { std::istreambuf_iterator<char>(funcFile), std::istreambuf_iterator<char>() };
	funcChar = funcString.c_str(); //must convert to const char array for matlab engine

}

matlabFilter::~matlabFilter()
{
	engEvalString(ep, "close all");

}

AudioProcessorEditor* matlabFilter::createEditor()
{
	editor = new matlabFilterEditor(this, true);

	return editor;
}


bool matlabFilter::isReady()
{

	if (isFileSupported(fileString))
	{		
		return true;
	}
	else
	{
		CoreServices::sendStatusMessage("No file selected in File Reader.");
		return false;
	}
}

void matlabFilter::setEnabledState(bool t)
{
	isEnabled = t;
}

String matlabFilter::getFile() const
{
	File file(fileString);
	return file.getFileName();
}

bool matlabFilter::setFile(String fullpath)
{
	File file(fullpath);
	fileString = fullpath;

	std::ifstream initFile{ fileString.toStdString() }; //reads .txt into string variable
	initString = { std::istreambuf_iterator<char>(initFile), std::istreambuf_iterator<char>() };
	initChar = initString.c_str(); //must convert to const char array for matlab engine

	count = 1; //Reset loop count


	String ext = file.getFileExtension().toLowerCase().substring(1);
	const int index = supportedExtensions[ext] - 1;
	const bool isExtensionSupported = index >= 0;

	if (isExtensionSupported)
	{
		return true;

	}
	else
	{
		CoreServices::sendStatusMessage("File type not supported");
		return false;
	}


	return true;
}

bool matlabFilter::isFileSupported(const String& fileName) const
{
	const File file(fileName);
	String ext = file.getFileExtension().toLowerCase().substring(1);

	return isFileExtensionSupported(ext);
}


bool matlabFilter::isFileExtensionSupported(const String& ext) const
{
	const int index = supportedExtensions[ext] - 1;
	const bool isExtensionSupported = index >= 0;

	return isExtensionSupported;
}

StringArray matlabFilter::getSupportedExtensions() const
{
	StringArray extensions;
	extensions.add(String("txt"));
	extensions.add(String("m"));

	return extensions;
	


}


void matlabFilter::process(AudioSampleBuffer& buffer)
{
	// Load data for buffer
	//int numChannels = getNumOutputs();
	int numChannels = 96; //Specific to Blackrock NSP

	int nSamples = getNumSamples(0); //this returns the actual number off samples in the buffer which can change every loop
	//Using buffer.getNumSamples() just returns the size of the buffer

	//Start matlab engine and read .txt file containing matlab commands on first call to process
	if (count == 1) {

		ep = engOpen("");
		engEvalString(ep, initChar); //reads matlab script from .txt file

		//Create mxArrays that will be passed to matlab engine
		mxArray *nC;
		nC = mxCreateDoubleScalar(numChannels);
		engPutVariable(ep, "numChannels", nC);
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
	mxArray *T, *nS;

	T = mxCreateDoubleMatrix(1, numChannels*nSamples, mxREAL);
	nS = mxCreateDoubleScalar(nSamples);

	//Write buffer data to mxArray
	double* ptr = mxGetPr(T);
	memcpy((void*)ptr, (void*)allBuf, nSamples*numChannels * sizeof(double));

	//Send array to matlab workspace
	engPutVariable(ep, "nSamples", nS);
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
	mxDestroyArray(nS);
	mxDestroyArray(resVar);

	delete[] allBuf;
	delete[] resBuf;
	delete[] doubleChanBuf;
	delete[] floatChanBuf;
	delete[] floatResBufChan;
	delete[] doubleResBufChan;

}
