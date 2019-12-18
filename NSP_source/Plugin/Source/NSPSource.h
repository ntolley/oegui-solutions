//This prevents include loops. We recommend changing the macro to a name suitable for your plugin
#ifndef NSPSOURCE_H_DEFINED
#define NSPSOURCE_H_DEFINED

#include <DataThreadHeaders.h>

#include <stdio.h>
#include <string.h>
#include <chrono>
#include <thread>
#include <math.h>
#include "cbsdk.h"
#include "Blackrock.h"
#include <iostream>
#include <fstream>

//namespace must be an unique name for your plugin
namespace NSPSourceSpace
{
	class NSPSource : public DataThread
	{
	public:
		/** The class constructor, used to initialize any members. */
		NSPSource(SourceNode* sn);

		/** The class destructor, used to deallocate memory */
		~NSPSource();

		void run(); // this isn't virtual, we can use the parent's if we want

		  /** Fills the DataBuffer with incoming data. This is the most important
			method for each DataThread.*/
		bool updateBuffer();

		/** Returns true if the data source is connected, false otherwise.*/
		bool foundInputSource();

		/** Initializes data transfer.*/
		bool startAcquisition();

		/** Stops data transfer.*/
		bool stopAcquisition();

		/** Returns the number of continuous headstage channels the data source can provide.*/
		int getNumHeadstageOutputs();

		/** Returns the number of continuous aux channels the data source can provide.*/
		int getNumAuxOutputs();

		/** Returns the number of continuous ADC channels the data source can provide.*/
		int getNumAdcOutputs();

		/** Returns the sample rate of the data source.*/
		float getSampleRate();

		/** Returns the volts per bit of the data source.*/
		float getBitVolts(Channel* chan);

		/** Returns the number of event channels of the data source.*/
		int getNumEventChannels();

		/** Notifies if the device is ready for acquisition */
		bool isReady();

		int modifyChannelName(int channel, String newName);

		int modifyChannelGain(int channel, float gain);

		/*  virtual void getChannelsInfo(StringArray &Names, Array<ChannelType> &type, Array<int> &stream, Array<int> &originalChannelNumber, Array<float> &gains)
	{
	}*/

		void getEventChannelNames(StringArray& names);

		bool usesCustomNames();

	private:
		void setDefaultChannelNames();

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