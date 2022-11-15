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
   int M=100;   //# of intervals          
   int n=10000; //# of throws
   double n_i=0; //# di successi in n prove (numero di volte in cui n numeri random tra 0 e 1 sono contenuti in ognuno degli M intervalli in cui viene diviso equamente l'intervallo (0,1))
   double v[M]; //vettore che contiene gli estremi degli M intervalli in cui viene diviso l'intervallo (0,1)
   double random=0; // numero random nell'intervallo (0,1)
   int square[M]; //quadrato della differenza tra il valore osservato (n_i) e quello atteso (n*M)
   double chi_2=0;
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
   //salvo in v[j] l'estremo sinistro di ognuno degli M intervalli
   for(int j=0; j<M; j++){
      v[j]=(double)j/M; 
   }


   ofstream out("chi_quadro.txt");
   if (out.is_open()){
     for(int l=0; l<M; l++){ 
        chi_2=0;  //inizializzo chi_2 all'inizio di ogni ciclo      
        for(int j=0; j<M; j++){
            n_i=0; //inizializzo n_i all'inizio di ogni ciclo 
             for(int i=0; i<n; i++){
                random= rnd.Rannyu();
                if (j==M-1){ // v[] contiene solo l'estremo sinistro dell'intervallo e perciò non contiene l'estremo destro dell'M-esimo intervallo. Aggiungo manulamente tale estremo
                    if (random >v[j])   n_i++; //se random appartiene all' M-esimo intervallo incremento il numero di successi      
                }
                else { 
                    if (random >v[j] and random <v[j+1])   n_i++; //se random appartiene al j-esimo intervallo incremento il numero di successi
                }
             }

            square[j]=pow(n_i-(n/M),2); 
          
        }
        for(int j=0; j<M; j++){
          chi_2+=square[j];
        } 
        chi_2/=(n/M);
        out << chi_2 << endl; }
   }else cerr << "PROBLEM: Unable to open Primes" << endl;
   out.close();
  

   return 0;
}









