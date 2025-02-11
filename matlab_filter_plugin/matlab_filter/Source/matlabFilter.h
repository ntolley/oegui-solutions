//This prevents include loops. We recommend changing the macro to a name suitable for your plugin
#ifndef MATLABFILTER_H_DEFINED
#define MATLABFILTER_H_DEFINED

#include <ProcessorHeaders.h>
#include "engine.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <FileSourceHeaders.h>

//#include "FileSource.h"





class matlabFilter : public GenericProcessor
{
public:

	/** The class constructor, used to initialize any members. */
	matlabFilter();

	/** The class destructor, used to deallocate memory */
	~matlabFilter();

	// Functions to read matlab script files
	AudioProcessorEditor* createEditor() override;
	bool hasEditor()                const  override { return true; }
	void setEnabledState(bool t)  override;

	String getFile() const;
	bool setFile(String fullpath);

	bool isFileSupported(const String& filename) const;
	bool isFileExtensionSupported(const String& ext) const;
	StringArray getSupportedExtensions() const;

	bool isReady()                  override;
	//bool enable() override;
	//bool disable() override;

	


	// Start Matlab Engine 
	Engine *ep;
	int count = 1; // used to check if first loop during acquisition, reset when new file loaded

	String fileString;

	std::string initString;
	const char *initChar;

	std::string funcString;
	const char *funcChar;

	void process(AudioSampleBuffer& buffer) override;

private:

	HashMap<String, int> supportedExtensions;
	ScopedPointer<FileSource> input;


};


#endif