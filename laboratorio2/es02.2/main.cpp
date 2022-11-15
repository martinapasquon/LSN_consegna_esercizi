/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
//ESERCIZIO 02.2:
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
   int length=100; //numero di step da cui è costituito ogni RW
   int M=10000; //numero di lanci            
   int N=100; //numero di blocchi
   int dim=3;  //dimesione su cui avviene la simulazione dei RW      
   double** pos; //matrice (length x pos) che contiene le coordinate di ogni step del RW
   

pos=new double*[length];

for (int i=0; i< length; i++){
       pos[i]=new double[dim];
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


   rnd.SaveSeed();


rnd.SumErrProg ( M, N, length, dim, pos, 0, "RW _lattice.txt"); //funzione che genera M RW di lunghezza length in dimensione dim su un reticolo e calcola
// con il metodo a blocchi (N blocchi)la media e l'errore progressivo della distanza dei RW dal'origine in funzione dello step. Infine scrive sul file
// "RW _lattice.txt" media ed errore progressivi.
rnd.SumErrProg ( M, N, length, dim, pos, 1,"RW _continuum.txt"); //funzione che genera M RW di lunghezza length in dimensione dim nel continuo e calcola
// con il metodo a blocchi (N blocchi)la media e l'errore progressivo della distanza dei RW dal'origine in funzione dello step. Infine scrive sul file
// "RW _continuum.txt" media ed errore progressivi.
   
for(int m=0; m<length; m++) {
   delete [] pos[m];
} 
delete [] pos;
   
return 0;
}









