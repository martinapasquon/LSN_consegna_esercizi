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
#include <cmath>
#include <cstdlib>
#include "random.h"

using namespace std;

Random :: Random(){}

Random :: ~Random(){}

void Random :: SaveSeed(){
   ofstream WriteSeed;
   WriteSeed.open("seed.out");
   if (WriteSeed.is_open()){
      WriteSeed << l1 << " " << l2 << " " << l3 << " " << l4 << endl;;
   } else cerr << "PROBLEM: Unable to open random.out" << endl;
  WriteSeed.close();
  return;
}

double Random :: Gauss(double mean, double sigma) {
   double s=Rannyu();
   double t=Rannyu();
   double x=sqrt(-2.*log(1.-s))*cos(2.*M_PI*t);
   return mean + x * sigma;
}

double Random :: Rannyu(double min, double max){
   return min+(max-min)*Rannyu();
}

double Random :: Rannyu(void){
  const double twom12=0.000244140625;
  int i1,i2,i3,i4;
  double r;

  i1 = l1*m4 + l2*m3 + l3*m2 + l4*m1 + n1;
  i2 = l2*m4 + l3*m3 + l4*m2 + n2;
  i3 = l3*m4 + l4*m3 + n3;
  i4 = l4*m4 + n4;
  l4 = i4%4096;
  i3 = i3 + i4/4096;
  l3 = i3%4096;
  i2 = i2 + i3/4096;
  l2 = i2%4096;
  l1 = (i1 + i2/4096)%4096;
  r=twom12*(l1+twom12*(l2+twom12*(l3+twom12*(l4))));

  return r;
}

void Random :: SetRandom(int * s, int p1, int p2){
  m1 = 502;
  m2 = 1521;
  m3 = 4071;
  m4 = 2107;
  l1 = s[0];
  l2 = s[1];
  l3 = s[2];
  l4 = s[3];
  n1 = 0;
  n2 = 0;
  n3 = p1;
  n4 = p2;

  return;
}
double error(double* AV,double*AV2, int n){
    if (n==0){ return 0;}
    else
        {return sqrt((AV2[n] - AV[n]*AV[n])/n);}
}





/*void Random :: SumErrProg (int  M, int N ){

   double arr_rand[M];
   double sum_prog[N];
   double sum2_prog[N];
   double err_prog[N];
   double ave[N];
   double av2[N];
   double sum1=0;
   int L=(M/N);           
   int k=0;


for(int i=0; i<M; i++){
      arr_rand[i]=Rannyu();
   }

   SaveSeed();

   

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
    cout << "somma progressiva= " << sum_prog[i] << "   quadrato della somma progressiva= " << sum2_prog[i] <<"   std progressiva= "<< err_prog[i]<<endl;
    }
  ofstream out("sum_prog.txt");
   for(int i=0; i<N; i++){
      out << sum_prog[i]<< " " << err_prog[i] << endl ;
   }
   out.close();
}*/
/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
