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
    double* _pDatas;

public:
	void Store(ofstream& ofp);
	int Restore(unsigned char* pContent);
};