#pragma once
#include "FileProperty.h"
#include "StationProperty.h"
#include "RecordProperty.h"
#include "Channel.h"

class AFX_EXT_CLASS StandardFile
{
public:
	StandardFile(void);
	~StandardFile(void);

public:
	FileProperty* _pFileProperty;
	StationProperty* _pStationProperty;
	RecordProperty* _pRecordProperty;
	vector<Channel*> _Channels;

protected:
	BOOL _bDirtyFile;

public:
	BOOL IsDirty();
	void Store(ofstream& ofp);
	int Restore(unsigned char* pContent);

	void ConvertToAscii(ofstream& ofp);
};

