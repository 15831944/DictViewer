#pragma once
#include <fstream>
using namespace std;

class AFX_EXT_CLASS IFormatProperty
{
public:
	IFormatProperty(void);
	~IFormatProperty(void);

public:
	virtual void Store(ofstream& ofp) = 0;
	virtual int Restore(unsigned char* pContent) = 0;
};

