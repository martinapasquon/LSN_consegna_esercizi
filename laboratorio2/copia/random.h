/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/

#ifndef __Random__
#define __Random__

class Random {

private:
  int m1,m2,m3,m4,l1,l2,l3,l4,n1,n2,n3,n4;

protected:

public:
  // constructors
  Random();
  // destructor
  ~Random();
  // methods
  void SetRandom(int * , int, int);
  void SaveSeed();
  double Rannyu(void);
  int Rannyuint(double min, double max);
  double Rannyu(double min, double max);
  double Gauss(double mean, double sigma);
  void RW_lattice(double **RW, int length, int dim);
  void RW_continuum(double **RW, int length, int dim);
};
double error(double* AV,double*AV2, int n);

#endif // __Random__

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
