
#include "matlabFilterEditor.h"
#include "matlabFilter.h"
#include <CoreServicesHeader.h>
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

	fileNameLabel = new Label("FileNameLabel", "matlabFilter_init.m");
	fileNameLabel->setBounds(30, 25, 140, 20);
	addAndMakeVisible(fileNameLabel);

	recordSelector = new ComboBox("Recordings");
	recordSelector->setBounds(30, 50, 120, 20);
	recordSelector->addListener(this);
	addAndMakeVisible(recordSelector);

	desiredWidth = 180;

	setEnabledState(false);

}


matlabFilterEditor::~matlabFilterEditor()
{
}


void matlabFilterEditor::setFile(String file)
{
	File fileToRead(file);
	lastFilePath = fileToRead.getParentDirectory();

	if (mFilter->setFile(fileToRead.getFullPathName()))
	{
		fileNameLabel->setText(fileToRead.getFileName(), dontSendNotification);

		setEnabledState(true);
	}
	else
	{
		clearEditor();
	}

	CoreServices::updateSignalChain(this);
	repaint();
}


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
				setFile(chooseFileReaderFile.getResult().getFullPathName());

				// lastFilePath = fileToRead.getParentDirectory();

				// thread->setFile(fileToRead.getFullPathName());

				// fileNameLabel->setText(fileToRead.getFileName(),false);
			}
		}
	}
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

	setEnabledState(false);
}

//
void matlabFilterEditor::startAcquisition()
{
	recordSelector->setEnabled(false);
}


void matlabFilterEditor::stopAcquisition()
{
	recordSelector->setEnabled(true);
}


void matlabFilterEditor::saveCustomParameters(XmlElement* xml)
{
	xml->setAttribute("Type", "FileReader");

	XmlElement* childNode = xml->createNewChildElement("FILENAME");
	childNode->setAttribute("path", mFilter->getFile());
	childNode->setAttribute("recording", recordSelector->getSelectedId());

}


void matlabFilterEditor::loadCustomParameters(XmlElement* xml)
{
	forEachXmlChildElement(*xml, element)
	{
		if (element->hasTagName("FILENAME"))
		{
			String filepath = element->getStringAttribute("path");
			setFile(filepath);

			int recording = element->getIntAttribute("recording");
			recordSelector->setSelectedId(recording, sendNotificationSync);
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
	setFile(files[0]);

	m_isFileDragAndDropActive = false;
	repaint();
}


