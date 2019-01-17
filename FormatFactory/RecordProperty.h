#pragma once
#include "IFormatProperty.h"

class AFX_EXT_CLASS RecordProperty : public IFormatProperty
{
public:
	RecordProperty();
	~RecordProperty();
	
	//̽��ģʽ
    typedef enum tagModeType
    {
		ModeType_Unknown,
        ModeType_Curve = 1,//����̽��
        ModeType_Sum
    }ModeType;

	static char* ModeTypeCaption[ModeType_Sum];

public:
	//̽��ģʽ
	ModeType _ModeType;
	//�Ŵ���
	unsigned short _Amp;
	//��ʼ�ɼ�ʱ��
    CTime _TimeStart;
	//�����ɼ�ʱ��
	CTime _TimeEnd;
	//������ 
	double _FyAngle;
	//��λ��
	double _FwAngle;

public:
	void Store(ofstream& ofp,IFormatProperty::FormatType formatType = IFormatProperty::FormatType_Lidar);
	int Restore(unsigned char* pContent,IFormatProperty::FormatType formatType = IFormatProperty::FormatType_Lidar);
};