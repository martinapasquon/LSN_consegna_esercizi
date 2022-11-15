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
   int M=100000;             
   int N=100;               
   int L=(M/N);           
   double ave[N];
   double  av2[N];
   double sum_prog[N];
   double sum2_prog[N];
   double err_prog[N];
   double arr_rand[M];
   double sum1=0;
   int k=0;
   for(int i=0; i<N; i++){
     ave[i]=0;
     av2[i]=0;
     sum_prog[i]=0;
     sum2_prog[i]=0;
     err_prog[i]=0;
    }
    for(int i=0; i<M; i++){
     arr_rand[i]=0;
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
   for(int i=0; i<M; i++){
      arr_rand[i]=rnd.Rannyu();
   }

   rnd.SaveSeed();

   

    for(int i=0; i<N; i++){
      sum1 = 0;   
       for(int j=0; j<L; j++){
         k = j+i*L;
         sum1 += arr_rand[k];
       }
    
      ave[i] = sum1/L;     
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
    cout << sum_prog[i] << "   " << sum2_prog[i] <<"   "<< err_prog[i]<<endl;
    }
  ofstream out("sum_prog.txt");
   for(int i=0; i<N; i++){
      out << sum_prog[i]<< " " << err_prog[i] << endl ;
   }
   out.close();
  
   



   
   return 0;
}









