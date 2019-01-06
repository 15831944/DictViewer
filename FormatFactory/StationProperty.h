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
	//��վ��
	CString _ID;
	//λ��
	Position _Position;
	//����
	vector<unsigned short> _LenOfWaves;
	//ͨ����
	unsigned short _ChannelCount;

public:
	int Restore(unsigned char* pContent);
	void Store(ofstream& ofp);
};