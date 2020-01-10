#ifndef MATLABFILTEREDITOR_H_DEFINED
#define MATLABFILTEREDITOR_H_DEFINED

#include <JuceHeader.h>
#include <EditorHeaders.h>

class matlabFilter;
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


	void startAcquisition() override;
	void stopAcquisition()  override;

	void setFile(String file);

	void comboBoxChanged(ComboBox* combo);
	//void populateRecordings(FileSource* source);


private:
	void clearEditor();


	ScopedPointer<UtilityButton>        fileButton;
	ScopedPointer<Label>                fileNameLabel;
	ScopedPointer<ComboBox>             recordSelector;


	matlabFilter* mFilter;
	unsigned int recTotalTime;

	bool m_isFileDragAndDropActive;

	File lastFilePath;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(matlabFilterEditor);
};


#endif