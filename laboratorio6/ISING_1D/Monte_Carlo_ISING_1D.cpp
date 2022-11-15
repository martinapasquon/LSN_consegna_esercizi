

#include <iostream>
#include <fstream>
//#include <ostream>
#include <cmath>
#include <iomanip>
#include "Monte_Carlo_ISING_1D.h"

using namespace std;

int main()
{ 
  Input(); //Inizialization
  if (restart==1){
     for (int i=0; i< N; i++){
        T=0.5 +0.1*i;
        for(int iblk=1; iblk <= nblk; ++iblk) {
           Reset(iblk);   //Reset block averages
           for(int istep=1; istep <= nstep; ++istep) {
               Move(metro);
               Measure();
               Accumulate(); //Update block averages
           }
           Averages(iblk);   //Print results for current block
        }
      Mean();
      } 
   }

   else{
    T=temp;
    nstep=50000;
    for(int istep=1; istep <= nstep; ++istep){
        print_U_eq();  
    }
    ConfFinal(); //Write final configuration
  }
  return 0;
}


void Input(void)
{

  ifstream ReadInput, ReadConf, Primes, Seed;


  cout << "Classic 1D Ising model             " << endl;
  cout << "Monte Carlo simulation             " << endl << endl;
  cout << "Nearest neighbour interaction      " << endl << endl;
  cout << "Boltzmann weight exp(- (1/T) * H ), (1/T) = 1/T " << endl << endl;
  cout << "The program uses k_B=1 and mu_B=1 units " << endl;

//Read seed for random numbers
  int p1, p2;
  Primes.open("Primes");
  Primes >> p1 >> p2 ;
  Primes.close();

//Read input informations
  ReadInput.open("input.dat");

  ReadInput >> restart;
  ReadInput >> temp;
  if(restart==1) Seed.open("seed.out");
  else Seed.open("seed.in");
  Seed >> seed[0] >> seed[1] >> seed[2] >> seed[3];
  rnd.SetRandom(seed,p1,p2);
  Seed.close();
  
  cout << "Temperature = " << temp << endl;

  ReadInput >> nspin;
  cout << "Number of spins = " << nspin << endl;

  ReadInput >> J;
  cout << "Exchange interaction = " << J << endl;

  ReadInput >> h;
  cout << "External field = " << h << endl << endl;
    
  ReadInput >> metro; // if=1 Metropolis else Gibbs

  ReadInput >> nblk;

  ReadInput >> nstep;
  
  if(metro==1) cout << "The program perform Metropolis moves" << endl;
  else cout << "The program perform Gibbs moves" << endl;
  cout << "Number of blocks = " << nblk << endl;
  cout << "Number of steps in one block = " << nstep << endl << endl;
  ReadInput.close();


//Prepare arrays for measurements
  iu = 0; //Energy
  ic = 1; //Heat capacity
  im = 2; //Magnetization
  ix = 3; //Magnetic susceptibility
 
  n_props = 4; //Number of observables

/////////////////////////
//Read initial configuration
  cout << "Read initial configuration" << endl << endl;
  if(restart==1)
  {
    ReadConf.open("config.out");
    int a=0;
    for (int i=0; i< nspin; i++){
      ReadConf >> a;
      s[i]=a;
    }
  }
  else 
  {
    for (int i=0; i<nspin; ++i)
      {
        if(rnd.Rannyu() >= 0.5) s[i] = 1; //per la configurazione a t=infinito. Per quella a T=0 si è usato s[i]=-1 per ogni i
        else
        s[i] = -1; 
     // }
  }
  
//Evaluate energy etc. of the initial configuration
  Measure();

//Print initial values for the potential energy and virial
  cout << "Initial energy = " << walker[iu]/(double)nspin << endl;
}
}
double Boltzmann(int sm, int ip)
{
  double ene = -J * sm * ( s[Pbc(ip-1)] + s[Pbc(ip+1)] ) - h * sm;
  return ene;
}

void Measure()
{
  double u =0.0, m = 0.0, x=0;

//cycle over spins
  for (int i=0; i<nspin; ++i)
  {
     u += -J * s[i] * s[Pbc(i+1)] - 0.5 * h * (s[i] + s[Pbc(i+1)]);
     x+=s[i];
     m+=s[i]; 
  }

  walker[iu] = u;
  walker[ic]= u*u;
  walker[ix]= x*x;
  walker[im]= m;
}

void Move(int metro)
{
  int o;
  double p,p_G, energy_old, energy_new, sm;
  double energy_up, energy_down;

  for(int i=0; i<nspin; ++i)
  {
  //Select randomly a particle (for C++ syntax, 0 <= o <= nspin-1)
    o = (int)(rnd.Rannyu()*nspin); 
    sm=s[o];
    energy_old= Boltzmann(sm, o); //per Metropolis
    energy_new= Boltzmann(sm*(-1), o);//per Metropolis
    energy_up=  Boltzmann(1, o); //per Gibbs
    energy_down=Boltzmann(-1, o); //per Gibbs
    p=energy_new-energy_old; //per Metropolis: differenza tra l'energia cambiando spin e senza cambiarlo
    p_G= energy_up- energy_down; //per Gibbs: differenza tra l'energia con lo spin =1 e quella con lo spin =-1

    if(metro==1){ //Metropolis
       if (p<0 or exp(-p/T)>rnd.Rannyu()){
         s[o]=s[o]*(-1);
         attempted ++; //devo scambiare accepted con attempted?
       }
       else accepted++;}

    else{ //Gibbs sampling
       if((1/(1+exp(p_G/T)))>rnd.Rannyu()){
         s[o]=1;
         attempted ++;
       }
       else {
         s[o]=-1;
       }
       accepted++;
    }
  }
}


void print_U_eq(void) //stampa su file l'energia dalla configurazione a T=0 o infinito fino all'equilibrio
{
    
   ofstream U_eq;
   U_eq.open("output_ene_eq_0.txt",ios::app);
   Move_eq(metro);
   U_eq <<  walker[iu]/nspin<< endl;
   U_eq.close();
}


void Move_eq(int metro) //funzione per cambiare gli spin per raggiungere l'equilibrio. Si é usato solo Metropolis per semplicità
{
  int o;
  double p, energy_old, energy_new;

  for(int i=0; i<nspin; ++i)
  {
  //Select randomly a particle (for C++ syntax, 0 <= o <= nspin-1)
    o = (int)(rnd.Rannyu()*nspin); 
    energy_old= Boltzmann(s[o], o); 
    energy_new= Boltzmann(s[o]*(-1), o); 
    p=energy_new-energy_old;
    if(metro==1){ //Metropolis
       if (p<0 or exp(-p/T)>rnd.Rannyu()){
         s[o]=s[o]*(-1);
         attempted ++;
       }
       else accepted++;
      }
  }
  Measure();
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
   for(int i=0; i<n_props; ++i){
     blk_av[i] = blk_av[i] + walker[i];
   }
   blk_norm = blk_norm + 1.0;
}


void Averages(int iblk) //Print results for current block
{
    //Energy
    stima_u = blk_av[iu]/blk_norm/(double)nspin; 
    glob_av[iu]  += stima_u;
    glob_av2[iu] += stima_u*stima_u;
    err_u=Error(glob_av[iu],glob_av2[iu],iblk);
    //Calore specifico
    stima_c = (1/T)*(1/T)*(blk_av[ic]/blk_norm/(double)nspin -stima_u*stima_u*nspin); 
    glob_av[ic]  += stima_c;
    glob_av2[ic] += stima_c*stima_c;
    err_c=Error(glob_av[ic],glob_av2[ic],iblk);
    //magnetizzazione
    stima_m= blk_av[im]/blk_norm/(double)nspin;  //Energy
    glob_av[im]  += stima_m;
    glob_av2[im] += stima_m*stima_m;
    err_m=Error(glob_av[im],glob_av2[im],iblk);
    //suscettività
    stima_x= (1/T)*blk_av[ix]/blk_norm/(double)nspin;  //Energy
    glob_av[ix]  += stima_x;
    glob_av2[ix] += stima_x*stima_x;
    err_x=Error(glob_av[ix],glob_av2[ix],iblk);
}


void Mean(void) //Print results for current block
{
  if(h==0){ 
  ofstream Ene, Heat,  Chi;
  if(metro==1){ //stampare su file i calcoli utlizzando Metropolis
    Ene.open("output_ene.txt", ios::app);
    Heat.open("output_Heat.txt", ios::app);
    Chi.open("output_Chi.txt", ios::app);
  }
  else{ //stampare su file i calcoli utlizzando Gibbs
    Ene.open("output_ene_G.txt", ios::app);
    Heat.open("output_Heat_G.txt", ios::app);
    Chi.open("output_Chi_G.txt", ios::app); 
  }
  const int wd=12;
  Ene <<   setw(wd) << stima_u << setw(wd) << glob_av[iu]/(double)nblk << setw(wd) << err_u << endl;
  Heat << stima_c << setw(wd) << glob_av[ic]/(double)nblk << setw(wd) << err_c << endl;
  Chi << stima_x << setw(wd) << glob_av[ix]/(double)nblk << setw(wd) << err_x << endl;

  Ene.close();
  Heat.close();
  Chi.close();
  } 
  else{
    ofstream Mag;

    if(metro==1){
       Mag.open("output_magn.txt", ios::app);
    }
    else{
       Mag.open("output_magn_G.txt", ios::app);
    }
    const int wd=12;
    Mag << stima_m << setw(wd) << glob_av[im]/(double)nblk << setw(wd) << err_m << endl;
    Mag.close();
  }
}




void ConfFinal(void)
{
  ofstream WriteConf;

  cout << "Print final configuration to file config.out" << endl << endl;
  WriteConf.open("config.out");
  for (int i=0; i<nspin; ++i)
  {
    WriteConf << s[i] << endl;
  }
  WriteConf.close();

  rnd.SaveSeed();
}


int Pbc(int i)  //Algorithm for periodic boundary conditions
{
    if(i >= nspin) i = i - nspin;
    else if(i < 0) i = i + nspin;
    return i;
}

double Error(double sum, double sum2, int iblk)
{
    if(iblk==1) return 0.0;
    else return sqrt((sum2/(double)iblk - pow(sum/(double)iblk,2))/(double)(iblk-1));
}


