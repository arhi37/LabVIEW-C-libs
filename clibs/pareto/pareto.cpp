#include "pareto.h"
#include <cmath>

qint32 initPareto(){
	qint32 id;
	int flag=0;
	do{
		id=qrand()+1;
		flag++;
	}while(paretoMap.contains(id) && flag<10000);

	if(flag>=10000)return 0;
	else {
		paretoMap.insert(id, new pareto_config);
		paretoMap[id]->size=0;
		return id;
	}
}

void removePareto(qint32 paretoId){
	if(!paretoMap.contains(paretoId))return;
	delete paretoMap[paretoId];
	paretoMap.remove(paretoId);
}

qint32 getParetoSize(qint32 paretoId){
	if(!paretoMap.contains(paretoId))return 0;
	return paretoMap[paretoId]->size;
}

qint32 addData(qint32 paretoId, double* data, qint32 size){
	if(!paretoMap.contains(paretoId) || size<=0)return 0;

	pareto_config*	pareto=paretoMap[paretoId];

	QVector<double>	vData;
	vData.resize(size);
	bool minChange=false;
	double localMin=data[0];

	for(int i=0;i<size;i++){
		if(data[i]<=0)return 0;
		vData[i]==data[i];
		if(data[i]<localMin)
			localMin=data[i];
	}

	if(pareto->min>localMin || pareto->size==0)
		minChange=true;

	pareto->list<<vData.toList();
	pareto->size+=size;

	if(minChange){
		pareto->min=localMin;
		qSort(pareto->list.begin(), pareto->list.end(), qGreater<double>());
		pareto->logList.clear();
		QListIterator<double> listIt(pareto->list);
		while(listIt.hasNext())
			pareto->logList<<log10(listIt.next()/localMin);

	}else{
		for(int i=0;i<size;i++)
			pareto->logList<<log10(vData[i]/pareto->min);
		qSort(pareto->logList.begin(), pareto->logList.end(), qGreater<double>());
	}

	if(pareto->size>numLogList.size())
		for(int i=numLogList.size();i<pareto->size;i++)
			numLogList<<log10(i+1);

	return pareto->size;

}

qint32 getPareto(qint32 paretoId, double* countArray, double* numArray, qint32 arraysSize){
	if(!paretoMap.contains(paretoId))return 0;
	if(paretoMap[paretoId]->size>arraysSize)return 0;

	pareto_config*	pareto=paretoMap[paretoId];

	QListIterator<double>	numLogListIt(numLogList);
	QListIterator<double>	logListIt(pareto->logList);
	for(int i=pareto->size-1;i>=0;--i){
		numArray[i]=numLogListIt.next();
		countArray[i]=logListIt.next();
	}

	return 1;
}

void resetData(qint32 paretoId){
	if(!paretoMap.contains(paretoId))return;
	paretoMap[paretoId]->size=0;
	paretoMap[paretoId]->list.clear();
	paretoMap[paretoId]->logList.clear();
}
