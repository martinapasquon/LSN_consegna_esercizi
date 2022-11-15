#include <iostream>
#include <fstream> 
#include <iomanip> 
#include <vector>
#include <string>
#include <cmath>

using namespace std;

// =====================================================================

template <typename T> void Print( const vector<T> & v ) {
  for (unsigned int i=0; i<v.size(); i++) cout << v[i] << endl;
};


template <typename T> void Print( const vector<T> & v  , string filename ) {                                                                            

 ofstream out(filename);
 for(unsigned int i=0; i<v.size(); i++)
   out << v[i] << endl;
 out.close();

};

// =====================================================================

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

// =====================================================================

template <typename T> double CalcolaMedia( const vector<T> & v) {

 T accumulo = 0;
  for ( int k = 0 ; k < v.size() ; k++ ) { 
    accumulo += v[k] ;
  }
  
  return accumulo / ( v.size() ) ;
  



};

template <typename T> double CalcolaStdev( const vector<T> & v, T mean) {

 T accumulo = 0;
  for ( int k = 0 ; k < v.size() ; k++ ) { 
    accumulo += pow((v[k]-mean),2) ;
  }
    accumulo =sqrt(accumulo/v.size());
  return accumulo / ( v.size() ) ;
  



};
template <typename T> double CalcolaMediana( vector<T> v ) {

   sort( v.begin(), v.end() ) ;  
  double mediana;

  
 if(v.size()%2==0){
    mediana=(v[v.size()/2 -1] +v[v.size()/2]/2.);
 }
 else{
     mediana=v[v.size()/2];
   }
   
  return mediana;


};


