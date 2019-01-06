#pragma once
#include "IFormatProperty.h"

class AFX_EXT_CLASS FileProperty : public IFormatProperty
{
public:
	FileProperty(void);
	~FileProperty(void);

	typedef enum tagFileType
	{
		FileType_Lidar = 0,
		FileType_Product,
		FileType_Unknown,
		FileType_Sum
	}FileType;

	
	static char* FileTypeCaption[FileType_Sum];

	unsigned short _FormatVersion;
	FileType _FileType;

protected:
	static const unsigned short FormatVersion = 1;

public:
	void Store(ofstream& ofp);
	int Restore(unsigned char* pContent);
};

