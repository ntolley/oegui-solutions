
#include "matlabFilterEditor.h"
#include "matlabFilter.h"
#include <stdio.h>

matlabFilterEditor::matlabFilterEditor(GenericProcessor* parentNode, bool useDefaultParameterEditors = true)
	: GenericEditor(parentNode, useDefaultParameterEditors)
	, mFilter(static_cast<matlabFilter*> (parentNode))
	, recTotalTime(0)
	, m_isFileDragAndDropActive(false)
{
	lastFilePath = CoreServices::getDefaultUserSaveDirectory();

	fileButton = new UtilityButton("F:", Font("Small Text", 13, Font::plain));
	fileButton->addListener(this);
	fileButton->setBounds(5, 27, 20, 20);
	addAndMakeVisible(fileButton);

	fileNameLabel = new Label("FileNameLabel", "No file selected.");
	fileNameLabel->setBounds(30, 25, 140, 20);
	addAndMakeVisible(fileNameLabel);

	recordSelector = new ComboBox("Recordings");
	recordSelector->setBounds(30, 50, 120, 20);
	recordSelector->addListener(this);
	addAndMakeVisible(recordSelector);

	currentTime = new DualTimeComponent(this, false);
	currentTime->setBounds(5, 80, 175, 20);
	addAndMakeVisible(currentTime);

	timeLimits = new DualTimeComponent(this, true);
	timeLimits->setBounds(5, 105, 175, 20);
	addAndMakeVisible(timeLimits);

	desiredWidth = 180;

	setEnabledState(false);
}


matlabFilterEditor::~matlabFilterEditor()
{
}


//void matlabFilterEditor::setFile(String file)
//{
//	File fileToRead(file);
//	lastFilePath = fileToRead.getParentDirectory();
//
//	if (mFilter->setFile(fileToRead.getFullPathName()))
//	{
//		fileNameLabel->setText(fileToRead.getFileName(), dontSendNotification);
//
//		setEnabledState(true);
//	}
//	else
//	{
//		clearEditor();
//	}
//
//	CoreServices::updateSignalChain(this);
//	repaint();
//}


void matlabFilterEditor::paintOverChildren(Graphics& g)
{
	// Draw a frame around component if files are drag&dropping now
	if (m_isFileDragAndDropActive)
	{
		g.setColour(Colours::aqua);
		g.drawRect(getLocalBounds(), 2.f);
	}
}


void matlabFilterEditor::buttonEvent(Button* button)
{
	if (!acquisitionIsActive)
	{
		if (button == fileButton)
		{
			StringArray extensions = mFilter->getSupportedExtensions();
			String supportedFormats = String::empty;

			int numExtensions = extensions.size();
			for (int i = 0; i < numExtensions; ++i)
			{
				supportedFormats += ("*." + extensions[i]);
				if (i < numExtensions - 1)
					supportedFormats += ";";
			}

			FileChooser chooseFileReaderFile("Please select the file you want to load...",
				lastFilePath,
				supportedFormats);

			if (chooseFileReaderFile.browseForFileToOpen())
			{
				// Use the selected file
				//setFile(chooseFileReaderFile.getResult().getFullPathName());

				// lastFilePath = fileToRead.getParentDirectory();

				// thread->setFile(fileToRead.getFullPathName());

				// fileNameLabel->setText(fileToRead.getFileName(),false);
			}
		}
	}
}


bool matlabFilterEditor::setPlaybackStartTime(unsigned int ms)
{
	if (ms > timeLimits->getTimeMilliseconds(1))
		return false;

	mFilter->setParameter(1, ms);
	return true;
}


bool matlabFilterEditor::setPlaybackStopTime(unsigned int ms)
{
	if ((ms > recTotalTime)
		|| (ms < timeLimits->getTimeMilliseconds(0)))
		return false;

	mFilter->setParameter(2, ms);
	return true;
}


void matlabFilterEditor::setTotalTime(unsigned int ms)
{
	timeLimits->setTimeMilliseconds(0, 0);
	timeLimits->setTimeMilliseconds(1, ms);
	currentTime->setTimeMilliseconds(0, 0);
	currentTime->setTimeMilliseconds(1, ms);

	recTotalTime = ms;
}


void matlabFilterEditor::setCurrentTime(unsigned int ms)
{
	currentTime->setTimeMilliseconds(0, ms);
}


void matlabFilterEditor::comboBoxChanged(ComboBox* combo)
{
	mFilter->setParameter(0, combo->getSelectedId() - 1);
	CoreServices::updateSignalChain(this);
}


void matlabFilterEditor::clearEditor()
{
	fileNameLabel->setText("No file selected.", dontSendNotification);
	recordSelector->clear(dontSendNotification);

	timeLimits->setTimeMilliseconds(0, 0);
	timeLimits->setTimeMilliseconds(1, 0);
	currentTime->setTimeMilliseconds(0, 0);
	currentTime->setTimeMilliseconds(1, 0);

	setEnabledState(false);
}


void matlabFilterEditor::startAcquisition()
{
	recordSelector->setEnabled(false);
	timeLimits->setEnable(false);
}


void matlabFilterEditor::stopAcquisition()
{
	recordSelector->setEnabled(true);
	timeLimits->setEnable(true);
}


void matlabFilterEditor::saveCustomParameters(XmlElement* xml)
{
	xml->setAttribute("Type", "FileReader");

	XmlElement* childNode = xml->createNewChildElement("FILENAME");
	childNode->setAttribute("path", mFilter->getFile());
	childNode->setAttribute("recording", recordSelector->getSelectedId());

	childNode = xml->createNewChildElement("TIME_LIMITS");
	childNode->setAttribute("start_time", (double)timeLimits->getTimeMilliseconds(0));
	childNode->setAttribute("stop_time", (double)timeLimits->getTimeMilliseconds(1));
}


void matlabFilterEditor::loadCustomParameters(XmlElement* xml)
{
	forEachXmlChildElement(*xml, element)
	{
		if (element->hasTagName("FILENAME"))
		{
			String filepath = element->getStringAttribute("path");
			//setFile(filepath);

			int recording = element->getIntAttribute("recording");
			recordSelector->setSelectedId(recording, sendNotificationSync);
		}
		else if (element->hasTagName("TIME_LIMITS"))
		{
			unsigned int time = 0;

			time = (unsigned int)element->getDoubleAttribute("start_time");
			setPlaybackStartTime(time);
			timeLimits->setTimeMilliseconds(0, time);

			time = (unsigned int)element->getDoubleAttribute("stop_time");
			setPlaybackStopTime(time);
			timeLimits->setTimeMilliseconds(1, time);
		}
	}
}


bool matlabFilterEditor::isInterestedInFileDrag(const StringArray& files)
{
	if (!acquisitionIsActive)
	{
		const bool isExtensionSupported = mFilter->isFileSupported(files[0]);
		m_isFileDragAndDropActive = true;

		return isExtensionSupported;
	}

	return false;
}


void matlabFilterEditor::fileDragExit(const StringArray& files)
{
	m_isFileDragAndDropActive = false;

	repaint();
}


void matlabFilterEditor::fileDragEnter(const StringArray& files, int x, int y)
{
	m_isFileDragAndDropActive = true;

	repaint();
}


void matlabFilterEditor::filesDropped(const StringArray& files, int x, int y)
{
	//setFile(files[0]);

	m_isFileDragAndDropActive = false;
	repaint();
}


// DualTimeComponent
// ================================================================================
DualTimeComponent::DualTimeComponent(matlabFilterEditor* e, bool editable)
	: editor(e)
	, isEditable(editable)
{
	Label* l;
	l = new Label("Time1");
	l->setBounds(0, 0, 75, 20);
	l->setEditable(isEditable);
	l->setFont(Font("Small Text", 10, Font::plain));
	if (isEditable)
	{
		l->addListener(this);
		l->setColour(Label::backgroundColourId, Colours::lightgrey);
		l->setColour(Label::outlineColourId, Colours::black);
	}

	addAndMakeVisible(l);
	timeLabel[0] = l;

	l = new Label("Time2");
	l->setBounds(85, 0, 75, 20);
	l->setEditable(isEditable);
	l->setFont(Font("Small Text", 10, Font::plain));
	if (isEditable)
	{
		l->addListener(this);
		l->setColour(Label::backgroundColourId, Colours::lightgrey);
		l->setColour(Label::outlineColourId, Colours::black);
	}

	addAndMakeVisible(l);
	timeLabel[1] = l;

	setTimeMilliseconds(0, 0);
	setTimeMilliseconds(1, 0);
}


DualTimeComponent::~DualTimeComponent()
{
}


void DualTimeComponent::paint(Graphics& g)
{
	String sep;
	if (isEditable)
		sep = "-";
	else
		sep = "/";
	g.setFont(Font("Small Text", 10, Font::plain));
	g.setColour(Colours::darkgrey);
	g.drawText(sep, 78, 0, 5, 20, Justification::centred, false);
}


void DualTimeComponent::setTimeMilliseconds(unsigned int index, unsigned int time)
{
	if (index > 1)
		return;

	msTime[index] = time;

	int msFrac = 0;
	int secFrac = 0;
	int minFrac = 0;
	int hourFrac = 0;

	msFrac = time % 1000;
	time /= 1000;
	secFrac = time % 60;
	time /= 60;
	minFrac = time % 60;
	time /= 60;
	hourFrac = time;

	labelText[index] = String(hourFrac).paddedLeft('0', 2)
		+ ":" + String(minFrac).paddedLeft('0', 2)
		+ ":" + String(secFrac).paddedLeft('0', 2)
		+ "." + String(msFrac).paddedLeft('0', 3);

	if (editor->acquisitionIsActive)
	{
		triggerAsyncUpdate();
	}
	else
	{
		timeLabel[index]->setText(labelText[index], dontSendNotification);
	}
}


void DualTimeComponent::handleAsyncUpdate()
{
	timeLabel[0]->setText(labelText[0], dontSendNotification);
}


unsigned int DualTimeComponent::getTimeMilliseconds(unsigned int index) const
{
	if (index > 1)
		return 0;

	return msTime[index];
}


void DualTimeComponent::setEnable(bool enable)
{
	timeLabel[0]->setEnabled(enable);
	timeLabel[1]->setEnabled(enable);
}


void DualTimeComponent::labelTextChanged(Label* label)
{
	const int index = (label == timeLabel[0]) ? 0 : 1;

	StringArray elements;
	elements.addTokens(label->getText(), ":.", String::empty);

	unsigned int time = elements[0].getIntValue();
	time = 60 * time + elements[1].getIntValue();
	time = 60 * time + elements[2].getIntValue();
	time = 1000 * time + elements[3].getIntValue();

	bool res = false;
	if (index == 0)
		res = editor->setPlaybackStartTime(time);
	else
		res = editor->setPlaybackStopTime(time);

	if (res)
		setTimeMilliseconds(index, time);
	else
		setTimeMilliseconds(index, getTimeMilliseconds(index));
}
