#include "timer.h"


void initTimer(int timerId){
	if(!timers.contains(timerId))
		timers[timerId]=new timer_config;
}

void setPeriod(qint32 timerId, qint32 period){
	if(timers.contains(timerId))
		timers[timerId]->period=period;
}

void setDuration(qint32 timerId, qint32 duration){
	if(timers.contains(timerId))
		timers[timerId]->duration=duration;
}

void setRestValue(qint32 timerId, double restValue){
	if(timers.contains(timerId))
		timers[timerId]->restValue=restValue;
}

void setActionValue(qint32 timerId, double actionValue){
	if(timers.contains(timerId))
		timers[timerId]->actionValue=actionValue;
}

double getValue(qint32 timerId){
	if(!timers.contains(timerId) || !timers[timerId]->isStarted)
		return 0.0;
	timer_config *p=timers[timerId];
	qint32	msec=QTime::currentTime().msecsTo(p->startTime);
	if(msec%p->period > p->period - p->duration)
		return p->actionValue;
	else return p->restValue;
}

void startTimer(qint32 timerId){
	if(timers.contains(timerId)){
		timers[timerId]->startTime=QTime::currentTime();
		timers[timerId]->isStarted=true;
	}
}

void resetTimer(qint32 timerId){
	if(timers.contains(timerId))
		timers[timerId]->startTime=QTime::currentTime();
}

void setTimerConfig(qint32 timerId, qint32 period, qint32 duration, double restValue, double actionValue){
	if(!timers.contains(timerId))return;
	timer_config *p=timers[timerId];
	p->period=period;
	p->duration=duration;
	p->restValue=restValue;
	p->actionValue=actionValue;
}
