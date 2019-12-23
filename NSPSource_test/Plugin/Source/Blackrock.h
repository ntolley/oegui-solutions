#pragma once
#include "cbsdk.h"
#include <string>
#include <Windows.h>
#include <windows.h>
#include <vector>
//#include "stdafx.h"

class CBlackrock
{
public:
	CBlackrock(void);
	virtual ~CBlackrock(void);

	int connection_init_EMG(void);
	void connection_end(void);
	void get_EMG(const int, const int, const int* const, INT16*, INT16*, INT16**);
	void CBlackrock::get_data(std::vector<int>, std::vector<int>, INT16** data);
	void get_spikes(UINT32***, double***, double*);
	UINT32 getTime(void);
	void setComment(UINT32, std::string);
	void setup_connection_blackrock(void);
	int connection_init_neural(void);

private:

private:
	cbSdkTrialEvent m_trialEvent;
	cbSdkTrialCont m_trialCont;
	UINT32 m_blkrckInstance;
	const size_t m_sizeBufferMarco;
	const size_t m_spikeBufferSize;
	const size_t m_neuronalSampleRate;
	//const size_t m_rawNeuralChannels;
	const size_t m_numEmgChannels;
	static const UINT m_charset = 1;
};