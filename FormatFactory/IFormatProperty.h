#pragma once
#include <fstream>
using namespace std;

class AFX_EXT_CLASS IFormatProperty
{
public:
	IFormatProperty(void);
	~IFormatProperty(void);

	typedef enum tagFormatType
	{
		FormatType_Lidar = 0,
		FormatType_Product,
		FormatType_Unknown,
		FormatType_Sum
	}FormatType;

	static char* FormatTypeCaption[FormatType_Sum];

public:
	virtual void Store(ofstream& ofp,FormatType formatType = FormatType_Lidar) = 0;
	virtual int Restore(unsigned char* pContent,FormatType formatType = FormatType_Lidar) = 0;
};

