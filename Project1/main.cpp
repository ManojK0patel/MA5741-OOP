#include<bits/stdc++.h>
#include "AD.h"
using namespace std;
#define max 500

class charStack{
    private: 
      char elements[max];
      int maxCapacity = max;
      int top;
    public:
      charStack();
      bool isEmpty();
      bool isFull();
      void push(char);
      char pop();
      char getTop();
};
class doubleStack{
    private: 
      double elements[max];
      int maxCapacity = max;
      int top;
    public:
      doubleStack();
      bool isEmpty();
      bool isFull();
      void push(double);
      double pop();
      double getTop();
      int getTopIndex();
};
charStack :: charStack(){
    top = -1;
}

bool charStack :: isEmpty(){
    if(top == -1)
        return true;
    else
        return false;
}

bool charStack :: isFull(){
    if(top == maxCapacity - 1)
        return true;
    else
        return false;
}

void charStack :: push(char ch){
    if(isFull())
        cout << "\nStack is full"<<endl;
    else{
        top++;
        elements[top] = ch;
    }
}

char charStack :: pop(){
    char ch;
    if(isEmpty())
        cout << "\nStack is empty"<<endl;
    else{
        ch = elements[top];
        top--;
    }
    return ch;
}

char charStack :: getTop(){
    char ch;
    if(isEmpty())
        cout << "\nStack is empty"<<endl;
    else{
        ch = elements[top];
    }
    return ch;
}
doubleStack :: doubleStack(){
    top = -1;
}

bool doubleStack :: isEmpty(){
    if(top == -1)
        return true;
    else
        return false;
}

bool doubleStack :: isFull(){
    if(top == maxCapacity - 1)
        return true;
    else
        return false;
}

void doubleStack :: push(double ch){
    if(isFull())
        cout << "\nStack is full"<<endl;
    else{
        top++;
        elements[top] = ch;
    }
}

double doubleStack :: pop(){
    double ch;
    if(isEmpty())
        cout << "\nStack is empty"<<endl;
    else{
        ch = elements[top];
        top--;
    }
    return ch;
}

double doubleStack :: getTop(){
    double ch;
    if(isEmpty())
        cout << "\nStack is empty"<<endl;
    else{
        ch = elements[top];
    }
    return ch;
}
int doubleStack :: getTopIndex(){
    return this->top;
}


int main(){
   int n;//Number of independent variable
   cin>>n;
   char IDPV[n];
   for(int i=0;i<n;i++){
     cin>>IDPV[i];
   }
   double values[n];
   for(int i=0;i<n;i++){
    cin>>values[i];
   }
   char functions[n][max];
   for(int i=0;i<n;i++){
    cin>>functions[i];
   }
 AD x(3),y(8),z(-1),u(0);
 AD f,g,h;
 x.setIndVar();
 y.setIndVar();
 z.setIndVar();
 u.setIndVar();
 h=x+y+z+u;
 //f=x*y*z+sin(x*y)*2+x*y*cos(z);
 //h=1.4-x*y+y*z+z*x+(x^2)+2-3.4;
// cout<<h.getDf(0);
//  g=(x*x)+(y*y)+(z*z+x*y*z)+(y^2);
//  h=x*y+y*z+z*x;
 AD func_arr[]={h};
 
 matrix M;
 M=getJacobian(func_arr);
//  for(int i=0;i<3;i++){
//      M(0,i,(round(f.getDf(i)*10000))/10000);
//  }
//  for(int i=0;i<3;i++){
//      M(1,i,g.getDf(i));
//  }
//  for(int i=0;i<3;i++){
//      M(2,i,h.getDf(i));
//  }
M.print();
return 0;
}

