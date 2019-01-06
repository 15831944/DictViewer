#include "StdAfx.h"
#include "Channel.h"

Channel::Channel()
{
    _pChannelProperty = NULL;
    _pDatas = NULL;
}

Channel::Channel(unsigned int no)
{
	_pChannelProperty = new ChannelProperty(no);
	_pDatas = NULL;
}

Channel::~Channel()
{
	if(_pChannelProperty != NULL)
		delete _pChannelProperty;
	if(_pDatas != NULL)
		delete[] _pDatas;
}

void Channel::Store(ofstream& ofp)
{

}

int Channel::Restore(unsigned char* pContent)
{
	if(_pChannelProperty == NULL)
		return -1;

	if(_pChannelProperty->Restore(pContent) != 0)
		return -2;

	unsigned short dist_count = _pChannelProperty->_DistCount;
	unsigned int data_ptr = _pChannelProperty->_DataPtr;

	_pDatas = new double[dist_count];

	float* fTemp;
	for(unsigned short i=0;i<dist_count;i++)
	{ 
		fTemp = (float *)(pContent+ data_ptr + i * 4);
		_pDatas[i] = *fTemp;
	}

	return 0;
}
