/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
//ESERCIZIO01.3
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
   int p1, p2;
   int M=100000; //# di lanci            
   int N=100;    //# di blocchi 
   int L=(M/N);  // # di lanci in ogni blocco 
   double l=0.3;//lunghezza dell'ago
   double d=1; //distanza tra le due righe del foglio         
   double a=0; //seno dell'angolo con cui cade l'ago
   double b1=0; //posizione di un estremo dell'ago
   double b2=0; //posizione dell'altro estremo dell'ago
   double pos=0; //posizione del baricentro dell'ago
   double  N_hit[N]; //array che contiene il numero di volte in cui l'ago cade su una riga per ogni blocco N;
   for(int i=0; i<N; i++){ //inizializzazione
     N_hit[i]=0;
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


    for(int i=0; i<N; i++){
       for(int j=0; j<L; j++){
          a=sin(rnd.theta()); //theta angolo casuale compreso in (0, PI)
          pos=rnd.Rannyu(); //posizione del baricentro dell'ago: posizione random tra due righe. Poichè d=1, la posizione del baricentro è un numero random tra 0 e 1
          //estratto da una distribuzione uniforme.
          b1 =pos + a*l*0.5; //posizione di un estremo dell'ago
          b2 =pos - a*l*0.5; //posizione dell'altro estremo dell'ago
          if (b1>=d or b2<=0){ //se l'ago cade su una riga viene incrementato N_hit
             N_hit[i]++;
          }
      }
   } 
   rnd.SaveSeed();
   SumErrProg(M, N, N_hit, l, d,   "sum_prog.txt"); //funzione che trova media ed errore progressivo e li scrive su file
     
   
   return 0;
}









