#ifndef FREQUENCYTEST_H
#define FREQUENCYTEST_H

#include "../MovingAverage/movingaverage.h"

//	SIMPLE	FRENQUENCY	TEST (sFrTest)

struct sFrTest_state{
	// частота дискретизации
	double sampleRate;
	//время последнего пересечения
	double last_ch_time;
	//последнее значение
	double last_value;
	//время последнего значения
	double last_time;
	//период скользящего среднего
	double movAvPeriod;
	//объект для рассчёта скользящего среднего
	movingAverage	movAv;

	sFrTest_state(){
		movAvPeriod=10;
		movAv.setPeriod(movAvPeriod);
		sampleRate=1000;
		last_value=0;
		last_ch_time=-1;
		last_time=-1;
	}
};

static QMap<qint32, sFrTest_state*> sFrTestMap;

extern "C"{
	qint32 sInitFrTest();
	void sRemoveFrTest(qint32 sFrTestId);
	void sSetMovAvPeriod(qint32 sFrTestId, qint32	period);
	void sSetSampleRate(qint32 sFrTestId, double sampleRate);
	void sAddArray(qint32 sFrTestId, double *array, qint32 arraySize);
	double sGetFrequency(qint32 sFrTestId);
}

#endif // FREQUENCYTEST_H
