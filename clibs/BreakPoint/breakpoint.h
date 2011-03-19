#ifndef BREAKPOINT_H
#define BREAKPOINT_H

#include <QtCore>

extern "C"{
	qint32 BreakPoint(double *X, double *Y, qint32 size, double* F, double* point);
}

qint32 BreakPoint(double *X, double *Y, qint32 size, double* F, double* point);

#endif // BREAKPOINT_H
