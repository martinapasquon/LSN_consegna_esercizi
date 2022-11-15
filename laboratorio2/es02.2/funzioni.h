#include <iostream>
#include <fstream> 
#include <iomanip> 
#include <vector>
#include <string>
#include "random.h"

using namespace std;

// =====================================================================
template <typename T> void Print( const vector<T> & v ) {
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
 
};


void SumErrProg (int  M, int N, double* sum1, const char* filename){

   double sum_prog[N]; //media progressiva
   double sum2_prog[N]; //media progressiva dei quadrati
   double err_prog[N]; //errore progressivo
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
      ave[i] = sqrt(sum1[i])/L; //ogni elemento di sum1 è stato riempito con L numeri random. Qui calcolo la media degli L numeri random per ogni blocco      
      av2[i] = pow((ave[i]),2);  
    }

    for(int i=0; i<N; i++){
      for(int j=0; j<i+1; j++){
        sum_prog[i] += ave[j];
        sum2_prog[i] += av2[j];
      }
      sum_prog[i]/=(i+1); //media progressiva
      sum2_prog[i]/=(i+1);//media progressiva dei quadrati
      err_prog[0]=0;//l'errore sul primo blocco infatti non è calcolabile
      
      if (i!=0){ 
        err_prog[i] = sqrt((sum2_prog[i] - pow(sum_prog[i],2))/i); 
      }
    }
    ofstream out(filename);
    for(int i=0; i<N; i++){
      out << sum_prog[i]<< " " << err_prog[i] << endl ;
    }
   out.close();
}




