#include "Blackrock.h"
#include <string>

typedef enum _blackrockErrors
{
	NUMCHANNELMISMATCH
} blackrockErrors;

CBlackrock::CBlackrock(void)
	: m_blkrckInstance(0)
	, m_sizeBufferMarco(20)
	, m_spikeBufferSize(100)
	, m_neuronalSampleRate(30000)
	, m_numEmgChannels(1)
{
}


CBlackrock::~CBlackrock(void)
{
}

void CBlackrock::setup_connection_blackrock()
{
	cbSdkResult resTest2;

	// GET VERSION
	cbSdkVersion ver;
	cbSdkResult res = cbSdkGetVersion(m_blkrckInstance, &ver);

	//// OPEN CONNECTION
	cbSdkConnection con = cbSdkConnection();
	cbSdkConnectionType conType = CBSDKCONNECTION_DEFAULT;
	// cbSdkInstrumentType instType;
	//resTest2 = cbSdkOpen(m_blkrckInstance, conType, con);

	//// GET TIME
	UINT32 cbtime = 0;
	//resTest2 = cbSdkGetTime(m_blkrckInstance, &cbtime);

	//// CHANNEL INFO
	//UINT16 channel = 129;
	//cbPKT_CHANINFO chaninfo;
	//resTest2 = cbSdkGetChannelConfig(m_blkrckInstance, channel, &chaninfo);

	//// CHECK and STORE NAMES OF CHANNEL BEING READ
	//char label[cbNUM_ANALOG_CHANS][cbLEN_STR_LABEL];
	//for (int i = 0; i < cbNUM_ANALOG_CHANS; i++)
	//{
	//	UINT16 channelSDK = i + 1;
	//	resTest2 = cbSdkGetChannelLabel(m_blkrckInstance, channelSDK, NULL, label[i]); // Get channel label
	//}

	//// SET CONFIG SETUP 
	//UINT16 uBegChan = 1;
	//UINT32 uBegMask = 0;
	//UINT32 uBegVal = 0;
	//UINT16 uEndChan = 10;
	//UINT32 uEndMask = 0;
	//UINT32 uEndVal = 0;
	//bool   bDouble = false;
	//bool   bAbsolute = false;
	//UINT32 uWaveforms = 0;
	//UINT32 uConts = cbSdk_CONTINUOUS_DATA_SAMPLES;
	//UINT32 uEvents = 0;
	//UINT32 uComments = 0;
	//UINT32 uTrackings = 0;
	//UINT32 bWithinTrial = false;

	//resTest2 = cbSdkGetTrialConfig(m_blkrckInstance
	//	, &bWithinTrial
	//	, &uBegChan
	//	, &uBegMask
	//	, &uBegVal
	//	, &uEndChan
	//	, &uEndMask
	//	, &uEndVal
	//	, &bDouble
	//	, &uWaveforms
	//	, &uConts
	//	, &uEvents
	//	, &uComments
	//	, &uTrackings);

	//uEvents = 0;
	//UINT32 bActive = 0; // 0 leave buffer intact, 1 clear the buffer
	//uBegChan = 0;
	//uEndChan = 0;
	//uBegVal = 0;
	//uBegMask = 0;
	//uEndMask = 0;
	//uEndVal = 0;
	//resTest2 = cbSdkSetTrialConfig(m_blkrckInstance
	//	, bActive
	//	, uBegChan
	//	, uBegMask
	//	, uBegVal
	//	, uEndChan
	//	, uEndMask
	//	, uEndVal
	//	, bDouble
	//	, uWaveforms
	//	, uConts
	//	, uEvents
	//	, uComments
	//	, uTrackings
	//	, bAbsolute); // Configure a data collection trial
	//if (resTest2 != CBSDKRESULT_SUCCESS)
	//{
	//	bool debug2 = true;
	//}

	//UINT32 bActive2 = 0; //activate channel 1, deactivating 0

	////DEACTIVATING THE NEURAL DATA
	//int nchan = 96;
	//UINT16 dchannel = 0;
	//for(int i=1; i<=nchan; i++)
	//{  //i must start from 1 because dchannel =0, bactive= 0 means deactivate everything
	//	dchannel = i;
	//	resTest2 = cbSdkSetChannelMask(m_blkrckInstance, dchannel, bActive2);
	//}
}
//
//int CBlackrock::connection_init_EMG() // BLACKROCK
//{
//	cbSdkResult resTest2;
//
//	resTest2 = cbSdkClose(m_blkrckInstance); //ADDED FOR DEBUGGING
//	// GET VERSION
//	cbSdkVersion ver;
//	cbSdkResult res = cbSdkGetVersion(m_blkrckInstance, &ver);
//
//
//	// OPEN CONNECTION
//	cbSdkConnection con = cbSdkConnection();
//	cbSdkConnectionType conType = CBSDKCONNECTION_DEFAULT;
//	// cbSdkInstrumentType instType;
//	resTest2 = cbSdkOpen(m_blkrckInstance, conType, con);
//
//
//	// GET TIME
//	UINT32 cbtime = 0;
//	resTest2 = cbSdkGetTime(m_blkrckInstance, &cbtime);
//
//
//	// CHANNEL INFO
//	UINT16 channel = 128;
//	cbPKT_CHANINFO chaninfo;
//	resTest2 = cbSdkGetChannelConfig(m_blkrckInstance, channel, &chaninfo);
//
//
//	// CHECK and STORE NAMES OF CHANNEL BEING READ
//	char label[cbNUM_ANALOG_CHANS][cbLEN_STR_LABEL];
//	for (int i = 0; i < cbNUM_ANALOG_CHANS; i++)
//	{
//		UINT16 channelSDK = i + 1;
//		resTest2 = cbSdkGetChannelLabel(m_blkrckInstance, channelSDK, NULL, label[i]); // Get channel label
//	}
//
//
//	// SET CONFIG SETUP 
//	UINT16 uBegChan = 1;
//	UINT32 uBegMask = 0;
//	UINT32 uBegVal = 0;
//	UINT16 uEndChan = 10;
//	UINT32 uEndMask = 0;
//	UINT32 uEndVal = 0;
//	bool   bDouble = false;
//	bool   bAbsolute = false;
//	UINT32 uWaveforms = 0;
//	UINT32 uConts = cbSdk_CONTINUOUS_DATA_SAMPLES;
//	UINT32 uEvents = 0;
//	UINT32 uComments = 0;
//	UINT32 uTrackings = 0;
//	UINT32 bWithinTrial = false;
//
//	resTest2 = cbSdkGetTrialConfig(m_blkrckInstance
//		, &bWithinTrial
//		, &uBegChan
//		, &uBegMask
//		, &uBegVal
//		, &uEndChan
//		, &uEndMask
//		, &uEndVal
//		, &bDouble
//		, &uWaveforms
//		, &uConts
//		, &uEvents
//		, &uComments
//		, &uTrackings);
//
//
//	uEvents = 0;
//	UINT32 bActive = 1; // 0 leave buffer intact, 1 clear the buffer
//	uBegChan = 0;
//	uEndChan = 0;
//	uBegVal = 0;
//	uBegMask = 0;
//	uEndMask = 0;
//	uEndVal = 0;
//	resTest2 = cbSdkSetTrialConfig(m_blkrckInstance
//		, bActive
//		, uBegChan
//		, uBegMask
//		, uBegVal
//		, uEndChan
//		, uEndMask
//		, uEndVal
//		, bDouble
//		, uWaveforms
//		, uConts
//		, uEvents
//		, uComments
//		, uTrackings
//		, bAbsolute);
//	if (resTest2 != CBSDKRESULT_SUCCESS)
//	{
//		bool debug2 = true;
//	}
//
//	// SEND COMMENT
//	UINT32 rgba = 128;
//	UINT8 charset = 1;
//	std::string commentMessage = "ciccio";
//	for (int i = 0; i < 1; i++)
//	{
//		//resTest2 = cbSdkSetComment( nInstance, 8912896, charset, commentMessage.c_str());
//		resTest2 = cbSdkSetComment(m_blkrckInstance, 50000, charset, commentMessage.c_str());
//	}
//
//
//	// 1 - Get how many samples are waiting
//	UINT32 bActive2 = 0; //activate channel 1, deactivating 0
//
//	//DEACTIVATING THE NEURAL DATA
//	//resTest2 = cbSdkSetChannelMask( nInstance, 0,1 );	
//
//	int nchan = 127; //96
//	UINT16 dchannel = 0;
//	for (int i = 1; i <= nchan; i++)  //i must start from 1 because dchannel =0, bactive= 0 means deactivate everything
//	{
//		dchannel = i;
//		resTest2 = cbSdkSetChannelMask(m_blkrckInstance, dchannel, bActive2);
//	}
//
//
//	//cbSdkTrialEvent trialevent;
//	resTest2 = cbSdkInitTrialData(m_blkrckInstance, NULL, NULL, &m_trialCont, NULL, NULL);
//
//
//	// BUFFER FOR FASTER UPDATING
//	for (int chio = 0; chio < m_trialCont.count; chio++)
//	{
//		m_trialCont.num_samples[chio] = m_sizeBufferMarco;
//	}
//
//	bool bTrialDouble = false;
//	resTest2 = cbSdkGetTrialConfig(m_blkrckInstance, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &bTrialDouble);
//
//
//	// ALLOCATE MEMORY
//	int ch = 0;
//	double* pi = NULL;
//
//	if (bTrialDouble)
//	{
//		for (ch = 0; ch < m_trialCont.count; ch++)
//		{
//			// m_trialCont.samples[ch] = NULL;
//			// m_trialCont.samples[ch] = (double *)malloc(sizeof(double)*m_trialCont.num_samples[ch]);
//			m_trialCont.samples[ch] = new double[m_trialCont.num_samples[ch]];
//		}
//	}
//	else
//	{
//		for (ch = 0; ch < m_trialCont.count; ch++)
//		{
//			// m_trialCont.samples[ch]=NULL;
//			// m_trialCont.samples[ch]=(INT16 *)malloc(sizeof(INT16)*m_trialCont.num_samples[ch]);
//			m_trialCont.samples[ch] = new INT16[m_trialCont.num_samples[ch]];
//		}
//	}
//
//	return 0;
//}
//
//// mask_start and mask_stop is the 2 variables that set the channels to be activated
//int CBlackrock::connection_init_neural() // BLACKROCK
//{
//	// UINT32 nInstance = 0;
//	cbSdkResult resTest2;
//	resTest2 = cbSdkClose(m_blkrckInstance);
//
//	// GET VERSION
//	cbSdkVersion ver;
//	cbSdkResult res = cbSdkGetVersion(m_blkrckInstance, &ver);
//
//	// OPEN CONNECTION
//	cbSdkConnection con = cbSdkConnection();
//	cbSdkConnectionType conType = CBSDKCONNECTION_DEFAULT;
//	// cbSdkInstrumentType instType;
//	resTest2 = cbSdkOpen(m_blkrckInstance, conType, con);
//
//	// GET TIME
//	UINT32 cbtime = 0;
//	resTest2 = cbSdkGetTime(m_blkrckInstance, &cbtime);
//
//	// CHANNEL INFO
//	UINT16 channel = 1;
//	cbPKT_CHANINFO chaninfo;
//	resTest2 = cbSdkGetChannelConfig(m_blkrckInstance, channel, &chaninfo);
//
//	// CHECK and STORE NAMES OF CHANNEL BEING READ
//	char label[cbNUM_ANALOG_CHANS][cbLEN_STR_LABEL];
//	for (int i = 0; i < cbNUM_ANALOG_CHANS; i++)
//	{
//		UINT16 channelSDK = i + 1;
//		resTest2 = cbSdkGetChannelLabel(m_blkrckInstance, channelSDK, NULL, label[i]); // Get channel label
//	}
//
//
//	// SET CONFIG SETUP 
//	UINT16 uBegChan = 1;
//	UINT32 uBegMask = 0;
//	UINT32 uBegVal = 0;
//	UINT16 uEndChan = 128;
//	UINT32 uEndMask = 0;
//	UINT32 uEndVal = 0;
//	bool   bDouble = false;
//	bool   bAbsolute = false;
//	UINT32 uWaveforms = 0;
//	UINT32 uConts = 0;
//	UINT32 uEvents = 0;
//	UINT32 uComments = 0;
//	UINT32 uTrackings = 0;
//	UINT32 bWithinTrial = false;
//
//	resTest2 = cbSdkGetTrialConfig(m_blkrckInstance
//		, &bWithinTrial
//		, &uBegChan
//		, &uBegMask
//		, &uBegVal
//		, &uEndChan
//		, &uEndMask
//		, &uEndVal
//		, &bDouble
//		, &uWaveforms
//		, &uConts
//		, &uEvents
//		, &uComments
//		, &uTrackings);
//
//	uConts = 0;
//	UINT32 bActive = 1; // 0 leave buffer intact, 1 clear the buffer
//	uBegChan = 0;
//	uEndChan = 0;
//	uBegVal = 0;
//	uBegMask = 0;
//	uEndMask = 0;
//	uEndVal = 0;
//	resTest2 = cbSdkSetTrialConfig(m_blkrckInstance
//		, bActive
//		, uBegChan
//		, uBegMask
//		, uBegVal
//		, uEndChan
//		, uEndMask
//		, uEndVal
//		, bDouble
//		, uWaveforms
//		, uConts
//		, uEvents
//		, uComments
//		, uTrackings
//		, bAbsolute); // Configure a data collection trial
//
//	if (resTest2 != CBSDKRESULT_SUCCESS)
//	{
//		bool debug2 = true;
//	}
//
//	// SEND COMMENT
//	UINT32 rgba = 128;
//	UINT8 charset = 1;
//	std::string commentMessage = "start Neu";
//	//resTest2 = cbSdkSetComment( nInstance, 8912896, charset, commentMessage.c_str());
//	//resTest2 = cbSdkSetComment(m_blkrckInstance, 50000, charset, commentMessage.c_str());
//
//	//DEACTIVATING ALL THE CHANNELS
//	UINT32 bActive2 = 0; //activate channel 1, deactivating 0
//	UINT16 dchannel = 0;
//	resTest2 = cbSdkSetChannelMask(m_blkrckInstance, dchannel, bActive2);
//
//	//ACTIVATING ONLY THE CHANNELS TO BE USED
//	bActive2 = 1; //activate channel: 1, deactivating 0
//	dchannel = 0;
//	size_t noOfNeuronalCh = 96;
//	for (size_t ch = 1; ch <= noOfNeuronalCh; ch++)  //i must start from 1 because dchannel =0, bactive= 0 means deactivate everything
//	{
//		dchannel = ch;
//		resTest2 = cbSdkSetChannelMask(m_blkrckInstance, dchannel, bActive2);
//	}
//
//	//INITIALIZE DATA STRUCTURES
//	resTest2 = cbSdkInitTrialData(m_blkrckInstance, NULL, &m_trialEvent, NULL, NULL, NULL);
//
//	bool bTrialDouble = false;
//	resTest2 = cbSdkGetTrialConfig(m_blkrckInstance, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &bTrialDouble);
//
//	//ALLOCATE MEMORY
//	for (UINT32 channel = 0; channel < cbNUM_ANALOG_CHANS + 2; channel++)
//	{
//		// Fill timestamps for non-empty channels
//		for (UINT u = 0; u <= cbMAXUNITS + 1; u++)
//		{
//			m_trialEvent.timestamps[channel][u] = NULL;
//		}
//
//		m_trialEvent.waveforms[channel] = NULL;
//	}
//
//	return 0;
//}
//
//
//void CBlackrock::connection_end()
//{
//
//	// SEND COMMENT
//	cbSdkResult resTest2;
//	UINT32 rgba = 128;
//	UINT8 charset = 1;
//	std::string commentMessage = "STOP";
//	for (int i = 0; i < 1; i++)
//	{
//		//resTest2 = cbSdkSetComment( nInstance, 8912896, charset ,pippo);
//		resTest2 = cbSdkSetComment(m_blkrckInstance, 128, charset, commentMessage.c_str());
//	}
//	resTest2 = cbSdkClose(m_blkrckInstance);
//}
//
//
//
////Function to get both analog and spike data from NSP
//void CBlackrock::get_data(std::vector<int> neuralChannels,
//	//int firstAnalogChan,
//	std::vector<int> analogChannels,
//	INT16** contData)
//	//double*** spikeTimes,
//	//double** spikeWaveforms)
//{
//
//	cbSdkResult resp;
//
//	//// Initiate trial (see now many samples are available)
//	//resp = cbSdkInitTrialData(m_blkrckInstance, &m_trialEvent, &m_trialCont, NULL, NULL);
//
//	//// See if double or not
//	//bool bTrialDouble = false;
//	//resp = cbSdkGetTrialConfig(m_blkrckInstance, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &bTrialDouble);
//
//	//// ALLOCATE MEMORY
//	//// First the analog data
//	//int ch = 0;
//	//if(bTrialDouble)
//	//{
//	//	for(ch=0; ch<m_trialCont.count; ch++)
//	//	{
//	//		m_trialCont.samples[ch] = new double[m_trialCont.num_samples[ch]];
//	//	}
//	//}
//	//else
//	//{
//	//	for(ch=0; ch<m_trialCont.count; ch++)
//	//	{
//	//		m_trialCont.samples[ch] = new INT16[m_trialCont.num_samples[ch]];
//	//	}
//	//}
//
//	//// Then allocate for spikes
//	//for (UINT32 channel = 0; channel < m_trialEvent.count; channel++)
//	//{
//	//	UINT16 ch = m_trialEvent.chan[channel]; // Actual channel number
//	//	
//	//	// Fill timestamps for non-empty channels
//	//	UINT32 total_samples = 0; // the total number of spikes found for all units (in a single channel)
//	//	for (UINT u = 0; u <= cbMAXUNITS; u++)
//	//	{
//	//		// m_trialEvent.timestamps[channel][u] = NULL;
//	//		UINT32 num_samples = m_trialEvent.num_samples[channel][u];
//	//		total_samples += num_samples;
//	//		if (num_samples > 0)
//	//		{
//	//			if (bTrialDouble)
//	//			{
//	//				m_trialEvent.timestamps[channel][u] = new double[m_trialEvent.num_samples[channel][u]];
//	//			}
//	//			else
//	//			{
//	//				m_trialEvent.timestamps[channel][u] = new UINT32[m_trialEvent.num_samples[channel][u]];
//	//			}
//	//		}
//	//	}
//
//	//	// Allocate memory for waveforms (all units are combined?)
//	//	m_trialEvent.waveforms[channel] = new double[total_samples];
//
//
//	//	// Fill values for non-empty digital or serial channels (why no timestamp allocation?)
//	//	if (ch == MAX_CHANS_DIGITAL_IN || ch == MAX_CHANS_SERIAL)
//	//	{
//	//		UINT32 num_samples = m_trialEvent.num_samples[channel][0];
//	//		if (num_samples > 0)
//	//		{
//	//			if (bTrialDouble)
//	//			{
//	//				m_trialEvent.waveforms[channel] = new double[m_trialEvent.num_samples[channel][0]];
//	//			}
//	//			else
//	//			{
//	//				m_trialEvent.waveforms[channel] = new UINT16[m_trialEvent.num_samples[channel][0]];
//	//			}
//	//		}
//	//	}
//	//}
//
//
//	//// GET DATA
//	//bool bFlushBuffer = true;
//	//resp = cbSdkGetTrialData(m_blkrckInstance, bFlushBuffer, &m_trialEvent, &m_trialCont, NULL, NULL);
//
//
//	//// Copy data to outputs
//	//
//	//if (m_trialCont.count < (neuralChannels.size()+analogChannels.size()))
//	//{
//	//	throw(NUMCHANNELMISMATCH);
//	//}
//
//	//// first raw neural data
//	//if (bTrialDouble)
//	//{
//	//	for (size_t chan = 0; chan < neuralChannels.size(); chan++)
//	//	{
//	//		INT16* neuralData = (INT16 *)m_trialCont.samples[chan];
//	//		for (size_t j = 0; j < m_trialCont.num_samples[0]; j++)
//	//		{
//	//			contData[neuralChannels[chan]][j] = neuralData[j];
//	//		}
//	//	}
//	//}
//	//else
//	//{
//	//	for (size_t chan = 0; chan < neuralChannels.size(); chan++)
//	//	{
//	//		double* neuralData = (double *)m_trialCont.samples[chan];
//	//		for (size_t j = 0; j < m_trialCont.num_samples[0]; j++)
//	//		{
//	//			contData[neuralChannels[chan]][j] = neuralData[j];
//	//		}
//	//	}
//	//}
//
//	//// next get analog data
//	//if (bTrialDouble)
//	//{
//	//	for (size_t chan = 0; chan < analogChannels.size(); chan++)
//	//	{
//	//		INT16* neuralData = (INT16 *)m_trialCont.samples[chan+firstAnalogChan];
//	//		for (size_t j = 0; j < m_trialCont.num_samples[0]; j++)
//	//		{
//	//			contData[analogChannels[chan]][j] = neuralData[j];
//	//		}
//	//	}
//	//}
//	//else
//	//{
//	//	for (size_t chan = 0; chan < analogChannels.size(); chan++)
//	//	{
//	//		double* neuralData = (double *)m_trialCont.samples[chan + firstAnalogChan];
//	//		for (size_t j = 0; j < m_trialCont.num_samples[0]; j++)
//	//		{
//	//			contData[analogChannels[chan]][j] = neuralData[j];
//	//		}
//	//	}
//	//}
//
//	////next get spikes
//	//if (m_trialEvent.count < neuralChannels.size())
//	//{
//	//	throw(NUMCHANNELMISMATCH);
//	//}
//
//	//for (UINT32 channel = 0; channel < neuralChannels.size(); channel++)
//	//{
//	//	UINT16 ch = m_trialEvent.chan[channel]; // Actual channel number
//	//	
//	//	// Fill timestamps for non-empty channels
//	//	UINT32 total_samples = 0;
//	//	for (UINT u = 0; u <= cbMAXUNITS; u++)
//	//	{
//	//		UINT32 num_samples = m_trialEvent.num_samples[channel][u];
//	//		if (num_samples > 0)
//	//		{
//	//			if (bTrialDouble)
//	//			{
//	//				memcpy(spikeTimes[neuralChannels[ch]][u], m_trialEvent.timestamps[channel][u], num_samples * sizeof(double));
//	//			}
//	//			else
//	//			{
//	//				memcpy(spikeTimes[neuralChannels[ch]][u], m_trialEvent.timestamps[channel][u], num_samples * sizeof(UINT32));
//	//			}
//	//		}
//	//	}
//
//	//	//add waveforms
//	//	int nWaveformPoints= 0; // need to find out what this number is!
//	//	memcpy(spikeWaveforms[neuralChannels[ch]], m_trialEvent.waveforms[channel], total_samples * nWaveformPoints* sizeof(double));
//
//	//}
//
//}
//
//
////Function to get EMG raw data
//void CBlackrock::get_EMG(const int CHANNEL2USE_m1
//	, const int CHANNEL2USE_m2
//	, const int* const CHANNELS2USE
//	, INT16* Signal_m1
//	, INT16* Signal_m2
//	, INT16** Signals)
//{
//
//	cbSdkResult resTest2;
//	// INIT TRIAL (EVERY TIME)
//	resTest2 = cbSdkInitTrialData(m_blkrckInstance, NULL, NULL, &m_trialCont, NULL, NULL);
//
//	// BUFFER FOR FASTER UPDATING - smaller size (20 samples)
//	for (int chio = 0; chio < m_trialCont.count; chio++)
//	{
//		m_trialCont.num_samples[chio] = m_sizeBufferMarco;
//	}
//
//	// GET CONFIG
//	bool bTrialDouble = false;
//	resTest2 = cbSdkGetTrialConfig(m_blkrckInstance, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &bTrialDouble);
//
//
//	// ALLOCATE MEMORY
//	int ch = 0;
//	double* pi = NULL;
//
//	if (bTrialDouble)
//	{
//		for (ch = 0; ch < m_trialCont.count; ch++)
//		{
//			// m_trialCont.samples[ch] = NULL;
//			// m_trialCont.samples[ch] = (double *)malloc(sizeof(double)*m_trialCont.num_samples[ch]);
//			m_trialCont.samples[ch] = new double[m_trialCont.num_samples[ch]];
//		}
//	}
//	else
//	{
//		for (ch = 0; ch < m_trialCont.count; ch++)
//		{
//			// m_trialCont.samples[ch]=NULL;
//			// m_trialCont.samples[ch]=(INT16 *)malloc(sizeof(INT16)*m_trialCont.num_samples[ch]);
//			m_trialCont.samples[ch] = new INT16[m_trialCont.num_samples[ch]];
//		}
//	}
//
//	// GET DATA
//	bool bFlushBuffer = true;
//	UINT16 activeChannels = -1;
//	UINT32 num_samples = -1;
//	UINT32 time_rec = -1;
//	resTest2 = cbSdkGetTrialData(m_blkrckInstance, bFlushBuffer, NULL, &m_trialCont, NULL, NULL);
//
//
//	// WAIT UNTIL BUFFER UPDATED
//	double waitTime = 0;
//	if (m_trialCont.sample_rates[0] > 0)
//	{
//		waitTime = double(m_sizeBufferMarco) / m_trialCont.sample_rates[0] * 1000 - 2; // remove 2ms to avoid accumulating delays
//	}
//
//	Sleep(waitTime);
//
//	// STORE IN GLOBAL FUNCTION
//	INT16* test = (INT16 *)m_trialCont.samples[CHANNEL2USE_m1];
//	for (size_t j = 0; j < m_trialCont.num_samples[0]; j++)
//	{
//		Signal_m1[j] = test[j];
//	}
//
//	INT16* test2 = (INT16 *)m_trialCont.samples[CHANNEL2USE_m2];
//	for (size_t j = 0; j < m_trialCont.num_samples[0]; j++)
//	{
//		Signal_m2[j] = test2[j];
//	}
//
//	for (size_t chan = 0; chan < m_numEmgChannels; chan++)
//	{
//		INT16* test = (INT16 *)m_trialCont.samples[CHANNELS2USE[chan]];
//		for (size_t j = 0; j < m_trialCont.num_samples[0]; j++)
//		{
//			Signals[chan][j] = test[j];
//		}
//	}
//}
//
//
////function to get SPIKING data...}}}}}}
//void CBlackrock::get_spikes(UINT32*** spikes_32
//	, double*** spikes
//	, double* Raster)
//{
//	cbSdkResult resTest2;
//	// INIT TRIAL (EVERY TIME)
//	//resTest2 = cbSdkInitTrialData(m_blkrckInstance, &m_trialEvent, NULL, NULL, NULL);
//	resTest2 = cbSdkInitTrialData(m_blkrckInstance, NULL, &m_trialEvent, NULL, NULL, NULL);
//
//
//	// GET CONFIG
//	bool bTrialDouble = false;
//	resTest2 = cbSdkGetTrialConfig(m_blkrckInstance, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &bTrialDouble);
//
//	for (UINT32 channel = 0; channel < m_trialEvent.count; channel++)
//	{
//		UINT16 ch = m_trialEvent.chan[channel]; // Actual channel number
//		// Fill timestamps for non-empty channels
//		for (UINT u = 0; u <= cbMAXUNITS; u++)
//		{
//			// m_trialEvent.timestamps[channel][u] = NULL;
//			UINT32 num_samples = m_trialEvent.num_samples[channel][u];
//			if (num_samples > 0)
//			{
//				if (bTrialDouble)
//				{
//					m_trialEvent.timestamps[channel][u] = new double[m_trialEvent.num_samples[channel][u]];
//				}
//				else
//				{
//					m_trialEvent.timestamps[channel][u] = new UINT32[m_trialEvent.num_samples[channel][u]];
//				}
//			}
//		}
//
//		// Fill values for non-empty digital or serial channels
//		//if (ch == MAX_CHANS_DIGITAL_IN || ch == MAX_CHANS_SERIAL)
//		if (ch == cbNUM_DIGIN_CHANS || ch == cbNUM_SERIAL_CHANS)
//		{
//			UINT32 num_samples = m_trialEvent.num_samples[channel][0];
//			// m_trialEvent.waveforms[channel] = NULL;
//			if (num_samples > 0)
//			{
//				if (bTrialDouble)
//				{
//					m_trialEvent.waveforms[channel] = new double[m_trialEvent.num_samples[channel][0]];
//				}
//				else
//				{
//					m_trialEvent.waveforms[channel] = new UINT16[m_trialEvent.num_samples[channel][0]];
//				}
//			}
//		}
//	}
//	//END MEMORY ALLOCATION
//
//	// GET DATA
//	bool bFlushBuffer = true;
//	UINT16 activeChannels = -1;
//	UINT32 num_samples = -1;
//	UINT32 time_rec = -1;
//	resTest2 = cbSdkGetTrialData(m_blkrckInstance, bFlushBuffer, &m_trialEvent, NULL, NULL, NULL);
//
//
//	// STORE IN GLOBAL FUNCTION (ALL SIGNALS)
//	for (UINT32 channel = 0; channel < m_trialEvent.count; channel++)
//	{
//		UINT16 ch = m_trialEvent.chan[channel]; // Actual channel number
//		// Fill timestamps for non-empty channels
//		for (UINT u = 0; u <= cbMAXUNITS; u++)
//		{
//			UINT32 num_samples = m_trialEvent.num_samples[channel][u];
//			if (num_samples > 0)
//			{
//				if (bTrialDouble)
//				{
//					memcpy(spikes[ch - 1][u], m_trialEvent.timestamps[channel][u], num_samples * sizeof(double));
//				}
//				else
//				{
//					memcpy(spikes_32[ch - 1][u], m_trialEvent.timestamps[channel][u], num_samples * sizeof(UINT32));
//					Raster[ch - 1] += num_samples;
//				}
//			}
//		}
//	}
//
//	// DELETE THE MEMORY
//	for (UINT32 channel = 0; channel < m_trialEvent.count; channel++)
//	{
//		for (UINT u = 0; u <= cbMAXUNITS; u++)
//		{
//			if (m_trialEvent.timestamps[channel][u] != NULL)
//			{
//				delete[] m_trialEvent.timestamps[channel][u];
//				m_trialEvent.timestamps[channel][u] = NULL;
//			}
//		}
//
//		if (m_trialEvent.waveforms[channel] != NULL)
//		{
//			delete[] m_trialEvent.waveforms[channel];
//			m_trialEvent.waveforms[channel] = NULL;
//		}
//	}
//}
//
//UINT32 CBlackrock::getTime(void)
//{
//	UINT32 tmpTime;
//	cbSdkResult cbRes;
//	cbRes = cbSdkGetTime(m_blkrckInstance, &tmpTime);
//	return tmpTime;
//}
//
//void CBlackrock::setComment(UINT32 cbColor, std::string cbMessage)
//{
//	cbSdkResult cbRes;
//	cbRes = cbSdkSetComment(m_blkrckInstance, cbColor, m_charset, cbMessage.c_str());
//}

