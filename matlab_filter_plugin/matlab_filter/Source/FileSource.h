/*
	------------------------------------------------------------------

	This file is part of the Open Ephys GUI
	Copyright (C) 2016 Open Ephys

	------------------------------------------------------------------

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef FILESOURCE_H_INCLUDED
#define FILESOURCE_H_INCLUDED

#include <JuceHeader.h>
#include <PluginInfo.h>


class PLUGIN_API FileSource
{
public:
	FileSource();
	virtual ~FileSource();

	String getRecordName(int index) const;

	bool OpenFile(File file);
	bool isFileOpened()  const;
	String getFileName() const;

	virtual bool isReady();

protected:
	struct RecordInfo
	{
		String name;

	};
	Array<RecordInfo> infoArray;

	bool fileOpened;
	Atomic<int> activeRecord;       // atomic to protect against threaded data race in FileReader
	String filename;


private:
	virtual bool Open(File file) = 0;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FileSource);
};


#endif  // FILESOURCE_H_INCLUDED

