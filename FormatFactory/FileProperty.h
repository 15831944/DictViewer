#pragma once
#include "IFormatProperty.h"

class AFX_EXT_CLASS FileProperty : public IFormatProperty
{
public:
	FileProperty(void);
	~FileProperty(void);

	unsigned short _FormatVersion;
	FormatType _FormatType;

protected:
	static const unsigned short FormatVersion = 1;

public:
	void Store(ofstream& ofp,IFormatProperty::FormatType formatType = IFormatProperty::FormatType_Lidar);
	int Restore(unsigned char* pContent,IFormatProperty::FormatType formatType = FormatType_Lidar);
	BOOL IsLidarFile() { return _FormatType; }
};

