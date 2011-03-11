#include "frequencytest.h"

qint32 sInitFrTest(){
	qint32 id;
	int flag=0;
	do{
		id=qrand()+1;
		flag++;
	}while(sFrTestMap.contains(id) && flag<10000);

	if(flag>=10000)return 0;
	else {
		sFrTestMap.insert(id, new sFrTest_state);
		return id;
	}
}

void sRemoveFrTest(qint32 sFrTestId){
	if(!sFrTestMap.contains(sFrTestId))return;
	delete sFrTestMap[sFrTestId];
	sFrTestMap.remove(sFrTestId);
}

void sSetMovAvPeriod(qint32 sFrTestId, qint32	period){
	if(!sFrTestMap.contains(sFrTestId) || period<1)return;
	sFrTestMap[sFrTestId]->movAvPeriod=period;
	sFrTestMap[sFrTestId]->movAv.setPeriod(period);
}

void sSetSampleRate(qint32 sFrTestId, double sampleRate){
	if(!sFrTestMap.contains(sFrTestId) || sampleRate<1)return;
	sFrTestMap[sFrTestId]->sampleRate=sampleRate;
}

void sAddArray(qint32 sFrTestId, double *array, qint32 arraySize){
	if(!sFrTestMap.contains(sFrTestId) || arraySize<1)return;

	sFrTest_state	*sFrTestBuf=sFrTestMap[sFrTestId];

	qint32 chArrSize=sFrTestBuf->movAvPeriod+1;
	double *chArr=new double[chArrSize];
	qint32 chCount=0;
	double first_time=sFrTestBuf->last_time+1;

	for(int i=arraySize-2;i>=0;i--){
		bool a=array[i]<0;
		bool b=array[i+1]<0;
		if(a^b){
			chArr[chCount]=i+0.5+first_time;
			chCount++;
			if(chCount>=chArrSize)break;
		}
	}

	bool a=array[0]<0;
	bool b=sFrTestBuf->last_value<0;
	if(chCount<chArrSize && a^b){
		chArr[chCount]=first_time-0.5;
		chCount++;
	}

	if(chCount<chArrSize){
		chArr[chCount]=sFrTestBuf->last_ch_time;
		chCount++;
	}

	if(chCount>0)sFrTestBuf->last_ch_time=chArr[chCount-1];
	sFrTestBuf->last_time+=arraySize;
	sFrTestBuf->last_value=array[arraySize-1];

	chCount--;
	for(;chCount>0;chCount--){
		sFrTestBuf->movAv.addPoint(
					sFrTestBuf->sampleRate/2/
					(chArr[chCount-1]-chArr[chCount]) );
	}

	delete chArr;
}

double sGetFrequency(qint32 sFrTestId){
	if(!sFrTestMap.contains(sFrTestId))return 0.0;
	return sFrTestMap[sFrTestId]->movAv.getValue();
}
