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
#include <ostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
# include <cstdlib>
# include <ctime>
# include <mpi.h>
# include "random.h"
#include "Configurazione.h"
#include "main.h"


using namespace std;

int main(int argc, char* argv[])
{
int size, rank;
MPI_Init(&argc,&argv);
MPI_Comm_size(MPI_COMM_WORLD, &size);
MPI_Comm_rank(MPI_COMM_WORLD, &rank);
std::cout<<" Sono il nodo "<<rank<<" dei "<<size<<" che hai utilizzato"<<endl;

MPI_Status stat;
double population1[N][2];
double population2[N][2];
int itag=1; int itag2=2;


  Input(size, rank); //Inizialization 
  for(int igen=0; igen<N_gen; igen++){
      if(igen%Nmigr!=0 or igen==0){ //se non sono nella generazione Nmigr applico il crossover e le mutazioni alla mia popolazione
        for(int i=0; i<M-1; i+=2)
             population_crossover(i);
         for(int i=0; i<M; i++)
             population_mutations(i);
         for (int i=0; i<M; i++){
             population[i]=newpopulation[i];
		       get_index(i, index_city); //metto in un vettore il percorso
             get_distance(i);
	      }
	
      Selection_Sort();
   
   }
   
   else{ 
      if(rank==0){ 
         gv=rnd.Rannyuint(0,size); //scelgo casualmente il nodo che dà il suo individuo migliore
         do{
            rcv=rnd.Rannyuint(0,size); //scelgo casualmente il nodo che riceve il suo individuo migliore
         }while (rcv==gv);
      }

      MPI_Bcast(&gv, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);
      MPI_Bcast(&rcv, 1, MPI_INTEGER, 0, MPI_COMM_WORLD);

      if (rank==gv){
          get_index(0, index_city);  //metto in un array il percorso dell'individuo migliore
      
          MPI_Send(index_city, N, MPI_INTEGER, rcv,itag, MPI_COMM_WORLD); //il nodo gv invia l'array
      }
      if (rank==rcv){
          MPI_Recv(index_city, N, MPI_INTEGER, gv,itag, MPI_COMM_WORLD, &stat); //il nodo rcv riceve l'array
         for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){//metto nell'individuo migliore di rcv il percorso inviato da gv
             if(index_city[i]==j){
                population[0].setm_c(i, j, 1); 
             }
             else
             population[0].setm_c(i, j, 0);
            }
         }
      } 
      for (int i=0; i<M; i++){
		       get_index(i, index_city);
             get_distance(i);
      }  
	
      Selection_Sort();
      
   } 
   L_best[igen]=dist[0]; //metto in un array L_best la lunghezza del percorso migliore di ogni generazione
   int cont=0;
   for(int i=0; i<igen; i++){
      if (L_best[igen]>L_best[i])cont++; //trovo l'individuo migliore per ogni generazione (bestpopulation)
   }
   if (cont==0){bestpopulation=population[0]; } 
   for(int j=0; j<M/2; j++) //trovo la media delle lunghezze degli M/ individui migliori per ogni generazione
   L_best_av[igen]+=dist[j];
   L_best_av[igen]=L_best_av[igen]/(M/2.); 
   for(int i=0; i< M; i++) dist[i]=0;
  }
  population[0]=bestpopulation;
  get_index(0, index_city);
   ofstream out1("L_best_out_america_1.txt");
   ofstream out2("L_best_av_out_america_1.txt");
   ofstream out3("best_cartesian_america_1.txt");
   for(int i=0; i<N_gen; i++){
   out1 <<  L_best[i] << endl;
   out2 <<  L_best_av[i] << endl;
   }
   for (int i=0; i<N; i++){
      int ind=index_city[i];
      out3 << city[ind][0] << setw(20) << city[ind][1] << endl;
   }
      out3 << city[0][0] << setw(20) << city[0][1] << endl;
   out1.close();
   out2.close();
   out3.close();
   
  delete []population;
  delete []newpopulation;
  MPI_Finalize();
return 0;
}





void Input(int size, int rank){
   for(int j=0; j<size; j++){
      if(j==rank){ 
  int p1, p2, p1_prova, p2_prova;
   ifstream Primes("Primes");
   for (int i=0; i< rank*4; i++)
       Primes >>p1_prova >>p2_prova;
   Primes >> p1 >> p2 ;
   Primes.close();
   //for (int i=0 i<size; i++)
     
   ifstream input("seed.in");
   input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
   rnd.SetRandom(seed,p1,p2);
   input.close();
     }
   }
   american_cities(N);
   starting_population();
   
   for (int i=0; i<M; i++){
		get_index(i, index_city);
      get_distance(i);
	}
	
   Selection_Sort();
   
   for(int i=0; i< M; i++) dist[i]=0;
};





void american_cities( int N){ //funzione che riempie city con le coordinate delle capitali americane
   string name;
   string descr;
  ifstream in("American_capitals.dat");
  //assert(in && "Input file non esistente ");
  if(!in){
  std::cout << "problema con apertura file, esco!"<< endl;
   exit(11);
  }
  else{
   
    for(int i=1; i<N+1; i++){
      //getline(in, name, ' ');
      getline(in, descr, '-');
      in >>  city[i-1][0] >> city[i-1][1];
      city[i-1][0]=-1*city[i-1][0];
      if (in.eof()){
        std::cout << "è stata raggiunta la fine del file, esco!"<< endl;
        exit(11);
      }
    }
  }

};

void city_square( double r, int N){ //funzione che riempie city con le coordinate delle città su un quadrato

	for (int i=0; i<N; i++){
		city[i][0]=rnd.Rannyu(0, r);
      city[i][1]=rnd.Rannyu(0, r);
      std::cout << city[i][0] << "   "<< city[i][1] << endl;
	}
};


void starting_population(void){ //funzione che rende diversi tra loro gli individui della mia popolazione di partenza applicando
// permutazioni radom a tutte le città di tutta la mia popolazione 
	
	for(int i=0; i<M; i++){
     for(int j=0; j<M; j++){
        rand1=rnd.Rannyuint(1,N);
        do{
           rand2=rnd.Rannyuint(1,N);
        }while(rand2==rand1);
        population[i].permutation(rand1, rand2);
        population[i].check();
     }
   }
};

void get_index(int i, int index_city[]){ //funzione che mette in un array il percorso di ogni individuo
   for (int k=0; k<N; k++){
		for (int j=0; j<N; j++){
            if(population[i].getm_c(k, j)==1) {index_city[j]=k; }
		} 
	}
};

void get_distance(int i){ //funzione che calcola la distanza tra due città contigue di un individuo
    d=0;
   for (int k=1; k< N; k++){d+=distanza( index_city[k], index_city[k-1]) ;}
   dist[i]+=d;
   dist[i]+=distanza( index_city[N], index_city[0]);
  
};

double distanza( int i, int j) { //funzione che calcola la distanza tra due città i e j
    L=sqrt(pow(city[i][0]-city[j][0],2) + pow(city[i][1]-city[j][1],2));
    
 return L;

};
void Selection_Sort(void){ //funzione che ordina gli individui dell popolazione in base alla lunghezza del percorso

  configurazione copy;
  double temp;
  int min=0;
   for(int i=0; i<M-1; i++){
      min = i;
   for(int j=i+1; j<M; j++)
      if(dist[j] < dist[min]) 
         min = j;
   temp=dist[min];
   copy=population[min];
   dist[min]=dist[i];
   population[min]=population[i];
   dist[i]=temp;
   population[i]=copy;
   }

};


int select(void){ //funzione che serve per selezionare un inividuo della mia popolazione
	
	 double r=rnd.Rannyu();
	 int p=4, l;
	 l=N*pow(r, p);

	return l+1;
 };


void population_crossover(int i){ //funzione che applica l'operatore di crossover alla mia popolazione

   int parent1=select();
   int cut =rnd.Rannyuint(1,N);
   int parent2=0;
   do{
      parent2=select();
   }while(parent2==parent1);
   if(rnd.Rannyu()<pc){ //applico il crossover con probabilità pc
      get_index(parent1, index1 );
      get_index(parent2, index2 );
      population[parent1].crossover( newpopulation[i],cut, index1,index2);
      newpopulation[i].check();
      population[parent2].crossover( newpopulation[i+1],cut, index2,index1);
      newpopulation[i+1].check();
   }
   else{
      newpopulation[i]=population[parent1];
      newpopulation[i+1]=population[parent2];
   }
}


void population_mutations(int i){ //funzione che applica gli operatori di mutazione alla mia popolazione
   
   for(int j=1; j<N; j++){
      if(rnd.Rannyu()<pm){
         rand1=rnd.Rannyuint(1,N);
         newpopulation[i].permutation(j, rand1);
         newpopulation[i].check();
      }
      if(rnd.Rannyu()<0 and j<N/4){
         rand1=rnd.Rannyuint(1,N/4.);
         rand2=rnd.Rannyuint(1,N/4.);
         newpopulation[i].permutation_contiguous(rand1, j, rand2);
         newpopulation[i].check();}
        
        if(rnd.Rannyu()<pm ){
         rand1=rnd.Rannyuint(1,N/4);
         rand2=rnd.Rannyuint(1,N/4);
         if(j<(N-rand1-rand2)){
            newpopulation[i].shift(rand1, rand2, j);
            newpopulation[i].check();}
        }
        

       if(rnd.Rannyu()<pm and j<N-3){
         rand1=rnd.Rannyuint(1,N-j);
        population[i].inversion(rand1, j);
        population[i].check();}
   }  

}


