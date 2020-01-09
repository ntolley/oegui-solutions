#ifndef MATLABFILTEREDITOR_H_DEFINED
#define MATLABFILTEREDITOR_H_DEFINED

#include <JuceHeader.h>
#include <EditorHeaders.h>

class matlabFilter;
class DualTimeComponent; //**** remove at some point
class FileSource; //*****

/**

  User interface for the "Matlab Filter" processor

*/

class matlabFilterEditor : public GenericEditor
	, public FileDragAndDropTarget
	, public ComboBox::Listener
{
public:
	matlabFilterEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors);
	virtual ~matlabFilterEditor();

	void paintOverChildren(Graphics& g) override;

	void buttonEvent(Button* button) override;

	void saveCustomParameters(XmlElement*) override;
	void loadCustomParameters(XmlElement*) override;

	// FileDragAndDropTarget methods
	// ============================================
	bool isInterestedInFileDrag(const StringArray& files)  override;
	void fileDragExit(const StringArray& files)  override;
	void filesDropped(const StringArray& files, int x, int y)  override;
	void fileDragEnter(const StringArray& files, int x, int y)  override;

	bool setPlaybackStartTime(unsigned int ms);
	bool setPlaybackStopTime(unsigned int ms);
	void setTotalTime(unsigned int ms);
	void setCurrentTime(unsigned int ms);

	void startAcquisition() override;
	void stopAcquisition()  override;

	//void setFile(String file);

	void comboBoxChanged(ComboBox* combo);
	//void populateRecordings(FileSource* source);


private:
	void clearEditor();


	ScopedPointer<UtilityButton>        fileButton;
	ScopedPointer<Label>                fileNameLabel;
	ScopedPointer<ComboBox>             recordSelector;
	ScopedPointer<DualTimeComponent>    currentTime;
	ScopedPointer<DualTimeComponent>    timeLimits;

	matlabFilter* mFilter;
	unsigned int recTotalTime;

	bool m_isFileDragAndDropActive;

	File lastFilePath;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(matlabFilterEditor);
};


class DualTimeComponent : public Component
	, public Label::Listener
	, public AsyncUpdater
{
public:
	DualTimeComponent(matlabFilterEditor* e, bool isEditable);
	~DualTimeComponent();

	void paint(Graphics& g) override;

	void labelTextChanged(Label* label) override;

	void handleAsyncUpdate() override;

	void setEnable(bool enable);

	void setTimeMilliseconds(unsigned int index, unsigned int time);
	unsigned int getTimeMilliseconds(unsigned int index) const;


private:
	ScopedPointer<Label> timeLabel[2];
	String labelText[2];
	unsigned int msTime[2];

	matlabFilterEditor* editor;
	bool isEditable;
};



#endif