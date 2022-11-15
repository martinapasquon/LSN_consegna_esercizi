#include <iostream>
#include <fstream> 
#include <iomanip> 
#include <vector>
#include <string>
#include "random.h"

using namespace std;
Random rnd;
// =====================================================================
/*template <typename T> void Print( const vector<T> & v ) {
  for (unsigned int i=0; i<v.size(); i++) cout << v[i] << endl;
};

template <typename T> void Print( const vector<T> & v  , string filename ) {                                                                            

 ofstream out(filename);
 for(int i=0; i<v.size(); i++)
   out << v[i] << endl;
 out.close();

};
template <typename T> vector<T> Read( unsigned int N, char* filename ) {

  vector<T> v(N);
  ifstream in(filename);
  //assert(in && "Input file non esistente ");
  if(!in){
  cout << "problema con apertura file " << filename <<"  esco!"<< endl;
   exit(11);
  }
  else{
    for(int i=0; i<N; i++){
      T a;
      in>> a;
      v[i]= a;
      //assert ( !(in.eof()) && "lettura file terminata ");
      if (in.eof()){
        cout << "è stata raggiunta la fine del file, esco!"<< endl;
        exit(11);
      }
    }
  }

  return v;  

};

template <typename T> vector<T> ReadAll( const char* filename ) {

 vector<T> v;
  ifstream in(filename);
  //assert(in && "Input file non esistente ");
  if(!in){
  cout << "problema con apertra file " << filename <<"  esco!"<< endl;
   exit(11);
  }
  else{
     while(!in.eof()){ 
      T a;
      in>> a;
      v.push_back(a);
      //assert ( !(in.eof()) && "lettura file terminata ");
      
    };
  };
  
  return v;  
 
};*/
double  S(double S_0,double t, double mean, double gauss, double sigma){
   double S;
   S=S_0*exp((mean-0.5*pow(sigma,2))*(t) + sigma*gauss*sqrt(t));
   
return S;
};

void SumErrProg (int  M, int N, double* sum1, const char* filename){

   double sum_prog[N];
   double sum2_prog[N];
   double err_prog[N];
   double ave[N];
   double av2[N];
   int L=(M/N);           
   for(int i=0; i<N; i++){ //inizializzo gli array
     ave[i]=0;
     av2[i]=0;
     sum_prog[i]=0;
     sum2_prog[i]=0;
     err_prog[i]=0;
   }

    for(int i=0; i<N; i++){
      ave[i] = sum1[i]/L;     
      av2[i] = pow((ave[i]),2);  
    }

    for(int i=0; i<N; i++){
      for(int j=0; j<i+1; j++){
        sum_prog[i] += ave[j];
        sum2_prog[i] += av2[j];
      }
      sum_prog[i]/=(i+1);
      sum2_prog[i]/=(i+1);
      err_prog[0]=0;
      
      if (i!=0){
        err_prog[i] = sqrt((sum2_prog[i] - pow(sum_prog[i],2))/i); 
      }
    }
    ofstream out(filename);
    for(int i=0; i<N; i++){
      out << sum_prog[i]<< " " << err_prog[i] << endl ;
    }
   out.close();
};




