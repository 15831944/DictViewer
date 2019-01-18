#include "StdAfx.h"
#include "RecordProperty.h"

char* RecordProperty::ModeTypeCaption[] = {"Î´¶¨Òå","ÀªÏßÌ½²â"};

RecordProperty::RecordProperty()
{
	_ModeType = ModeType_Unknown;
	_FyAngle = 0.0;
	_FwAngle = 0.0;
}

RecordProperty::~RecordProperty()
{

}

void RecordProperty::Store(ofstream& ofp,IFormatProperty::FormatType formatType)
{
	unsigned short usTemp;
	usTemp = _ModeType;
	if(formatType  == IFormatProperty::FormatType_Product)
	{
		usTemp = usTemp << 14;
		usTemp |= (_Amp & 0x3fff);
	}
	ofp.write((char*)&usTemp,2);

	CTime t(1970, 1, 1, 12, 0, 0);
	CTimeSpan tSpan = _TimeStart - t;
	CTimeSpan tSpanX(12*60*60);
	tSpan = tSpan + tSpanX;
	usTemp = tSpan.GetDays();
	CTimeSpan tSpanE(usTemp * 3600 * 24);
	tSpan = tSpan - tSpanE;
	unsigned int iTemp = tSpan.GetTotalSeconds();
	ofp.write((char*)&iTemp,4);

	tSpan = _TimeEnd - t;
	tSpan = tSpan + tSpanX;
	tSpan = tSpan - tSpanE;
	iTemp = tSpan.GetTotalSeconds();
	ofp.write((char*)&iTemp,4);

	ofp.write((char*)&usTemp,2);

	usTemp = _FyAngle / (180.0 / 4096.0) * 8.0;
	ofp.write((char*)&usTemp,2);

	if(formatType  == IFormatProperty::FormatType_Lidar)
	{
		usTemp = _FwAngle / (180.0 / 4096.0) * 8.0;
		ofp.write((char*)&usTemp,2);
	}
}

int RecordProperty::Restore(unsigned char* pContent,IFormatProperty::FormatType formatType)
{
	unsigned short usTemp;
	unsigned int iTemp, iTempc;
	double fTemp;

	usTemp = pContent[31];
	usTemp = (unsigned short)(usTemp << 8);
	usTemp += pContent[30];
	if(formatType == IFormatProperty::FormatType_Lidar)
	{
		if (usTemp >= ModeType_Sum)
		{
			_ModeType = ModeType_Unknown;
			return -1;
		}
		_ModeType = (ModeType)usTemp;
	}
	else
	{
		_Amp = (usTemp & 0x3fff);
		usTemp = (usTemp >> 14);
		if (usTemp >= ModeType_Sum)
		{
			_ModeType = ModeType_Unknown;
			return -1;
		}
		_ModeType = (ModeType)usTemp;
	}

	unsigned short totalDays;
	totalDays = pContent[41];
	totalDays = (unsigned short)(totalDays << 8);
	totalDays += pContent[40];

	iTemp = pContent[32];
	iTempc = pContent[33];
	iTempc = (iTempc << 8);
	iTemp += iTempc;
	iTempc = pContent[34];
	iTempc = (iTempc << 16);
	iTemp += iTempc;
	iTempc = pContent[35];
	iTempc = (iTempc << 24);
	iTemp += iTempc;
	CTime t(1970, 1, 1, 12, 0, 0);
	CTimeSpan tSpanD(totalDays,0, 0, 0);
	CTimeSpan tSpanS(iTemp);
	CTimeSpan tSpanX(12*60*60);
	_TimeStart = t + tSpanD + tSpanS - tSpanX;

	iTemp = pContent[36];
	iTempc = pContent[37];
	iTempc = (iTempc << 8);
	iTemp += iTempc;
	iTempc = pContent[38];
	iTempc = (iTempc << 16);
	iTemp += iTempc;
	iTempc = pContent[39];
	iTempc = (iTempc << 24);
	iTemp += iTempc;
	CTimeSpan tSpanE(iTemp);
	_TimeEnd = t + tSpanD + tSpanE - tSpanX;

	usTemp = pContent[43];
	usTemp = (unsigned short)(usTemp << 8);
	usTemp += pContent[42];
	fTemp = ((double)usTemp) / 8.0 * (180.0 / 4096.0);
	if (fTemp > 90.0 || fTemp < -90.0)
		return -2;
	_FyAngle = fTemp;

	if(formatType != IFormatProperty::FormatType_Lidar)
		return 0;

	usTemp = pContent[45];
	usTemp = (unsigned short)(usTemp << 8);
	usTemp += pContent[44];
	fTemp = ((double)usTemp) / 8.0 * (180.0 / 4096.0);
	if (fTemp > 360.0 || fTemp < 0.0)
		return -3;
	_FwAngle = fTemp;

	return 0;
}