//This prevents include loops. We recommend changing the macro to a name suitable for your plugin
#ifndef NSPSOURCE_H_DEFINED
#define NSPSOURCE_H_DEFINED

#include <DataThreadHeaders.h>
#include <stdio.h>
#include <thread>
#include <string.h>
#include <chrono>
#include <thread>
#include <math.h>
#include <iostream>
#include <fstream>
#include "cbsdk.h"
#include "Blackrock.h"
#include <array>

namespace NSP {

	class NSPSource : public DataThread
	{
	public:
		/** The class constructor, used to initialize any members. */
		NSPSource(SourceNode* sn);

		/** The class destructor, used to deallocate memory */
		~NSPSource();

		/** Calls 'updateBuffer()' continuously while the thread is being run.*/
		// **figure out why this is overridden**
		//void run() override;
		void run();


		/** Returns the address of the DataBuffer that the input source will fill.*/
		//DataBuffer* getBufferAddress(int subProcessor);

		/** Called when the chain updates, to add, remove or resize the sourceBuffers' DataBuffers as needed*/
		void resizeBuffers();

		/** Fills the DataBuffer with incoming data. This is the most important
		method for each DataThread.*/
		bool updateBuffer();

		/** Experimental method used for testing data sources that can deliver outputs.*/
		void setOutputHigh();

		/** Experimental method used for testing data sources that can deliver outputs.*/
		void setOutputLow();

		/** Returns true if the data source is connected, false otherwise.*/
		bool foundInputSource();

		/** Initializes data transfer.*/
		bool startAcquisition();

		/** Stops data transfer.*/
		bool stopAcquisition();

		/** Returns the number of continuous headstage channels the data source can provide.*/
		int getNumDataOutputs(DataChannel::DataChannelTypes type, int subProcessorIdx) const;

		/** Returns the number of TTL channels that each subprocessor generates*/
		int getNumTTLOutputs(int subProcessorIdx) const;

		/** Returns the sample rate of the data source.*/
		float getSampleRate(int subProcessorIdx) const;

		/** Returns the number of virtual subprocessors this source can generate */
		unsigned int getNumSubProcessors() const;

		/** Called to create extra event channels, apart from the default TTL ones*/
		void createExtraEvents(Array<EventChannel*>& events);

		/** Returns the volts per bit of the data source.*/
		float getBitVolts(const DataChannel* chan) const;

		/** Notifies if the device is ready for acquisition */
		bool isReady();

		int modifyChannelName(int channel, String newName);

		int modifyChannelGain(int channel, float gain);

		/*  virtual void getChannelsInfo(StringArray &Names, Array<ChannelType> &type, Array<int> &stream, Array<int> &originalChannelNumber, Array<float> &gains)
		  {
		  }*/

		void getEventChannelNames(StringArray& names);

		bool usesCustomNames();

		/** Changes the names of channels, if the thread needs custom names. */
		void updateChannels();

		/** Returns a pointer to the data input device, in case other processors
		need to communicate with it.*/
		//  virtual void* getDevice();

		//void getChannelInfo(Array<ChannelCustomInfo>& infoArray);

		/** Create the DataThread custom editor, if any*/
		//GenericEditor* createEditor(SourceNode* sn);

		//void createTTLChannels();

		String getChannelUnits(int chanIndex);

		static DataThread* createDataThread(SourceNode* sn);



	private:
		// Deault member variables from base class

		//void setDefaultChannelNames();

		SourceNode* sn;

		//Array<uint64> ttlEventWords;
		//Array<int64> timestamps;

		//Array<ChannelCustomInfo> channelInfo;
		//OwnedArray<DataBuffer> sourceBuffers;

		//Time timer;

		// Member variables required for data thread
		//DataBuffer* dataBuffer;

		UINT32*** m_spikesInt32;
		double*** m_spikesDouble;
		double* m_rasterHolder;
		CBlackrock* m_blackrock;
		static const int m_noOfNeuroCh = 97;
		double** rasterWindow;
		static const int Buffer_length = 15; //TODO: Instead of using constant number of samples, use constant time bin size (since the samples may potentially come in at varying intervals)
		double Raster_Time[Buffer_length];
		static const int m_Fs = 30000;
		float firingRates[m_noOfNeuroCh + 1];
		std::ofstream debugFile;
		std::string debugPath = "NSP_debug.txt";
		int i_win;
		int loopCount;
		INT64 cbtime1;
		int64 elapsedTime;

	};

}

#endif