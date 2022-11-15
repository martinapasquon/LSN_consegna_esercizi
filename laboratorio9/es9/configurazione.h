#ifndef __configurazione_h__
#define __configurazione_h__
#include "random.h"
//#include <string>

class config {

public:
 config( );

  // distruttore
  ~config();
config operator=( config & ) ;

int getN(void);
int getm_c(int i, int j);
void setm_c(int i, int j, double value);
//void shuffle( Random& ran);
void permutation(int i, int j);
void shift(int m, int n, int k);
//void crossover(config &conf2, int j);
//void permutation_cont(int m, int k, int j);
void inversion(int m, int k);
void check();
void permutation_contiguous(int m, int k, int l);
void crossover(config &,int cut, double  index1[],double index2[] );
//int select( Random& ran);
void print();


private:
 int m_N;
 double m_c[34][34];

//uso libreria armadillo
};


#endif // ___h__config