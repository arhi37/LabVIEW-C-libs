#include "movingaverage.h"


movingAverage::movingAverage(){
	m_period=5;
	array=new double[m_period];
	for(int i=0;i<m_period;i++)array[i]=0;
	pointer=0;
}

movingAverage::~movingAverage(){
	delete array;
}

void movingAverage::addPoint(double point){
	array[pointer]=point/m_period;
	pointer++;
	if(pointer>=m_period)pointer=0;
}

double movingAverage::getValue(){
	double sum=0.0;
	for(int i=0;i<m_period;i++)sum+=array[i];
	return sum;
}

void movingAverage::setPeriod(qint32	period){
	if(period<1)return;

	double val=this->getValue();
	m_period=period;
	delete array;

	array=new double[m_period];
	for(int i=0;i<m_period;i++)array[i]=val;
	pointer=0;
}

void movingAverage::reset(double value = 0){
	for(int i=0;i<m_period;i++)array[i]=value;
}


qint32 initMovingAverage(){
	qint32 id;
	int flag=0;
	do{
		id=qrand()+1;
		flag++;
	}while(movAvMap.contains(id) && flag<10000);

	if(flag>=10000)return 0;
	else {
		movAvMap.insert(id, new movingAverage);
		return id;
	}
}

void removeMovingAverage(qint32 movAvId){
	if(!movAvMap.contains(movAvId))return;
	delete movAvMap[movAvId];
	movAvMap.remove(movAvId);
}

void addPoint(qint32 movAvId, double point){
	if(!movAvMap.contains(movAvId))return;
	movAvMap[movAvId]->addPoint(point);
}

double getValue(qint32 movAvId){
	if(!movAvMap.contains(movAvId))return 0.0;
	return movAvMap[movAvId]->getValue();

}

void setPeriod(qint32 movAvId, qint32	period){
	if(!movAvMap.contains(movAvId))return;
	movAvMap[movAvId]->setPeriod(period);
}

void reset(qint32 movAvId, double count = 0){
	if(!movAvMap.contains(movAvId))return;
	movAvMap[movAvId]->reset(count);
}
