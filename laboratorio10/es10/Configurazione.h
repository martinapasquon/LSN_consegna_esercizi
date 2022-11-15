#ifndef __Configurazione_h__
#define __Configurazione_h__
#include "random.h"
# include <mpi.h>


class configurazione {

public:
 configurazione( );

  // distruttore
  ~configurazione();
configurazione operator=( configurazione & ) ;

int getN(void);
int getm_c(int i, int j);
void setm_c(int i, int j, int value);
void permutation(int i, int j);
void shift(int m, int n, int k);
void inversion(int m, int k);
void check();
void permutation_contiguous(int m, int k, int l);
void crossover(configurazione &,int cut,int  index1[],int index2[] );
void print();


private:
 int m_N;
 int m_c[50][50];

};


#endif // ___h__Configurazione