#include "qimageimaq.h"

int imagImageToQImage(char *qData, int size, quint32 *iData, int w, int h){
	QImage img(w, h, QImage::Format_RGB32);

	QByteArray ba;
	QDataStream stream(&ba, QIODevice::WriteOnly);
	stream.setVersion(QDataStream::Qt_4_7);

	for(int i=0;i<w;i++)
		for(int j=0;j<h;j++)
			img.setPixel(i, j, iData[i+j*w]);

//	img.save("1.png");

	stream<<img;

	for(int i=0;i<ba.size();i++)
		qData[i]=ba.data()[i];

	return ba.size();
}

void qImageToImaqImage(char *qData, int size, quint32 *iData, int *w, int *h){
	QImage img;

	QByteArray ba;
	ba.resize(size);

	for(int i=0;i<size;i++)
		ba[i]=qData[i];

	QDataStream stream(ba);

	stream>>img;

	if(*w<img.width() || *h<img.height()){
		*w=0;
		*h=0;
		return;
	}

	int newW=img.width();
	int newH=img.height();

	for(int i=0;i<newW;i++)
		for(int j=0;j<newH;j++)
			iData[i+*w*j]=img.pixel(i, j);

	*w=newW;
	*h=newH;

	return;

}
