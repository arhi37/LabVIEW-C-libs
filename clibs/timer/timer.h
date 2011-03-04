#ifndef TIMER_H
#define TIMER_H

#include <QtCore>
#include <QMap>
#include <QTime>

struct timer_config{
	QTime startTime;
	qint32 period;
	qint32 duration;
	bool isStarted;
	double restValue;
	double actionValue;

	timer_config(){
		isStarted=false;
		period=60000;
		duration=5000;
		restValue=0.0;
		actionValue=1.0;
	}
};

QMap<qint32, timer_config> timers;

extern "C" {
	void setPeriod(qint32 timerId, qint32 period);
	void setDuration(qint32 timerId, qint32 duration);
	void setRestValue(qint32 timerId, double restValue);
	void setActionValue(qint32 timerId, double actionValue);
	double getValue(qint32 timerId);
	void startTimer(qint32 timerId);
	void resetTimer(qint32 timerId);
	void setTimerConfig(qint32 timerId, qint32 period, qint32 duration, double restValue, double actionValue);
	void removeTimer(qint32 timerId);
}

void setPeriod(qint32 timerId, qint32 period);
void setDuration(qint32 timerId, qint32 duration);
void setRestValue(qint32 timerId, double restValue);
void setActionValue(qint32 timerId, double actionValue);
double getValue(qint32 timerId);
void startTimer(qint32 timerId);
void resetTimer(qint32 timerId);
void setTimerConfig(qint32 timerId, qint32 period, qint32 duration, double restValue, double actionValue);
void removeTimer(qint32 timerId);

#endif // TIMER_H
