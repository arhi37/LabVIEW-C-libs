#include "timer.h"


void setPeriod(qint32 timerId, qint32 period){
		timers[timerId].period=period;
}

void setDuration(qint32 timerId, qint32 duration){
		timers[timerId].duration=duration;
}

void setRestValue(qint32 timerId, double restValue){
		timers[timerId].restValue=restValue;
}

void setActionValue(qint32 timerId, double actionValue){
		timers[timerId].actionValue=actionValue;
}

double getValue(qint32 timerId){
	if(!timers.contains(timerId) || !timers[timerId].isStarted)
		return 0.0;

	timer_config *buf=&timers[timerId];
	qint32	msec=buf->startTime.msecsTo(QTime::currentTime());
	if(msec%(buf->period) > (buf->period - buf->duration))
		return buf->actionValue;
	else return buf->restValue;
}

void startTimer(qint32 timerId){
		timers[timerId].startTime=QTime::currentTime();
		timers[timerId].isStarted=true;
}

void resetTimer(qint32 timerId){
		timers[timerId].startTime=QTime::currentTime();
}

void setTimerConfig(qint32 timerId, qint32 period, qint32 duration, double restValue, double actionValue){
	timer_config *buf=&timers[timerId];
	buf->period=period;
	buf->duration=duration;
	buf->restValue=restValue;
	buf->actionValue=actionValue;
}

void removeTimer(qint32 timerId){
	if(timers.contains(timerId))timers.remove(timerId);
}
