#include "StdAfx.h"
#include "ChannelProperty.h"

char* ChannelProperty::AcqTypeString[] = {"AD","PC","融合","未定义"};
char* ChannelProperty::WaveTypeString[] = {"偏振P","偏振S","拉曼","未定义"};

ChannelProperty::ChannelProperty()
{
	_NO = 1;
}

ChannelProperty::ChannelProperty(unsigned int no)
{
	_NO = no;
}

ChannelProperty::~ChannelProperty()
{

}

void ChannelProperty::Store(ofstream& ofp)
{

}

int ChannelProperty::Restore(unsigned char* pContent)
{
	unsigned short usTemp;
	unsigned int iTemp,iTempc;
	unsigned int idx = 54 + (_NO - 1) * 16;

	usTemp = pContent[idx + 1];
	usTemp = (unsigned short)(usTemp << 8);
	usTemp += pContent[idx];
	if(_NO != usTemp)
		return -1;

	usTemp = pContent[idx + 3];
	usTemp = (unsigned short)(usTemp << 8);
	usTemp += pContent[idx + 2];
	if (((usTemp & 0xc000) >> 14) >= (unsigned short)(AcqType_Sum-1))
	{
		_AcqType = AcqType_Unknown;
		return -2;
	}
	_AcqType = (AcqType)((usTemp & 0xc000) >> 14);

	_WaveLen = (unsigned short)(usTemp & 0x3fff);

	usTemp = pContent[idx + 5];
	usTemp = (unsigned short)(usTemp << 8);
	usTemp += pContent[idx + 4];
	if (usTemp >= (unsigned short)(WaveType_Sum-1))
	{
		_WaveType = WaveType_Unknown;
		return -3;
	}
	_WaveType = (WaveType)usTemp;

	usTemp = pContent[idx + 7];
	usTemp = (unsigned short)(usTemp << 8);
	usTemp += pContent[idx + 6];
	_DistResolution = ((double)usTemp) / 100.0;

	usTemp = pContent[idx + 9];
	usTemp = (unsigned short)(usTemp << 8);
	usTemp += pContent[idx + 8];
	_DeadZone= ((double)usTemp) / 10.0;

	iTemp = pContent[idx + 10];
	iTempc = pContent[idx + 11];
	iTempc = (iTempc << 8);
	iTemp += iTempc;
	iTempc = pContent[idx + 12];
	iTempc = (iTempc << 16);
	iTemp += iTempc;
	iTempc = pContent[idx + 13];
	iTempc = (iTempc << 24);
	iTemp += iTempc;
	_DataPtr = iTemp;

	usTemp = pContent[idx + 15];
	usTemp = (unsigned short)(usTemp << 8);
	usTemp += pContent[idx + 14];
	_DistCount = usTemp;

	return 0;
}
