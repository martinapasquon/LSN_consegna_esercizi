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
int Random :: Rannyuint(double min, double max){
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
void Random:: RW_lattice(double ** pos, int length, int dim){
    
    //double pos[length][dim];
   // pos[length][dim]={};
    double dir[length];
    double updown[length];
    int direzione=0;
    pos[0][0]=0;
    for (int  i=0; i< length; i++){
       dir[i]=Rannyuint(0, dim);
       updown[i]=Rannyu();
       } 

    for (int i=0; i<length; i++){
       for (int j=0; j<dim; j++){
          if(i!=0)
           pos[i][j]=pos[i-1][j];
       }
       direzione=dir[i];
       if (updown[i]<0.5){
          pos[i][direzione]+=1;
       }
       else{
          pos[i][direzione]+=-1; 
       } }
    
   
} 
void Random:: RW_continuum(double ** pos, int length, int dim){
    
    //double pos[length][dim];
   // pos[length][dim]={};
   double theta[length];
   double phi[length];
    pos[0][0]=0;
    for (int  i=0; i< length; i++){
       theta[i]=Rannyu(0, 2*M_PI);
       phi[i]=Rannyu(0, M_PI);
       } 

    for (int i=0; i<length; i++){
       for (int j=0; j<dim; j++){
          if(i!=0)
           pos[i][j]=pos[i-1][j];
       }
      pos[i][0]+=sin(phi[i])*cos(theta[i]);
      pos[i][1]+=sin(phi[i])*sin(theta[i]);
      pos[i][2]+=cos(phi[i]);

       }
       
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
