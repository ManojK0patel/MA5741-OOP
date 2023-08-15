#ifndef VECTOR_H
#define VECTOR_H
#include<iostream>
using namespace std;
class Vector{
private: 
    double *v;
    int size;
public:
    Vector();
    Vector(int size);
    void print();
    int getSize();
    double& operator [](int);
};

Vector :: Vector(){
    this->size = 0;
}

Vector :: Vector(int size){
    this->size = size;
    this->v = new double[size];
}

void Vector :: print(){
    for(int i = 0; i<this->size ; i++)
       cout<< this->v[i] << "\t";
    cout<<"\n"<<endl;
}

int Vector :: getSize(){
    return this->size;
}

double& Vector :: operator [](int index){
    return this->v[index];
}

#endif










