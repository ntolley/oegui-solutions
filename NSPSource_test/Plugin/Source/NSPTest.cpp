#include "NSPTest.h"


//Change all names for the relevant ones, including "Processor Name"
NSPTest::NSPTest(SourceNode* sn) : DataThread(sn)
{

}

NSPTest::~NSPTest()
{

}

void NSPTest::run() {
	// Call the base class's run
	DataThread::run();

}


/** Returns the address of the DataBuffer that the input source will fill.*/
//DataBuffer* getBufferAddress(int subProcessor) {}

/** Called when the chain updates, to add, remove or resize the sourceBuffers' DataBuffers as needed*/
void NSPTest::resizeBuffers() {}

/** Fills the DataBuffer with incoming data. This is the most important
method for each DataThread.*/
bool NSPTest::updateBuffer() {
	// Compute spike rates here

	return true;

}

/** Experimental method used for testing data sources that can deliver outputs.*/
void NSPTest::setOutputHigh() {

}

/** Experimental method used for testing data sources that can deliver outputs.*/
void NSPTest::setOutputLow() {

}

/** Returns true if the data source is connected, false otherwise.*/
bool NSPTest::foundInputSource() {
	return true;
}

/** Initializes data transfer.*/
bool NSPTest::startAcquisition() {
	// Initilization code here
	return true;
}

/** Stops data transfer.*/
bool NSPTest::stopAcquisition() {
	// termination code here
	return true;
}

/** Returns the number of continuous headstage channels the data source can provide.*/
int NSPTest::getNumDataOutputs(DataChannel::DataChannelTypes type, int subProcessorIdx) const {

	//return m_noOfNeuroCh + 1;
	return 96;
}

/** Returns the number of TTL channels that each subprocessor generates*/
int NSPTest::getNumTTLOutputs(int subProcessorIdx) const {
	//**Look at sdk to get this value**
	//return m_noOfTTL
	return 0;
}

/** Returns the sample rate of the data source.*/
float NSPTest::getSampleRate(int subProcessorIdx) const {
	return 1000;
}

/** Returns the number of virtual subprocessors this source can generate */
unsigned int NSPTest::getNumSubProcessors() const{
	//Not sure what this is... check sdk 
	return 0;
}

/** Called to create extra event channels, apart from the default TTL ones*/
void NSPTest::createExtraEvents(Array<EventChannel*>& events) {

}

/** Returns the volts per bit of the data source.*/
float NSPTest::getBitVolts(const DataChannel* chan) const {
	float ans = 1;
	return ans;
}

/** Notifies if the device is ready for acquisition */
bool NSPTest::isReady() {
	return true;
}

int NSPTest::modifyChannelName(int channel, String newName) {
	// Do something with ChannelCustomInfo, eventually
	return 0;
}

int NSPTest::modifyChannelGain(int channel, float gain) {
	return 0;
}

/*  virtual void getChannelsInfo(StringArray &Names, Array<ChannelType> &type, Array<int> &stream, Array<int> &originalChannelNumber, Array<float> &gains)
  {
  }*/

void NSPTest::getEventChannelNames(StringArray& names) {
	/*names.clear();
	for (int k = 0; k < m_noOfNeuroCh; k++)
	{
		names.add("Channel" + String(k + 1));
	}*/
}

bool NSPTest::usesCustomNames() {
	return false;
}

/** Changes the names of channels, if the thread needs custom names. */
void NSPTest::updateChannels() {

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

String NSPTest::getChannelUnits(int chanIndex) {
	//check what actual units are
	return String::empty;
}
