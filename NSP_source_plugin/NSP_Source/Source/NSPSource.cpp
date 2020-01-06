#include "NSPSource.h"


namespace NSP {
	//Change all names for the relevant ones, including "Processor Name"
	DataThread* NSPSource::createDataThread(SourceNode *sn)
	{
		return new NSPSource(sn);
	}

	NSPSource::NSPSource(SourceNode* sn) : DataThread(sn)
	{
		m_blackrock = new CBlackrock;
		m_blackrock->setup_connection_blackrock();

		//dataBuffer = new DataBuffer(m_noOfNeuroCh + 1, 1000);
		sourceBuffers.add(new DataBuffer(m_noOfNeuroCh + 1, 1000));

		rasterWindow = new double*[m_noOfNeuroCh];
		m_rasterHolder = new double[m_noOfNeuroCh];
		m_spikesInt32 = new UINT32**[m_noOfNeuroCh];
		m_spikesDouble = new double**[m_noOfNeuroCh];

		for (size_t ch = 0; ch < m_noOfNeuroCh; ch++)
		{
			m_spikesInt32[ch] = new UINT32*[cbMAXUNITS];
			m_spikesDouble[ch] = new double*[cbMAXUNITS];
			for (size_t ui = 0; ui < cbMAXUNITS; ui++)
			{
				m_spikesInt32[ch][ui] = new UINT32[100];
				m_spikesDouble[ch][ui] = new double[100];
			}
		}

		for (size_t ch = 0; ch < m_noOfNeuroCh; ch++)
		{
			rasterWindow[ch] = new double[Buffer_length];
			for (int i = 0; i < Buffer_length; i++)
			{
				rasterWindow[ch][i] = 0;
				Raster_Time[i] = 0;
			}
			firingRates[ch] = 0;
			m_rasterHolder[ch] = 0;
		}
	}

	NSPSource::~NSPSource()
	{
		if (m_rasterHolder != 0)
		{
			delete[] m_rasterHolder;
			m_rasterHolder = 0;
		}

		if (m_spikesInt32 != 0)
		{
			for (size_t ch = 0; ch < m_noOfNeuroCh; ch++)
			{
				for (size_t ui = 0; ui < cbMAXUNITS; ui++)
				{
					delete[] m_spikesInt32[ch][ui];
				}
				delete[] m_spikesInt32[ch];
			}
			delete[] m_spikesInt32;
			m_spikesInt32 = 0;
		}

		if (m_spikesDouble != 0)
		{
			for (size_t ch = 0; ch < m_noOfNeuroCh; ch++)
			{
				for (size_t ui = 0; ui < cbMAXUNITS; ui++)
				{
					delete[] m_spikesDouble[ch][ui];
				}
				delete[] m_spikesDouble[ch];
			}
			delete[] m_spikesDouble;
			m_spikesDouble = 0;
		}

		if (rasterWindow != 0)
		{
			for (size_t ch = 0; ch < m_noOfNeuroCh; ch++)
			{
				delete[] rasterWindow[ch];
			}
			delete[] rasterWindow;
			rasterWindow = 0;
		}

		if (m_blackrock != 0)
		{
			delete m_blackrock;
			m_blackrock = 0;
		}
	}

	void NSPSource::run() {
		// Call the base class's run
		DataThread::run();

	}


	/** Returns the address of the DataBuffer that the input source will fill.*/
	//DataBuffer* getBufferAddress(int subProcessor) {}

	/** Called when the chain updates, to add, remove or resize the sourceBuffers' DataBuffers as needed*/
	void NSPSource::resizeBuffers() {}

	/** Fills the DataBuffer with incoming data. This is the most important
	method for each DataThread.*/
	bool NSPSource::updateBuffer() {
		// Compute spike rates here
		INT64 cbtime2;
		INT64 prev_time;

		// PULL DATA
		prev_time = cbtime1;
		cbtime2 = cbtime1;
		while (cbtime2 == cbtime1)		//wait until new data is ready, it is approx 10 ms
		{
			cbtime2 = m_blackrock->getTime();
			Sleep(1);
		}

		//Clear raster
		for (size_t ch = 0; ch < m_noOfNeuroCh; ch++)
		{
			m_rasterHolder[ch] = 0;
		}

		//get spike counts
		m_blackrock->get_spikes(m_spikesInt32, m_spikesDouble, m_rasterHolder);
		cbtime1 = m_blackrock->getTime();
		cbSdkResult resTest2;

		//add to buffer
		if (i_win >= Buffer_length - 1)
		{
			i_win = 0;
		}
		else
		{
			i_win++;
		}

		double sum = 0;
		double sum_time;

		//add elapsed time to time buffer
		Raster_Time[i_win] = double(cbtime1 - prev_time) / double(m_Fs); // since cbtime1 is in samples not actual seconds
		elapsedTime += double(cbtime1 - prev_time); //in samples

		firingRates[96] = elapsedTime;

		for (int ch = 0; ch < m_noOfNeuroCh; ch++)
		{
			//put spike count into buffer
			rasterWindow[ch][i_win] = m_rasterHolder[ch];

			/*
			if (cbtime1 - prev_time)
			{
			Raster_Time[i_win] = double(cbtime1 - prev_time) / double(Fs);
			}
			else
			{
			Raster_Time[i_win] = m_initRasterTime;
			}
			*/

			//calculate spike rate over Buffer_length for this particular time point
			sum = 0;
			sum_time = 0;
			for (int i = 0; i < Buffer_length; i++)
			{
				sum = sum + rasterWindow[ch][i];
				sum_time = sum_time + Raster_Time[i];
			}
			firingRates[ch] = sum / sum_time;

			//debugFile << "Channel: " << ch << " sum: " << firingRates[ch] << "\n";
			//debugFile << rasterWindow[ch][i_win] << " ";

		}
		debugFile << std::to_string(double(cbtime1 - prev_time)) << " ";
		for (int ch = 0; ch < m_noOfNeuroCh; ch++)
		{
			debugFile << firingRates[ch] << " ";
		}
		debugFile << "\n";

		uint64 eventCode = 0;

		//dataBuffer->addToBuffer(firingRates, &elapsedTime, &eventCode, 1);
		sourceBuffers[0]->addToBuffer(firingRates, &elapsedTime, &eventCode, 1);

		loopCount++;


		return true;

	}

	/** Experimental method used for testing data sources that can deliver outputs.*/
	void NSPSource::setOutputHigh() {

	}

	/** Experimental method used for testing data sources that can deliver outputs.*/
	void NSPSource::setOutputLow() {

	}

	/** Returns true if the data source is connected, false otherwise.*/
	bool NSPSource::foundInputSource() {
		return true;
	}

	/** Initializes data transfer.*/
	bool NSPSource::startAcquisition() {
		sourceBuffers[0]->clear();



		std::cout << "NSPSource starting acquisition." << std::endl;
		m_blackrock->connection_init_neural();
		debugFile.open(debugPath);
		i_win = -1;
		loopCount = 0;
		cbtime1 = m_blackrock->getTime();
		elapsedTime = 0;
		startThread();

		return true;
	}

	/** Stops data transfer.*/
	bool NSPSource::stopAcquisition() {
		debugFile.close();
		std::cout << "NSPSource stopping acquisition." << std::endl;
		//m_blackrock->connection_end();

		if (isThreadRunning())
		{
			signalThreadShouldExit();

		}

		if (waitForThreadToExit(500))
		{
			std::cout << "Thread exited." << std::endl;
		}
		else
		{
			std::cout << "Thread failed to exit, continuing anyway..." << std::endl;
		}
		return true;
	}

	/** Returns the number of continuous headstage channels the data source can provide.*/
	int NSPSource::getNumDataOutputs(DataChannel::DataChannelTypes type, int subProcessorIdx) const {
		if (type == DataChannel::DataChannelTypes::HEADSTAGE_CHANNEL) {
			return m_noOfNeuroCh + 1;
		}
		else {
			return 0;
		}
	}

	/** Returns the number of TTL channels that each subprocessor generates*/
	int NSPSource::getNumTTLOutputs(int subProcessorIdx) const {
		//**Look at sdk to get this value**
		//return m_noOfTTL
		return 0;
	}

	/** Returns the sample rate of the data source.*/
	float NSPSource::getSampleRate(int subProcessorIdx) const {
		return 1000;
	}

	/** Returns the number of virtual subprocessors this source can generate */
	unsigned int NSPSource::getNumSubProcessors() const {
		//Not sure what this is... check sdk 
		return 1;

	}

	/** Called to create extra event channels, apart from the default TTL ones*/
	void NSPSource::createExtraEvents(Array<EventChannel*>& events) {

	}

	/** Returns the volts per bit of the data source.*/
	float NSPSource::getBitVolts(const DataChannel* chan) const {

		return 1;
	}

	/** Notifies if the device is ready for acquisition */
	bool NSPSource::isReady() {
		return true;
	}

	int NSPSource::modifyChannelName(int channel, String newName) {
		// Do something with ChannelCustomInfo, eventually
		return 0;
	}

	int NSPSource::modifyChannelGain(int channel, float gain) {
		return 0;
	}

	/*  virtual void getChannelsInfo(StringArray &Names, Array<ChannelType> &type, Array<int> &stream, Array<int> &originalChannelNumber, Array<float> &gains)
	  {
	  }*/

	void NSPSource::getEventChannelNames(StringArray& names) {
		names.clear();
		for (int k = 0; k < m_noOfNeuroCh; k++)
		{
			names.add("Channel" + String(k + 1));
		}
	}

	bool NSPSource::usesCustomNames() {
		return false;
	}

	/** Changes the names of channels, if the thread needs custom names. */
	void NSPSource::updateChannels() {

	}

	/** Returns a pointer to the data input device, in case other processors
	need to communicate with it.*/
	//  virtual void* getDevice();

	//void getChannelInfo(Array<ChannelCustomInfo>& infoArray) {
	//
	//}

	/** Create the DataThread custom editor, if any*/
	//GenericEditor* createEditor(SourceNode* sn) {
	//
	//}

	//void createTTLChannels() {
	//
	//}

	String NSPSource::getChannelUnits(int chanIndex) {
		//check what actual units are
		return String::empty;
	}

}