/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
//ESERCIZIO 01.2:
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "random.h"
#include "funzioni.h"
#include<iomanip>
#include <cstdlib>

using namespace std;
 
int main (int argc, char *argv[]){

   Random rnd;
   int seed[4];
   int p1, p2;
   int N=10000; //numero di numeri random che vengono generati per ogni istogramma
   double a=0;
   vector <double> v;
  // double v[N];
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
      v.push_back(rnd.Gauss(0,1)); //genero N numeri random estratti da una distribuzione gaussiana con media=0 e deviazione standard=1
   }
  
   Print (v, "gauss1.txt" ); //stampo su file gli N numeri
   


   for(int i=0; i<N; i++){
      v[i]=(rnd.Gauss(0,1)+rnd.Gauss(0,1))*0.5; //genero 2*N numeri random estratti da una distribuzione gaussiana con media=0 e deviazione standard=1 e trovo la media 
      //di ogni coppia di numeri, ottenendo N numeri distribuiti secondo una gaussiana con media con media 0 e varianza =1/2
   }
   Print (v, "gauss2.txt" ); //stampo su file gli N numeri
    


   for(int i=0; i<N; i++){
      for(int i=0; i<10; i++){//genero 10*N numeri random estratti da una distribuzione gaussiana con media=0 e deviazione standard=1 e trovo la media 
      //di 10 di tali numeri per volta, ottenendo N numeri distribuiti secondo una gaussiana con media 0 e varianza =1/10
         a+=rnd.Gauss(0,1);
      }
      v[i]=a/10;
      a=0;
   }
   Print (v, "gauss10.txt" ); //stampo su file gli N numeri

   for(int i=0; i<N; i++){
      for(int i=0; i<100; i++){ //genero 100*N numeri random estratti da una distribuzione gaussiana con media=0 e deviazione standard=1 e trovo la media 
      //di 100 di tali numeri per volta, ottenendo N numeri distribuiti secondo una gaussiana con media con media 0 e varianza =1/100
         a+=rnd.Gauss(0,1);
      }
      v[i]=a/100;
      a=0;
   }
   Print (v, "gauss100.txt" ); //stampo su file gli N numeri


   

   for(int i=0; i<N; i++){ //genero N numeri random estratti da una distribuzione espoenziale con media=stdev=1
      v[i]=rnd.Exp(1);
   }
   Print (v, "exp1.txt" );



   for(int i=0; i<N; i++){ //genero 2*N numeri random estratti da una distribuzione espoenziale con media=stdev=1 e trovo la media di ogni coppia di tali numeri 
   //per volta, ottenendo N numeri con media 1 e varianza =1/2
      v[i]= (rnd.Exp(1)+rnd.Exp(1))/2;
   }
   Print (v, "exp2.txt" );//stampo su file gli N numeri

   
   for(int i=0; i<N; i++){//genero 10*N numeri random estratti da una distribuzione espoenziale con media=stdev=1 e trovo la media di 10 di tali numeri 
   //per volta, ottenendo N numeri con media 1 e varianza =1/10
      for(int i=0; i<10; i++){
         a+=rnd.Exp(1);
      }
      v[i]=a/10;
      a=0;
   }
    Print (v, "exp10.txt" );//stampo su file gli N numeri


   
   for(int i=0; i<N; i++){//genero 100*N numeri random estratti da una distribuzione espoenziale con media=stdev=1 e trovo la media di 100 di tali numeri 
   //per volta, ottenendo N numeri con media 1 e varianza =1/100
      for(int i=0; i<100; i++){
         a+=rnd.Exp(1);
      }
      v[i]= a/100 ;
      a=0;
   }
    Print (v, "exp100.txt" );//stampo su file gli N numeri



     for(int i=0; i<N; i++){//genero N numeri random estratti da una distribuzione di Cauchy_Lorentz con parametri (0, 1)
      v[i]=rnd.Lorentz(1);
   }
   Print (v, "Lorentz1.txt" );//stampo su file gli N numeri



   for(int i=0; i<N; i++){
      v[i]= (rnd.Lorentz(1)+rnd.Lorentz(1))/2;
   }
   Print (v, "Lorentz2.txt" );//stampo su file gli N numeri



   
   
   for(int i=0; i<N; i++){//genero N numeri random estratti da una distribuzione di Cauchy_Lorentz con parametri (0, 1)
      for(int i=0; i<10; i++){
         a+=rnd.Lorentz(1);
      }
      v[i]=a/10;
      a=0;
   }
    Print (v, "Lorentz10.txt" );//stampo su file gli N numeri



   
   for(int i=0; i<N; i++){//genero N numeri random estratti da una distribuzione di Cauchy_Lorentz con parametri (0, 1)
      for(int i=0; i<100; i++){
         a+=rnd.Lorentz(1);
      }
      v[i]= a/100 ;
      a=0;
   }
    Print (v, "Lorentz100.txt" );//stampo su file gli N numeri
   rnd.SaveSeed();
   return 0;
}

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
