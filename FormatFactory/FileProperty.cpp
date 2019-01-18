#include "StdAfx.h"
#include "FileProperty.h"

FileProperty::FileProperty(void)
{
	_FormatVersion = 0;
	_FormatType = IFormatProperty::FormatType_Unknown;
}


FileProperty::~FileProperty(void)
{
}


void FileProperty::Store(ofstream& ofp,IFormatProperty::FormatType formatType)
{
	char* pChar = new char[14];
	memset(pChar,0x00,14);
	ofp.write(pChar,14);

	unsigned short temp = _FormatType;
	pChar = (char*)&temp;
	ofp.write(pChar,2);

	pChar = (char*)&FormatVersion;
	ofp.write(pChar,2);
}

int FileProperty::Restore(unsigned char* pContent,IFormatProperty::FormatType formatType)
{
	unsigned short usTemp;
    usTemp = pContent[15];
    usTemp *= 8;
    usTemp += pContent[14];
    if (usTemp >= IFormatProperty::FormatType_Sum-1)
	{
		_FormatType = IFormatProperty::FormatType_Unknown;
        return -1;
	}
    _FormatType = (IFormatProperty::FormatType)usTemp;

    usTemp = pContent[17];
    usTemp = (unsigned short)(usTemp<<8);
    usTemp += pContent[16];
    if (usTemp != FormatVersion)
        return -2;
	_FormatVersion = usTemp;
    return 0;
}