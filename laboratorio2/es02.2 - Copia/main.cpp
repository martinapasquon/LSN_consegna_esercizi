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
   int length=100;
   int M=10000;             
   int N=100; 
   int dim=3;              
   int L=(M/N);           
   double ave[N][length];
   double  av2[N][length];
   double sum_prog[length];
   double sum2_prog[length];
   double err_prog[length];
   double sum1[length];
   

   double ave_cont[N][length];
   double  av2_cont[N][length];
   double sum_prog_cont[length];
   double sum2_prog_cont[length];
   double err_prog_cont[length];
   double sum1_cont[length];
   
   double** pos;
   double** pos_cont;
      pos=new double*[length];
      pos_cont=new double*[length];
    for (int i=0; i< length; i++){
       pos[i]=new double[dim];
       pos_cont[i]=new double[dim];
    }

   for(int i=0; i<N; i++){
     for (int j=0; j<length; j++){ 
       ave[i][j]=0;
       av2[i][j]=0;
       ave_cont[i][j]=0;
       av2_cont[i][j]=0;
     }
     sum_prog[i]=0;
     sum2_prog[i]=0;
     err_prog[i]=0;
     sum_prog_cont[i]=0;
     sum2_prog_cont[i]=0;
     err_prog_cont[i]=0;
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
   //rnd.RW( pos, length, dim);  
  // for (int i=0; i< length; i++)
  // cout << pos[i][0]<< " " << pos[i][1]<< " " << pos[i][2]<< endl;
 
//for (int i=0; i<N; i++){
 for (int k=0; k < length; k++ ){
   sum1[k]=0;
   sum1_cont[k]=0;
   }  
  for(int j=0; j<L; j++){
        rnd.RW_lattice( pos, length, dim); 
        //cout << pos[2][1]<< endl;
        rnd.RW_continuum( pos_cont, length, dim);
          for (int m=0; m<length; m++){
             for (int l=0; l<dim; l++){
                sum1[m]+=pow(pos[m][l],2);
                //cout << sum1[0]<< endl;

                sum1_cont[m]+=pow(pos_cont[m][l],2);    
               
            
         }}
      for (int m=0; m<length; m++){
         //cout << sum1[0]/L<< endl;
          ave[0][m] = sqrt(sum1[m]/(L));  
          av2[0][m] =pow(ave[0][m],2); 
          ave_cont[0][m] = sqrt(sum1_cont[m]/(L));     
          av2_cont[0][m] =pow(ave_cont[0][m],2); 
      }//cout << ave[i][0] <<  endl;
      cout << endl;
      }
      
    
     
   for (int m=0; m<length; m++){
      //for(int i=0; i<N; i++){
        sum_prog[m] += ave[0][m];
        sum2_prog[m] += av2[0][m];
        sum_prog_cont[m] += ave_cont[0][m];
        sum2_prog_cont[m] += av2_cont[0][m];
       
    }
      sum_prog[m]/=N;
      //cout << sum_prog[0] << endl;
      //cout << endl;
      sum2_prog[m]/=N;
      err_prog[0]=0;
      sum_prog_cont[m]/=N;
      sum2_prog_cont[m]/=N;
      err_prog_cont[0]=0;
      
      if (m!=0){
        err_prog[m] = sqrt((sum2_prog[m]- pow(sum_prog[m],2))); 
        err_prog_cont[m] = sqrt((sum2_prog_cont[m]- pow(sum_prog_cont[m],2))); 
      }
    cout << sum_prog_cont[m] << " " << sum2_prog[m] <<" "<< err_prog_cont[m]<<endl;
    }
ofstream out("RW _lattice.txt");
   for(int i=0; i<length; i++){
      out << sum_prog[i]<<" " <<err_prog[i]<<  endl ;
   }
   out.close();
ofstream output("RW _continuum.txt");
   for(int i=0; i<length; i++){
      output << sum_prog_cont[i]<<" " <<err_prog_cont[i]<<  endl ;
   }
   output.close();
 for(int m=0; m<M; ++m) {
    delete [] pos[m];
 } 
 delete [] pos;
 
 
   return 0;
}









