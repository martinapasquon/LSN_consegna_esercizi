/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#ifndef __ISING__
#define __ISING__

//Random numbers
#include "random.h"
 #include "mpi.h"
#include "Configurazione.h"
#include <vector>
int seed[4];
Random rnd;

double r=10.;
configurazione conf ;
int circle, gv, rcv;
const int M=5000, N_gen=5000;
configurazione * population = new configurazione[M];
configurazione * newpopulation = new configurazione[M];
configurazione population1;
configurazione population2;
configurazione bestpopulation ;
configurazione bestpopulation1 ;
configurazione bestpopulation2 ;
int N=conf.getN(),Nmigr=300000; 
double d=0;
int dim =50;
double city[50][2];
double pm=0.1, pc=0.9;
//vector <double> index;
//vector <double> dist;



int index_city[50];
int Index[50];
int index1[50];
int index2[50];
double L, L_best1, L_best2, rand1, rand2, rand3;
double L_best[N_gen];
double L_best_av[N_gen];


int  a=0;
double dist[M];




//functions
void Input(int, int);
void starting_population(void);
void get_index(int, int[]);
void get_distance(int );
double distanza(int, int);
void Selection_Sort(void);
int select(void);
void american_cities( int );
void city_square( double , int );
void population_crossover(int);
void population_mutations(int );

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
