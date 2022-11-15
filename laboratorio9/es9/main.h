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
#include "configurazione.h"
#include <vector>
int seed[4];
Random rnd;

double r=10.;
config conf ;
int circle;
const int M=5000, N_gen=5000;
config * population = new config[M];
config * newpopulation = new config[M];
config bestpopulation ;
int N=conf.getN(), d=0;
double city[34][2];
double pm=0.1, pc=0.9;
//vector <double> index;
//vector <double> dist;
double index[34],index1[34], index2[34];
double L, rand1, rand2, rand3;
double L_best[N_gen];
double L_best_av[N_gen];


int  a=0;
double dist[M];




//functions
void Input(void);
void starting_population(void);
void get_index(int, double[]);
void get_distance(int );
double distanza(int, int);
void Selection_Sort(void);
int select(void);
void city_circle( double , int );
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
