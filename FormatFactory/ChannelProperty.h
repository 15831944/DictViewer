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

	typedef enum tagProductType
	{
		ProductType_Unkown,
		ProductType_MEXT,
		ProductType_MBAKSCAT,
		ProductType_MDEP,
		ProductType_REXT,
		ProductType_RBAKSCAT,

		ProductType_AOD,
		ProductType_VVIS,
		ProductType_MPBL,
		ProductType_PM10,
		ProductType_CLOUD,
		ProductType_SUM = ProductType_CLOUD
	}ProductType;

    static char* AcqTypeString[AcqType_Sum];
	static char* WaveTypeString[WaveType_Sum];
	static char* ProductTypeString[ProductType_SUM+1];
protected:
	unsigned short _NO;

public:
	AcqType _AcqType;
	unsigned short _WaveLen;  
	WaveType _WaveType;
    double _DistResolution;
	double _DeadZone;
    unsigned short _DistCount;
	unsigned int _DataPtr;

	ProductType _ProductType;

public:
	void Store(ofstream& ofp, IFormatProperty::FormatType formatType = IFormatProperty::FormatType_Lidar);
	int Restore(unsigned char* pContent, IFormatProperty::FormatType formatType = IFormatProperty::FormatType_Lidar);
};