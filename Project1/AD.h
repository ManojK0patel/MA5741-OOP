#ifndef AD_H
#define AD_H
#include<cmath>
#include "Vector.h"
#include "matrix.h"

int varCount = 0; // to keep track number of independent variables used.

class AD{
private:
    double f;
    Vector df;
    int id;
    
public:
    AD();
    AD(double);
    void setIndVar();
    double getf();
    double getDf(int);
    Vector getGradient();
    friend matrix getJacobian(AD*);
    
    AD operator *(AD);
    AD operator +(AD);
    //AD operator*(double);
   	AD operator-(AD);
	AD operator/(AD);
	AD operator^(AD); // f^g
	
 	template<class U>
	AD operator^(U); // f^c
	template<class U>
	AD operator+(U);
	template<class U>
	AD operator-(U);
	template<class U>
	AD operator*(U);
	template<class U>
	AD operator/(U);
	// c+f, c-f, c*f, c/f, c^f.
	template<class U>
	friend AD operator+(U,AD);
	

	template<class U>
	friend AD operator-(U,AD);

	template<class U>
	friend AD operator*(U,AD);

	template<class U>
	friend AD operator/(U,AD);

	template<class U>
	friend AD operator^(U,AD);
	

	// sin(f), cos(f), tan(f), cosec(f), sec(f), cot(f).
	// arcsin(f), arccos(f), arctan(f), sinh(f), cosh(f), tanh(f).
	// log(f), exp(f), abs(f)
	
	
	friend AD sin(AD);


	friend AD cos(AD);

	
	friend AD tan(AD);



	friend AD cosec(AD);


	friend AD sec(AD);


	friend AD cot(AD);

	
	friend AD arcsin(AD);

	friend AD arccos(AD);


	friend AD arctan(AD);


	friend AD sinh(AD);


	friend AD cosh(AD);


	friend AD tanh(AD);


	friend AD log(AD);


	friend AD exp(AD);


	friend AD abs(AD);
    
};



AD :: AD(){
    f = 0;
}

AD :: AD(double value){
    this->f = value;
    this->id = varCount;
    varCount++;
}

void AD :: setIndVar(){
    this->df = Vector(varCount);
    for(int i=0 ; i<this->id ; i++)
        this->df[i] = 0;
    this->df[this->id] =  1;
    for(int i = this->id + 1 ; i < varCount ;i++)
        this->df[i] = 0;
}

double AD :: getf(){
   return this->f;
}
double AD :: getDf(int index){
    return df[index];
}

Vector AD :: getGradient(){
    Vector gradient(varCount);
    for(int i=0 ;i<varCount;i++)
        gradient[i] = this->df[i];
    return gradient;    
}

matrix getJacobian(AD funList[]){
    int n = varCount;
    matrix M = matrix(n,n);

      for(int i = 0; i<n ; i++)
      for(int j = 0 ; j< n ; j++)
         M(i,j) = round(funList[i].getDf(j)*10000)/10000;
    return M;     
}

//Binary operators
//f+g
AD AD :: operator +(AD g){
    AD h;
    h.f = this->f + g.f;
    h.df = Vector(varCount);
    for(int i = 0 ;i<varCount ;i++)
      h.df[i] = this->df[i] + g.df[i];
    return h;  
}
//f*g
AD AD :: operator *(AD g){
    AD h;
    h.f = this-> f * g.f;
    h.df = Vector(varCount);
    for(int i = 0 ; i <varCount ;i++)
        h.df[i] = (this->f * g.df[i]  + g.f * this->df[i]);
    return h;    
}
//f-g
AD AD::operator-(AD g){
    AD h;
    h.f = this->f - g.f;
    h.df = Vector(varCount);
    for(int i = 0 ;i<varCount ;i++)
      h.df[i] = this->df[i] - g.df[i];
    return h;
};
//f/g
AD	AD:: operator/(AD g){
    AD h;
    h.f = this-> f/g.f;
    h.df = Vector(varCount);
    for(int i = 0 ; i <varCount ;i++)
        h.df[i] = ((this->df[i] * g.f - this->f *g.df[i])/(g.f*g.f));
    return h; 
};
 // f^g
 AD AD:: operator^(AD g){
    AD h;
    h.f=pow(this->f,g.f);
    h.df=Vector(varCount);
    for(int i=0;i<varCount;i++)
      h.df[i]=h.f*((g.f*this->df[i])/(this->f)+g.df[i]*log(this->f));
    return h;  
 }
//f*s
template<class U>
AD AD :: operator *(U s){
    AD h;
    h.f = s*(this->f);
    h.df = Vector(varCount);
    for(int i = 0; i<varCount ;i++)
        h.df[i] = s*this->df[i];
    return h;    
}
// f^c
   template<class U>
   AD AD:: operator^(U c){
    AD h;
    h.f=pow(this->f,c);
    h.df=Vector(varCount);
      for(int i=0;i<varCount;i++)
         h.df[i]=c*pow(this->f,c)*this->df[i];
    return h;     
}
//f+s
template<class U>
AD	AD:: operator+(U s){
    AD h;
    h.f = s+(this->f);
    h.df = Vector(varCount);
    for(int i = 0; i<varCount ;i++)
        h.df[i] = this->df[i];
    return h;  
}
//f-s
template<class U>
AD	AD:: operator-(U s){
    AD h;
    h.f = s-(this->f);
    h.df = Vector(varCount);
    for(int i = 0; i<varCount ;i++)
        h.df[i] = this->df[i];
    return h;  
}
//f/s
template<class U>
AD	AD:: operator/(U s){
    AD h;
    h.f = (this->f)/s;
    h.df = Vector(varCount);
    for(int i = 0; i<varCount ;i++)
        h.df[i] = this->df[i]/s;
    return h;  
}


template<class U>
 AD operator+(U s,AD f){
	   AD h;
	   h.f=f.f+s;
	   h.df=f.df;
	 return h;  
 }
	

template<class U>
 AD operator-(U s,AD f){
     AD h;
	   h.f=s-f.f;
	   h.df = Vector(varCount);
    for(int i = 0; i<varCount ;i++)
        h.df[i] = -f.df[i];
    return h; 
 }

template<class U>
AD operator*(U s,AD f){
  AD h;
  h.f=s*f.f;
  h.df=Vector(varCount);
  for(int i=0;i<varCount;i++)
      h.df[i]=s*f.df[i];
 return h;      
}

template<class U>
AD operator/(U s,AD f){
   AD h;
  h.f=s/f.f;
  h.df=Vector(varCount);
  for(int i=0;i<varCount;i++)
      h.df[i]=-(s*f.df[i])/(f.f*f.f);
 return h; 
}

template<class U>
AD operator^(U s,AD f){
    AD h;
    h.f=pow(s,f.f);
    h.df=Vector(varCount);
    for(int i=0;i<varCount;i++)
        h.df[i]=(f.df[i])*(h.f)*(log(s));
  return h;
}


AD sin(AD g){
    AD h;
    h.f = sin(g.f);
    h.df = Vector(varCount);
    for(int i=0 ;i < varCount ; i++)
        h.df[i] = cos(g.f)*g.df[i];
    return h;    
}

AD cos(AD g){
    AD h;
    h.f = cos(g.f);
    h.df = Vector(varCount);
    for(int i=0 ;i < varCount ; i++)
        h.df[i] = -sin(g.f)*g.df[i];
    return h;    
}
AD tan(AD g){
   AD h;
    h.f=tan(g.f);
    h.df=Vector(varCount);
    for(int i=0;i<varCount;i++)
      h.df[i]=(1/pow(cos(g.f),2))*g.df[i];
  return h; 
}
AD cosec(AD g){
    AD h;
    h.f=1/sin(g.f);
    h.df=Vector(varCount);
    for(int i=0;i<varCount;i++)
       h.df[i]=-(1/tan(g.f))*h.f*g.df[i];
  return h;  
}


AD sec(AD g){
    AD h;
    h.f=1/cos(g.f);
    h.df=Vector(varCount);
    for(int i=0;i<varCount;i++)
      h.df[i]=tan(g.f)*h.f*g.df[i];
return h;
}
AD cot(AD g){
    AD h;
    h.f=1/tan(g.f);
    h.df=Vector(varCount);
    for(int i=0;i<varCount;i++)
     h.df[i]=-pow(1/sin(g.f),2)*g.df[i];
  return h;    
}
AD arcsin(AD g){
    AD h;
    h.f=asin(g.f);
    h.df=Vector(varCount);
    for(int i=0;i<varCount;i++)
      h.df[i]=(1/sqrt(1-pow(g.f,2)))*g.df[i];
  return h;
}
AD arccos(AD g){
    AD h;
    h.f=acos(g.f);
    h.df=Vector(varCount);
    for(int i=0;i<varCount;i++)
      h.df[i]=-(1/sqrt(1-g.f*g.f))*g.df[i];
  return h;
}
AD arctan(AD g){
    AD h;
    h.f=atan(g.f);
    h.df=Vector(varCount);
    for(int i=0;i<varCount;i++)
     h.df[i]=(1/(1+g.f*g.f))*g.df[i];
   return h;
}
AD sinh(AD g){
    AD h;
    h.f=sinh(g.f);
    h.df=Vector(varCount);
    for(int i=0;i<varCount;i++)
     h.df[i]=cosh(g.f)*g.df[i];
   return h;    
}
AD cosh(AD g){
    AD h;
    h.f=cosh(g.f);
    h.df=Vector(varCount);
    for(int i=0;i<varCount;i++)
     h.df[i]=sinh(g.f)*g.df[i];
   return h; 
}
AD tanh(AD g){
    AD h;
    h.f=tanh(g.f);
    h.df=Vector(varCount);
    for(int i=0;i<varCount;i++)
     h.df[i]=(1/pow(cosh(g.f),2))*g.df[i];
 return h;
}
AD log(AD g){
     AD h;
    h.f=log(g.f);
    h.df=Vector(varCount);
    for(int i=0;i<varCount;i++)
     h.df[i]=(1/g.f)*g.df[i];
   return h;    
}
AD exp(AD g){
    AD h;
    h.f=exp(g.f);
    h.df=Vector(varCount);
    for(int i=0;i<varCount;i++)
     h.df[i]=h.f*g.df[i];
  return h;
}
AD abs(AD g){
    AD h;
     h.f=abs(g.f);
     h.df=Vector(varCount);
    for(int i=0;i<varCount;i++){
      if(g.f<0)
      h.df[i]=-g.df[i];
     else 
      h.df[i]=g.df[i];
    }
    return h;
}



#endif
