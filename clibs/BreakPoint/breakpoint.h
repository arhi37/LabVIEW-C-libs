#ifndef BREAKPOINT_H
#define BREAKPOINT_H

#include <QtCore>

extern "C"{
	qint32 BreakPoint(double *X, double *Y, qint32 size, double* F, double* point,
					  double searchMin, double searchMax);
}

qint32 BreakPoint(double *X, double *Y, qint32 size, double* F, double* point,
				  double searchMin, double searchMax);

#endif // BREAKPOINT_H
