/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
//ESERCIZIO 01.1:
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "random.h"
#include "funzioni.h"

using namespace std;
 
int main (int argc, char *argv[]){

   Random rnd;
   int seed[4]; 
   int M=100000; //# di lanci            
   int N=100;    //# di blocchi 
   int L=(M/N);  // # di lanci in ogni blocco 
   double sum1[N]; //array i cui elementi conterranno ognuno la somma di L numeri random di cui si vogliono trovare la media e l 'errore progressivo
   double arr_rand[M]; //array che conterrà M numeri random nell'intervallo [0,1]
   int k=0;
   int p1, p2;
          
   
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

   for(int i=0; i<M; i++){
      arr_rand[i]=rnd.Rannyu(); //riempio l'array con numeri random 
   }

   rnd.SaveSeed();

   //PRIMO PUNTO ESERCIZIO:
   for(int i=0; i<N; i++){
      sum1[i] = 0; //inizializzo l'array sum1  
         for(int j=0; j<L; j++){
             k = j+i*L;
             sum1[i] += arr_rand[k]; //riempio l'array sum1 con numeri random compresi nell'intervallo (0,1)
         }   
   }
   SumErrProg(M, N, sum1,  "sum_prog.txt"); //funzione che trova media ed errore progressivo e li scrive su file
   //SECONDO PUNTO ESERCIZIO:
   for(int i=0; i<N; i++){
      sum1[i] = 0; //inizializzo l'array sum1  
         for(int j=0; j<L; j++){
             k = j+i*L;
             sum1[i] += pow(arr_rand[k]-0.5,2); //riempio l'array sum1 con i quadrati della differenza tra M numeri random e 0.5 
         }   
   }
    SumErrProg(M, N, sum1,  "sum_pow_prog.txt"); //funzione che trova media ed errore progressivo e li scrive su file

   return 0;
}









