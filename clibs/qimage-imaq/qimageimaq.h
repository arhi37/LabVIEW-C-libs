#ifndef QIMAGEIMAQ_H
#define QIMAGEIMAQ_H

#include <QByteArray>
#include <QImage>
#include <QDataStream>

extern "C" {
	int imagImageToQImage(char *qData, int size, quint32 *iData, int w, int h);
	void qImageToImaqImage(char *qData, int size, quint32 *iData, int *w, int *h);
}

#endif // QIMAGEIMAQ_H
