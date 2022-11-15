
#include <iostream>
#include <fstream>
#include <ostream>
#include <cmath>
#include <iomanip>
#include "main.h"

using namespace std;

int main()
{ 
  
  Input(); //Inizialization
  if(SA==1){ //se SA==1 applico SA
    H_old=0; //inizalizzo i parametri
    H_new=0;
    x_old=0; //punto di partenza

    for (int k=0; k< N; k++) {//trovo N stime ddell'integrale al variare di sigma, mu
        T[k]=1 -0.0019*k; //dimiuisco la temperaura ad ogni step SA
    for (int tr=0; tr< N_trial; tr++) {
        for(int iblk=1; iblk <= nblk; ++iblk) {
             Reset(iblk);   //Reset block averages
             for(int istep=1; istep <= nstep; ++istep){
                 H_old=0.;
                 H_new=0.;
                 for(int j=0; j <= n_x; j++){//stima dell'integrale come la somma dell'integranda valutata in x_n diversi punti per mean e sigma
                      Sample(SA); //campionamento psi**2
                      H_old+=Measure(x_old, mean, sigma);
                  }
                  delta_m=rnd.Rannyu(-0.01,0.01)/2.; //proposta variazioni di mean e sigma
                  delta_s=rnd.Rannyu(-0.01,0.01)/2.;
  
                  for(int j=0; j <= n_x; j++){//stima dell'integrale come la somma dell'integranda valutata in x_n diversi punti per mean+delta_m, sigma +delta_s
                        Sample(SA); //campionamento psi**2
                        H_new+=Measure(x_old, mean+delta_m, sigma+delta_s);
                  }
                  Accumulate(); 
              }
              Averages(iblk, SA);  
         } 
         Move(T[k], tr); //Metropolis 
    } cout << "step SA=" << "acceptance rate=" << accepted_1/attempted_1 << endl;
    accepted_1=0;
    attempted_1=0;
    }
    Print_param();
  }



  if (SA==0){ //se SA==0 allora trovo il valor medio di H con il metodo a blocchi, per mean e sigma fissati 
      H_old=0;
      for(int iblk=1; iblk <= nblk; ++iblk){
         Reset(iblk);   //Reset block averages
          for(int istep=1; istep <= nstep; ++istep){
             H_old=0;
             for(int j=0; j <= n_x; j++){//stima dell'integrale come la somma dell'integranda valutata in x_n diversi punti
               Sample(SA);
               H_old+=Measure(x_old, mean, sigma);
             }
     
          Accumulate(); 
          }
      Averages(iblk, SA);   
      }
  }
  return 0;
};

void Input(void)
{
   ifstream ReadInput;

   cout << "The program uses h/(2*PI) and m=1 units " << endl;
  
   int p1, p2;
  
   ifstream Primes("Primes");
   Primes >> p1 >> p2 ;
   Primes.close();

   ifstream input("seed.in");
   input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
   rnd.SetRandom(seed,p1,p2);
   input.close();
  
//Read input informations
   ReadInput.open("input.dat");

  ReadInput >> SA;
  
  ReadInput >> mean;
  ReadInput >> sigma;
 
  ReadInput >> nblk;
  cout << "Number of blocks = " << nblk << endl;

  ReadInput >> nstep;
  cout << "Number of steps in one block = " << nstep << endl << endl;
  ReadInput.close(); 


  cout << "mean = " << mean << endl;
  cout << "sigma = " << sigma << endl;
  o=0; n=1;
  x_old=0;
  
}
double Vpot(double x){ //funzione che calcola il potenziale
    return pow(x,4) - 2.5*pow(x,2);
};
double psi(double x, double mean, double sigma){ //funzione che calcola psi
    return (exp(-((x-mean)*(x-mean))/(2*sigma*sigma))+exp(-(x+mean)*(x+mean))/(2*sigma*sigma));
};
double Ekin(double x, double mean, double sigma){ //funzione che calcola l'energia cinetica
  double exp1=exp(-(x-mean)*(x-mean)/(2*sigma*sigma));
  double exp2=exp(-(x+mean)*((x+mean)))/(2*sigma*sigma);
  return -0.5*(  exp1 * (pow((x-mean),2)*pow(sigma,-2)-1)  + exp2* (pow((x+mean),2)*pow(sigma,-2)-1))  * pow(sigma,-2) ;
};
double psi_2( double x, double mean, double sigma){ //funzione che calcola il quadrato di psi
  return pow((psi(x, mean, sigma)),2);
}


void Sample(int SA) //funzione che campiona psi_2
{ 
  double x_new=0;
  //il tasso di accettazione è data dal min tra 1 e psi(xnew)/psi(xold)
 //campionamento della distribuzione di probabilità p valutata in mu e sigma fissati con T uniforme

  x_new=rnd.Rannyu(-2., 2.);
  
  p=psi_2(x_new, mean, sigma)/psi_2(x_old, mean, sigma);//T(x_new)/T(x_old)
  //se min[T(x_new)/T(x_old),1]=T(x_new)/T(x_old) allora accetto la mossa con probabilità T(x_new)/T(x_old) se no l'accetto sempre 
  attempted++;
  double minimo=min(1., p);
  if (minimo==1){
       x_old=x_new;
       accepted++;
    }
    else{
      if(rnd.Rannyu()< minimo){
          x_old=x_new;
          accepted++;
      }
    }

    if (SA==0){
       ofstream psi2;
       psi2.open("output_psi2.txt",ios::app);
       psi2 << x_old << endl;
       psi2.close();
    }
}


double Measure(double x, double sigma, double mu) //funzione che calcola l'integrale con la tecnica del re-weighting
{
  return(  Ekin(x, mean, sigma)/(psi(x,mean, sigma))  +  Vpot(x) )/(double)n_x;
 
}

void Reset(int iblk) //Reset block averages
{
   if(iblk == 1)
   {
       for(int i=0; i<n_props; ++i)
       {
           glob_av[i] = 0;
           glob_av2[i] = 0;
       }
   }

   for(int i=0; i<n_props; ++i){
     blk_av[i] = 0;
   }
   blk_norm = 0;
   attempted = 0;
   accepted = 0;
}


void Accumulate(void) //Update block averages
{
  blk_av[o] = blk_av[o] + H_old;
  blk_av[n] = blk_av[n] + H_new;
  blk_norm = blk_norm + 1.0;
}



void Averages(int iblk, int SA) //Print results for current block
{  cout << "block number=" << iblk << "  " <<  "acceptance rate= " << accepted/attempted << endl;
  
    stima_o = blk_av[o]/(double)(blk_norm*nstep);
    glob_av[o]  += stima_o;
    glob_av2[o] += stima_o*stima_o;
    err_o=Error(glob_av[o],glob_av2[o],iblk);

    stima_n = blk_av[n]/(double)(blk_norm*nstep);
    glob_av[n]  += stima_n;
    glob_av2[n] += stima_n*stima_n;
    err_n=Error(glob_av[n],glob_av2[n],iblk);

     
    
 if (SA==0){
    ofstream Integralblk;
    const int wd=20;
    Integralblk.open("output_integral_blk.txt",ios::app);
    Integralblk << stima_o << setw(wd) << glob_av[o] << setw(wd) << err_o  << endl;
    Integralblk.close();
 }
}


void Print_param(){
  ofstream param;
  param.open("output_param.txt");
  param << mean << setw(20)<< sigma << endl;
  param.close();
 }

void Move( double T, int tr) //funzione che implementa l'algoritmo di Metropolis
{

  ofstream Integral_SA;
    
  double p_m;
  if (tr==(N_trial-1)){
  Integral_SA.open("output_integral_SA.txt",ios::app);
  Integral_SA << glob_av[o] <<  setw(20) << err_o << endl;
  Integral_SA.close();
  }
  p_m=exp((glob_av[o]-glob_av[n])/T); //differenza tra H cambiando mu e sigma e senza cambiarle
  double minimo=min(1,p_m);
  if (minimo==1){
    glob_av[o]=glob_av[n];
    mean=fabs(mean+delta_m);
    sigma=fabs(sigma+delta_s);
    accepted_1++;
  }
  else{
    if(rnd.Rannyu()<minimo){ 
         glob_av[o]=glob_av[n];
         mean=fabs(mean+delta_m);
         sigma=fabs(sigma+delta_s);
         accepted_1++;
       }
  }
       attempted_1++;
 
}


double Error(double sum, double sum2, int iblk)
{
    if(iblk==1) return 0.0;
    else return sqrt((sum2/(double)iblk - pow(sum/(double)iblk,2))/(double)(iblk-1));
}
double min(double a, double b)
{   if (a<b)
    return a;
    else return b;
}

