#pragma once
#include "IFormatProperty.h"
#include "ChannelProperty.h"

class AFX_EXT_CLASS Channel : public IFormatProperty
{
public:
	Channel();
	Channel(unsigned int no);
	~Channel(void);

public:
	ChannelProperty* _pChannelProperty;
    float* _pDatas;

public:
	void Store(ofstream& ofp,IFormatProperty::FormatType formatType = IFormatProperty::FormatType_Lidar);
	int Restore(unsigned char* pContent,IFormatProperty::FormatType formatType = IFormatProperty::FormatType_Lidar);
};