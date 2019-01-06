#include "StdAfx.h"
#include "StationProperty.h"

StationProperty::StationProperty(void)
{
	_ID = _T("");
}

StationProperty::~StationProperty(void)
{

}

int StationProperty::Restore(unsigned char* pContent)
{
	unsigned short usTemp;
	double fTemp;
	
	usTemp = pContent[20];
	usTemp = (unsigned short)(usTemp << 8);
	usTemp += pContent[21];
	_ID.Format(_T("%C%0004d"),pContent[19],usTemp);

	usTemp = pContent[23];
	usTemp = (unsigned short)(usTemp << 8);
	usTemp += pContent[22];
	fTemp = ((double)usTemp) / 8.0 * (180.0 / 4096.0);
	if (fTemp > 180.0 || fTemp < -180.0)
		return -1;
	_Position._longitude = fTemp;

	usTemp = pContent[25];
	usTemp = (unsigned short)(usTemp << 8);
	usTemp += pContent[24];
	fTemp = ((double)usTemp) / 8.0 * (180.0 / 4096.0);
	if (fTemp > 90.0 || fTemp < -90.0)
		return -2;
	_Position._latitude = fTemp;

            
	usTemp = pContent[27];
	usTemp = (unsigned short)(usTemp << 8);
	usTemp += pContent[26];
	_Position._altitude = usTemp;
   
	for (unsigned short i = 0; i < 3; i++)
	{
		usTemp = pContent[47 + i * 2];
		usTemp = (unsigned short)(usTemp << 8);
		usTemp += pContent[46 + i * 2];
		if (usTemp == 0)
			continue;

		_LenOfWaves.push_back(usTemp);
	}

	usTemp = pContent[53];
	usTemp = (unsigned short)(usTemp << 8);
	usTemp += pContent[52];
	if (usTemp == 0)
		return -3;
	_ChannelCount = usTemp;

	return 0;
}

void StationProperty::Store(ofstream& ofp)
{
	
}