#pragma once
#include "IFormatProperty.h"
#include <vector>

class AFX_EXT_CLASS StationProperty : public IFormatProperty
{
public:
	typedef struct tagPosition
	{
		double _longitude;
		double _latitude;
		unsigned short _altitude;

		tagPosition()
		{
			_longitude = 0.0;
			_latitude = 0.0;
			_altitude = 0;
		}
	}Position,*PTR_POSITION;

public:
	StationProperty(void);
	~StationProperty(void);

public:
	//区站号
	CString _ID;
	//位置
	Position _Position;
	//波长
	vector<unsigned short> _LenOfWaves;
	//通道数
	unsigned short _ChannelCount;

public:
	int Restore(unsigned char* pContent);
	void Store(ofstream& ofp);
};