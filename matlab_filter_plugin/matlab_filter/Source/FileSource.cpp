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

#include "FileSource.h"


FileSource::FileSource()
	: fileOpened(false)
	, filename("")
{
}


FileSource::~FileSource()
{
}


String FileSource::getRecordName(int index) const
{
	return infoArray[index].name;
}


bool FileSource::isFileOpened() const
{
	return fileOpened;
}


String FileSource::getFileName() const
{
	return filename;
}


bool FileSource::OpenFile(File file)
{
	if (Open(file))
	{
		fileOpened = true;
		filename = file.getFullPathName();
	}
	else
	{
		fileOpened = false;
		filename = String::empty;
	}

	return fileOpened;
}

bool FileSource::isReady()
{
	return true;
}
