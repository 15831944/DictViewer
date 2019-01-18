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

void Channel::Store(ofstream& ofp,IFormatProperty::FormatType formatType)
{
	if(_pChannelProperty == NULL || _pDatas == NULL)
		return;

	_pChannelProperty->Store(ofp,formatType);

	unsigned int* ptr;
	if(formatType == IFormatProperty::FormatType_Lidar)
	{
		ofp.seekp(std::ios::beg,_pChannelProperty->_DataPtr);
		for(unsigned int i=0;i<_pChannelProperty->_DistCount;i++)
		{
			ptr = (unsigned int *)&_pDatas;
			ofp.write((char *)ptr,4);
		}
	}
	else
	{
		for(unsigned int i=0;i<_pChannelProperty->_DistCount;i++)
		{
			ptr = (unsigned int *)&_pDatas;
			ofp.write((char *)ptr,4);
		}
	}
}

int Channel::Restore(unsigned char* pContent,IFormatProperty::FormatType formatType)
{
	if(_pChannelProperty == NULL)
		return -1;

	if(_pChannelProperty->Restore(pContent, formatType) != 0)
		return -2;

	if(formatType == IFormatProperty::FormatType_Lidar)
	{
		unsigned short dist_count = _pChannelProperty->_DistCount;
		unsigned int data_ptr = _pChannelProperty->_DataPtr;

		_pDatas = new float[dist_count];

		float* fTemp;
		for(unsigned short i=0;i<dist_count;i++)
		{ 
			fTemp = (float *)(pContent+ data_ptr + i * 4);
			_pDatas[i] = *fTemp;
		}
	}
	else
	{
		unsigned short dist_count = _pChannelProperty->_DistCount;

		_pDatas = new float[dist_count];

		float* fTemp;
		for(unsigned short i=0;i<dist_count;i++)
		{ 
			fTemp = (float *)(pContent+ 50 + i * 4);
			_pDatas[i] = *fTemp;
		}
	}

	return 0;
}
