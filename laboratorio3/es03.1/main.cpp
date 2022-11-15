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
#include "funzioni.h"

using namespace std;
 
int main (int argc, char *argv[]){

   Random rnd;
   int seed[4];
   int p1, p2;
   int M=10000; //# of throws            
   int N=100;   //# of blocks       
   int L=(M/N); 
   double S_0=100; //asset price at t=0
   double T=1; //delivery time
   double K=100; //stike price
   double r=0.1; //risk-free interest rate
   double sigma=0.25; //volatilty
   double gauss=0; //variabile  che conterrà numeri random estratti da una distribuzione gaussiana
   int N_intervals=100; //numero di intervalli in cui viene diviso l'intervallo [0,T]
   double C_dir[N]; // vettore che conterrà la stima del call-option price campionando direttamente il prezzo finale per ogni blocco N
   double C_discr[N];// vettore che conterrà la stima del call-option price campionando l'andamento GMB discretizzato del prezzo  per ogni blocco N
   double P_dir[N];// vettore che conterrà la stima del put-option price campionando direttamente il prezzo finale per ogni blocco N
   double P_discr[N];// vettore che conterrà la stima del call-option price campionando l'andamento GMB discretizzato del prezzo per ogni blocco N
   double S_dir=0; //variabile che conterrà il prezzo finale del bene;
   double S_discr=0; //variabile che conterrà il prezzo del bene dicretizzato;
   double delta=T/(double)N_intervals;
   double S_new=0, S_old{S_0};

    
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
     //inizializzo i vettori
       C_dir[i]=0;
       P_dir[i]=0;  
       for(int j=0; j<L; j++){ 
          gauss=rnd.Gauss(0,1);  //per S_dir ci vorebbe Gauss(0,T)  ma in tal caso T=1 quindi per brevità si è messo solo Gauss(0,1)
          S_dir=S( S_0,T, r, gauss,  sigma); // stima diretta del prezzo finale per ogni blocco N 
         // cout << S_dir << endl;
          if (S_dir-K>0)
             C_dir[i]+=exp(-r*T)*(S_dir-K); //il profitto della call è il massimo tra 0 e (S_dir-K) quindi se per qualche j (S_dir-K) <0 non viene incrementata P_dir[i]
             //per ottenere il profitto al tempo t bisogna poi moltiplicare per exp(-rT) per gli interessi della banca una volta che si depositano i soldi a t=0 (vale 
             //anche per P_dir, C_discr e P_discr)
          else
             P_dir[i]+=exp(-r*T)*(K-S_dir);  //il profitto della put è il massimo tra 0 e (K-S_dir) quindi se per qualche j (K-S_dir) <0 non viene incrementata P_dir[i]
       }
  } 
   for(int i=0; i<N; i++){
      S_old=S_0;
     //inizializzo i vettori
       C_discr[i]=0;
       P_discr[i]=0;  
      for(int j=0; j<L; j++){
         S_old=S_0;
         for(int k=0; k<N_intervals; k++){
             gauss=rnd.Gauss(0,1);  //per S_dir ci vorebbe Gauss(0,T)  ma in tal caso T=1 quindi per brevità si è messo solo Gauss(0,1)
             S_new=S(S_old,delta, r, gauss,  sigma); // stima del prezzo finale per ogni blocco N dopo averne discretizzato l'andamento
             S_old=S_new;   
         }
         S_discr=S_new;
         if (S_discr-K>0){
             C_discr[i]+=exp(-r*T)*(S_discr-K);//il profitto della call è il massimo tra 0 e (S_discr-K) quindi se per qualche j (S_discr-K) <0 non viene incrementata c_discr[i]
              
         } else
            P_discr[i]+=exp(-r*T)*(K-S_discr);//il profitto della put è il massimo tra 0 e (K-S_discr) quindi se per qualche j (K-S_discr) <0 non viene incrementata P_discr[i]
      }
   }
   
  
 
    SumErrProg( M, N, C_dir, "C_dir.txt"); 
    SumErrProg( M, N, P_dir, "P_dir.txt");
    SumErrProg( M, N, C_discr, "C_discr.txt");
    SumErrProg( M, N, P_discr, "P_discr.txt");

   return 0;
}
























  /* for (int i=0; i<N; i++){
      S_discr=rnd.S_discrete(S_0,T, r, sigma, N_intervals);
      if (S_discr-K>0)
         C_discr+=exp(-r*T)*(S_discr-K);
      else
         P_discr+=exp(-r*T)*(K-S_discr); 
   }
   C_discr=C_discr/N;
   P_discr=P_discr/N;




cout << C_dir <<" " <<C_discr <<" "<< P_dir <<" "<< P_discr  << endl;
   
    for(int i=0; i<N; i++){
       N_hit= 0;   
       for(int j=0; j<L; j++){
         k = j+i*L;
         
      if ((arr_rand[k]*l)>=(d*0.5)){
         N_hit++;
      }
   } cout << N_hit<< endl;
      ave[i] = L*2*l/(N_hit*d);     
     
      av2[i] = pow((ave[i]),2); 
      
    }
    for(int i=0; i<N; i++){
      for(int j=0; j<i+1; j++){
        sum_prog_C[i] += ave[j];
        _C[i] += av2[j];
       
      }
      sum_prog_C[i]/=(i+1);
      _C[i]/=(i+1);
      _C[0]=0;
      
      if (i!=0){
        _C[i] = sqrt((_C[i] - pow(sum_prog_C[i],2))/i); 
      }
    cout << sum_prog_C[i] << "   " << _C[i] <<"   "<< _C[i]<<endl;
    }
  ofstream out("sum_prog_C.txt");
   for(int i=0; i<N; i++){
      out << sum_prog_C[i]<<endl ;
   }
   out.close();
  ofstream output("_C.txt");
   for(int i=0; i<N; i++){
      output << _C[i]<<endl;
   }
   output.close();
   


*/
   









