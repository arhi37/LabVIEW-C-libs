#include "breakpoint.h"


qint32 BreakPoint(double *Xarr, double *Yarr, qint32 size, double* F, double* point){
	if(size<7)return 0;

	double Mmin=-1;

	double xSr=0.0, ySr=0.0, xySr=0.0, xxSr=0.0;
	double a, b=0.0;
	for(int j=0;j<size;j++){
		b+=Yarr[j];
		xSr+=Xarr[j];
		xySr+=Xarr[j]*Yarr[j];
		xxSr+=Xarr[j]*Xarr[j];
	}

	b/=size;
	ySr=b;
	xSr/=size;
	xxSr/=size;
	xySr/=size;

	a=(xySr-xSr*ySr)/(xxSr-xSr*xSr);

	double S=0.0;

	for(int j=0;j<size;j++)
		S+=(Yarr[j]-(b+a*(Xarr[j]-xSr)))
				*(Yarr[j]-(b+a*(Xarr[j]-xSr)));
	S/=size-2;

	for(int i=3;i<size-3;i++){
		double xSr1=0.0, ySr1=0.0, xySr1=0.0, xxSr1=0.0;
		double a1, b1=0.0;
		for(int j=0;j<i;j++){
			b1+=Yarr[j];
			xSr1+=Xarr[j];
			xySr1+=Xarr[j]*Yarr[j];
			xxSr1+=Xarr[j]*Xarr[j];
		}
		b1/=i;
		ySr1=b1;
		xSr1/=i;
		xxSr1/=i;
		xySr1/=i;

		a1=(xySr1-xSr1*ySr1)/(xxSr1-xSr1*xSr1);

		double S1=0.0;

		for(int j=0;j<i;j++)
			S1+=(Yarr[j]-(b1+a1*(Xarr[j]-xSr1)))
					*(Yarr[j]-(b1+a1*(Xarr[j]-xSr1)));
		S1/=i-2;

		double Sa1, Sb1;

		Sb1=S1/i;
		Sa1=S1/(xxSr1-xSr1*xSr1)/i;

		//////////////////////////////////////////
		double xSr2=0.0, ySr2=0.0, xySr2=0.0, xxSr2=0.0;
		double a2, b2=0.0;
		for(int j=i;j<size;j++){
			b2+=Yarr[j];
			xSr2+=Xarr[j];
			xySr2+=Xarr[j]*Yarr[j];
			xxSr2+=Xarr[j]*Xarr[j];
		}
		b2/=size-i;
		ySr2=b2;
		xSr2/=size-i;
		xxSr2/=size-i;
		xySr2/=size-i;

		a2=(xySr2-xSr2*ySr2)/(xxSr2-xSr2*xSr2);

		double S2=0.0;

		for(int j=i;j<size;j++)
			S2+=(Yarr[j]-(b2+a2*(Xarr[j]-xSr2)))
					*(Yarr[j]-(b2+a2*(Xarr[j]-xSr2)));
		S2/=size-i-2;

		double Sa2, Sb2;

		Sb2=S2/(size-i);
		Sa2=S2/(xxSr2-xSr2*xSr2)/(size-i);


		//////////////////////////////////

		double M=i*S1+(size-i)*S2;

		if(Mmin>M || (Mmin<0 && M>0)){
			Mmin=M;
			//t=fabs(a1-a2)/sqrt(Sa1*Sa1+Sa2*Sa2);
			*F=(S*size)/Mmin;
			*point=Xarr[i];
		}
	}

	return 1;

}
