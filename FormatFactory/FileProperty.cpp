#include "StdAfx.h"
#include "FileProperty.h"

char* FileProperty::FileTypeCaption[] = {"原始数据","产品数据","未定义"};

FileProperty::FileProperty(void)
{
	_FormatVersion = 0;
	_FileType = FileType_Unknown;
}


FileProperty::~FileProperty(void)
{
}


void FileProperty::Store(ofstream& ofp)
{
	/*char* pChar = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
	ofp.write(pChar,14);

	unsigned short temp = _FileType;
	pChar = (char*)&temp;
	ofp.write(pChar,2);

	pChar = (char*)&FormatVersion;
	ofp.write(pChar,2);*/
}

int FileProperty::Restore(unsigned char* pContent)
{
	unsigned short usTemp;
    usTemp = pContent[15];
    usTemp *= 8;
    usTemp += pContent[14];
    if (usTemp >= FileType_Sum-1)
	{
		_FileType = FileType_Unknown;
        return -1;
	}
    _FileType = (FileType)usTemp;

    usTemp = pContent[17];
    usTemp = (unsigned short)(usTemp<<8);
    usTemp += pContent[16];
    if (usTemp != FormatVersion)
        return -2;
	_FormatVersion = usTemp;
    return 0;
}