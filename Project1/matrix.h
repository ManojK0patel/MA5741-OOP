#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
using namespace std;
class matrix{
  private:
          double **M;
          int num_row, num_col;
public:
    matrix();
    matrix(int, int);
    double& operator ()(int, int);
    void operator ()(int, int, double);
    void print();
};

matrix :: matrix(){
    num_row = 0;
    num_col = 0;
}

matrix :: matrix(int rows, int cols){
    this->num_row = rows;
    this->num_col = cols;
    M = new double *[this->num_row];
    for(int i=0 ; i<this->num_col ; i++)
     M[i] = new double[this->num_col];
}

void matrix :: print(){
    for(int i = 0;i<this->num_row ;i++){
    for(int j=0 ; j<this->num_col ; j++){
        cout << this->M[i][j] <<"\t";
    }
    cout<<endl;
    }
}

double& matrix :: operator()(int row, int col){
    if(row < this-> num_row && col < this->num_col)
    return this->M[row][col];
    else{
        cout<<"ERROR: Out of bound"<<endl;
        exit(0);
    }
}

void matrix :: operator ()(int row, int col, double value){
    this->M[row][col] = value;
}

#endif

