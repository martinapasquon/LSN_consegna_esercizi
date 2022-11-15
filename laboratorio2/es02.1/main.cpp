/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
//ESERCIZIO 02.1:
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <string>
#include "random.h"
#include "funzioni.h"

using namespace std;
 
int main (int argc, char *argv[]){

   Random rnd;
   int seed[4];
   int p1, p2;
   int M=100000;  //numero di lanci          
   int N=200;    //numero di blocchi         
   int L=(M/N);  // numero di lanci in ogni blocco          
   double sum1[N];
   double x=0; 

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


   rnd.SaveSeed();

   for(int i=0; i<N; i++){
     sum1[i]=0;   
      for(int j=0; j<L; j++){
         sum1[i]+=M_PI*0.5*cos(M_PI*rnd.Rannyu()/2);  //riempio il vettore sum1 con la somma dei valori della fuzione da integrare valutata in x numero random estratto da una distribuzione uniforme nell'intervallo (0,1)
      }
  }
  SumErrProg (M,N, sum1, "int_prog.txt");

for(int i=0; i<N; i++){
      sum1[i] = 0;   
       for(int j=0; j<L; j++){
         x=rnd.non_unif();
         sum1[i]+=M_PI*0.5*cos(M_PI*x/2)*1/(-2*x +2); //riempio il vettore sum1 con la somma dei valori della fuzione da integrare valutata in x numero random estratto da una distribuzione non uniforme nell'intervallo (0,1)
         //moltiplicata per la distribuzione uniforme valutata in x(=1) e divisa per la distibuzione non uniforme valutata in x
       if (i<5)
       cout << x << "  "<< 1/(-x*x +2*x) << endl;
       }

}
SumErrProg (M,N, sum1, "int_prog2.txt");
    
   return 0;
}









