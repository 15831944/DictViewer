#include "StdAfx.h"
#include "ChannelProperty.h"

char* ChannelProperty::AcqTypeString[] = {"AD","PC","融合","未定义"};
char* ChannelProperty::WaveTypeString[] = {"偏振P","偏振S","拉曼","未定义"};
char* ChannelProperty::ProductTypeString[] = {"米通道消光系数","米通道后向散射系数","退偏振比","拉曼通道消光系数","拉曼后向散射系数","光学厚度","垂直能见度","污染物混合层高度","PM10颗粒物质量浓度","云信息"};

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

void ChannelProperty::Store(ofstream& ofp, IFormatProperty::FormatType formatType)
{
	unsigned short usTemp;
	if(formatType == IFormatProperty::FormatType_Lidar)
	{
		ofp.write((char*)&_NO,2);

		usTemp = (_AcqType << 14);
		usTemp &= 0xc0;
		usTemp |= (_WaveLen & 0x3f);
		ofp.write((char*)&usTemp,2);

		usTemp = _WaveType;
		ofp.write((char*)&usTemp,2);

		usTemp = _DistResolution * 100;
		ofp.write((char*)&usTemp,2);

		usTemp = _DeadZone * 10;
		ofp.write((char*)&usTemp,2);

		ofp.write((char*)&_DataPtr,4);

		ofp.write((char*)&_DistCount,2);
	}
	else
	{
		ofp.seekp(std::ios_base::beg,28);

		usTemp = _DistResolution * 100;
		ofp.write((char*)&usTemp,2);

		ofp.seekp(std::ios_base::beg,44);
		ofp.write((char*)&_WaveLen,2);

		usTemp = _ProductType;
		ofp.write((char*)&usTemp,2);
		ofp.write((char*)&_DistCount,2);
	}
}

int ChannelProperty::Restore(unsigned char* pContent, IFormatProperty::FormatType formatType)
{
	unsigned short usTemp;
	unsigned int iTemp,iTempc;

	if(formatType == IFormatProperty::FormatType_Lidar)
	{
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
	}
	else
	{
		usTemp = pContent[29];
		usTemp = (unsigned short)(usTemp << 8);
		usTemp += pContent[28];
		_DistResolution = ((double)usTemp) / 100.0;

		usTemp = pContent[45];
		usTemp = (unsigned short)(usTemp << 8);
		usTemp += pContent[44];
		_WaveLen = usTemp;

		usTemp = pContent[47];
		usTemp = (unsigned short)(usTemp << 8);
		usTemp += pContent[46];
		if (usTemp > (unsigned short)(ProductType_SUM) || usTemp == (unsigned short)(ProductType_Unkown))
		{
			_ProductType = ProductType_Unkown;
			return -4;
		}
		_ProductType = (ProductType)usTemp;

		usTemp = pContent[49];
		usTemp = (unsigned short)(usTemp << 8);
		usTemp += pContent[48];
		_DistCount = usTemp;
	}

	return 0;
}
