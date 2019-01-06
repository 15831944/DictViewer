#pragma once
#include "IFormatProperty.h"

class AFX_EXT_CLASS RecordProperty : public IFormatProperty
{
public:
	RecordProperty();
	~RecordProperty();
	
	//探测模式
    typedef enum tagModeType
    {
		ModeType_Unknown,
        ModeType_Curve = 1,//廓线探测
        ModeType_Sum
    }ModeType;

	static char* ModeTypeCaption[ModeType_Sum];

public:
	//探测模式
	ModeType _ModeType;
	//开始采集时间
    CTime _TimeStart;
	//结束采集时间
	CTime _TimeEnd;
	//俯仰角 
	double _FyAngle;
	//方位角
	double _FwAngle;

public:
	void Store(ofstream& ofp);
	int Restore(unsigned char* pContent);
};