#ifndef PARETO_H
#define PARETO_H

#include <QtCore>

struct pareto_config{
	QList<double>	list;
	QList<double>	logList;
	double	min;
	int size;
};

static QList<double> numLogList;

static QMap<qint32, pareto_config*>	paretoMap;

extern "C"{
	qint32 initPareto();
	void removePareto(qint32 paretoId);
	qint32 getParetoSize(qint32 paretoId);
	qint32 addData(qint32 paretoId, double* data, qint32 size);
	qint32 getPareto(qint32 paretoId, double* countArray, double* numArray, qint32 arraysSize);
	void resetData(qint32 paretoId);
}

#endif // PARETO_H
