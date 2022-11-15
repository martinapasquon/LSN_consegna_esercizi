/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"

using namespace std;
 
int main (int argc, char *argv[]){

   Random rnd;
   int seed[4];
   int p1, p2;
   int M=100;             
   int N=1000000;
   int L=(N/M);
   double arr_M[M];
   double arr_rand[N];
   double ni[M];
   double chi_2[M];
   double n=0;
   int k=0;
   double sum1=0;

    for(int i=0; i<N; i++){
     arr_rand[i]=0;
    }
    for(int i=0; i<M; i++){
     arr_M[i]=i/M;
     ni[i]=0;
     chi_2[i]=0;
    }

   ifstream Primes("Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("seed.in");
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            rnd.SetRandom(seed,p1,p2);
         }
      }
      input.close();
   } else cerr << "PROBLEM: Unable to open seed.in" << endl;

   for(int i=0; i<20; i++){
      cout << rnd.Rannyu() << endl;  
   
   }
   for(int i=0; i<N; i++){
      arr_rand[i]=rnd.Rannyu();
      
   }

   rnd.SaveSeed();

   
    for(int i=0; i<M; i++){
       
       for(int j=0; j<L; j++){
         k = j+i*L;
         sum1 += arr_rand[k];
        
       }
    
      ni[i] = sum1/L;     
      n+=ni[i]/M;
      sum1=0;
      
   
    }
   
    for(int i=0; i<M; i++){
        chi_2[i]=pow(ni[i]-(n/M),2);
        chi_2[i]/=(n/M);
      }
      
  ofstream out("chi_quadro.dat");
   for(int i=0; i<M; i++){
      out << chi_2[i]<<endl ;
   }
   out.close();
  

   return 0;
}









