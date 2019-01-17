#include "StdAfx.h"
#include "StandardFile.h"
#include <string>

StandardFile::StandardFile(void)
{
	_bDirtyFile = TRUE;
}


StandardFile::~StandardFile(void)
{
}

BOOL StandardFile::IsDirty()
{
	return _bDirtyFile;
}

void StandardFile::Store(ofstream& ofp)
{
	if(_pFileProperty == NULL
		|| _pStationProperty == NULL
		|| _pRecordProperty == NULL
		|| _Channels.size() == 0)
		return;

	_pFileProperty->Store(ofp);
	_pStationProperty->Store(ofp,_pFileProperty->_FormatType);
	_pRecordProperty->Store(ofp,_pFileProperty->_FormatType);

	vector<Channel*>::iterator it = _Channels.begin();
	while(it != _Channels.end())
	{
		(*it)->Store(ofp,_pFileProperty->_FormatType);
		it++;
	}
}

int StandardFile::Restore(unsigned char* pContent)
{
	_pFileProperty = new FileProperty();
	if(_pFileProperty->Restore(pContent) != 0)
		return -1;

	_pStationProperty = new StationProperty();
	if(_pStationProperty->Restore(pContent) != 0)
		return -2;

	_pRecordProperty = new RecordProperty();
	if(_pRecordProperty->Restore(pContent) != 0)
		return -3;

	for(int i=0;i<_pStationProperty->_ChannelCount;i++)
	{
		Channel* pChannel = new Channel(i+1);
		if(pChannel->Restore(pContent) != 0)
			return -4;
		_Channels.push_back(pChannel);
	}

	_bDirtyFile = FALSE;
	return 0;
}

void StandardFile::ConvertToAscii(ofstream& ofp)
{
	ofp<< "#File Property"<<endl;
	ofp<< " File Type:"<<_pFileProperty->_FormatType<<endl;

	ofp<< endl;
	ofp<< "#Station Property"<<endl;
	string stemp = (LPCSTR)(CStringA)(_pStationProperty->_ID);
	ofp<< " ID:"<<stemp<<endl;
	ofp<< " longitude:"<<_pStationProperty->_Position._longitude<<endl;
	ofp<< " latitude:"<<_pStationProperty->_Position._latitude<<endl;
	ofp<< " altitude:"<<_pStationProperty->_Position._altitude<<endl;
	ofp<< " wave length:";
	for(int i=0;i<_pStationProperty->_LenOfWaves.size();i++)
		ofp<<_pStationProperty->_LenOfWaves.at(i)<<",";
	ofp<<endl;
	ofp<< " channel count:"<<_pStationProperty->_ChannelCount<<endl;

	ofp<<endl;
	ofp<< "#Record Property"<<endl;
	ofp<< " Mode:"<<_pRecordProperty->_ModeType<<endl;
	int year,month,day,hour,minute,second;
	year = _pRecordProperty->_TimeStart.GetYear();
	month = _pRecordProperty->_TimeStart.GetMonth();
	day = _pRecordProperty->_TimeStart.GetDay();
	hour = _pRecordProperty->_TimeStart.GetHour();
	minute = _pRecordProperty->_TimeStart.GetMinute();
	second = _pRecordProperty->_TimeStart.GetSecond();
	ofp<< " time start:"<<year<<"/"<<month<<"/"<<day<<" "<<hour<<":"<<minute<<":"<<second<<endl;
	year = _pRecordProperty->_TimeEnd.GetYear();
	month = _pRecordProperty->_TimeEnd.GetMonth();
	day = _pRecordProperty->_TimeEnd.GetDay();
	hour = _pRecordProperty->_TimeEnd.GetHour();
	minute = _pRecordProperty->_TimeEnd.GetMinute();
	second = _pRecordProperty->_TimeEnd.GetSecond();
	ofp<< " time end:"<<year<<"/"<<month<<"/"<<day<<" "<<hour<<":"<<minute<<":"<<second<<endl;
	ofp<< " fy angle:"<<_pRecordProperty->_FyAngle<<endl;
	ofp<< " fw angle:"<<_pRecordProperty->_FwAngle<<endl;

	for(int i=0;i<_Channels.size();i++)
	{
		Channel* pChannel = _Channels.at(i);

		ofp<<endl;
		ofp<<"#Channel "<<i+1<<"Property"<<endl;
		ofp<<" Acquire Type:"<<pChannel->_pChannelProperty->_AcqType<<endl;
		ofp<<" Wave length:"<<pChannel->_pChannelProperty->_WaveLen<<endl;
		ofp<<" Wave type:"<<pChannel->_pChannelProperty->_WaveType<<endl;
		ofp<<" Range resolution:"<<pChannel->_pChannelProperty->_DistResolution<<endl;
		ofp<<" Dead zone:"<<pChannel->_pChannelProperty->_DeadZone<<endl;
		ofp<<" Range count:"<<pChannel->_pChannelProperty->_DistCount<<endl;
		
		ofp<<" Data:";
		for(int j=0;j<pChannel->_pChannelProperty->_DistCount;j++)
			ofp<<pChannel->_pDatas[j]<<",";
		ofp<<endl;
	}
}
