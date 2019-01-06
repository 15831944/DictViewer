#pragma once
#include "IFormatProperty.h"

class AFX_EXT_CLASS ChannelProperty : public IFormatProperty
{
public:
    ChannelProperty();
	ChannelProperty(unsigned int no);
    ~ChannelProperty();

    typedef enum tagAcqType
	{
		AcqType_AD = 0,
		AcqType_PC,
		AcqType_MIX,
		AcqType_Unknown,
		AcqType_Sum
	}AcqType;

	typedef enum tagWaveType
	{
		WaveType_P = 1,
		WaveType_S,
		WaveType_Laman,
		WaveType_Unknown,
		WaveType_Sum
	}WaveType;

    static char* AcqTypeString[AcqType_Sum];
	static char* WaveTypeString[WaveType_Sum];

protected:
	unsigned int _NO;

public:
	AcqType _AcqType;
	unsigned short _WaveLen;  
	WaveType _WaveType;
    double _DistResolution;
	double _DeadZone;
    unsigned short _DistCount;
	unsigned int _DataPtr;

public:
	void Store(ofstream& ofp);
	int Restore(unsigned char* pContent);
};