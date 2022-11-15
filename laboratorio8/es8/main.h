/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#ifndef __MAIN__
#define __MAIN__

//Random numbers
#include "random.h"
int seed[4];
Random rnd;

//parameters, observables
const int wd=20;
const int n_props=2;
double nbins;
double mean;
double sigma;
double walker[n_props];


// averages
double blk_av[n_props],blk_norm,accepted,attempted, accepted_1,attempted_1;
double glob_av[n_props],glob_av2[n_props];
double stima_n, stima_o, H_old, err_n, err_o, H_new;

// simulation
double  x_old;
const int N=500, N_trial=15, n_x=100;
int n_betak;
double p,delta_m,delta_s, T[N];
int o,n;
double x;
int nstep, nblk, metro, SA; 
double err;

//functions
void Input(void);
void Reset(int);
void Accumulate(void);
double Vpot(double);
double psi(double, double, double);
double Ekin(double, double, double );
void Averages(int, int);
void Sample(int);
void Move(double, int);
double psi_2(double, double, double);
double Boltzmann(double, int);
double Measure(double, double, double);
double Boltzmann(int, int);
void Print_param(void);
double Error(double,double,int);
double min(double a, double b);

#endif

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
