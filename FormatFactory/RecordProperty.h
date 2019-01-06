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
	//��ʼ�ɼ�ʱ��
    CTime _TimeStart;
	//�����ɼ�ʱ��
	CTime _TimeEnd;
	//������ 
	double _FyAngle;
	//��λ��
	double _FwAngle;

public:
	void Store(ofstream& ofp);
	int Restore(unsigned char* pContent);
};