#ifndef MOVINGAVERAGE_H
#define MOVINGAVERAGE_H

#include <QtCore>
#include <QMap>

class movingAverage{

	qint32 m_period;
	double *array;
	qint32 pointer;

public:
	movingAverage();
	~movingAverage();

	void addPoint(double point);
	double getValue();
	void setPeriod(qint32	period);
	void reset(double count/* = 0*/);

};


static QMap<qint32, movingAverage*>	movAvMap;

extern "C" {
	qint32 initMovingAverage();
	void removeMovingAverage(qint32 movAvId);
	void addPoint(qint32 movAvId, double point);
	double getValue(qint32 movAvId);
	void setPeriod(qint32 movAvId, qint32	period);
	void reset(qint32 movAvId, double count/* = 0*/);
}

#endif // MOVINGAVERAGE_H
