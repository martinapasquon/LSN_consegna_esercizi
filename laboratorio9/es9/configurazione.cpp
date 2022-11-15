#include "configurazione.h"
#include "random.h"
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;



config::config( ){ //posizioni 
	
	m_N=34;
	for (int i=0; i<m_N; i++){
		for (int j=0; j<m_N; j++){
			if(i==j)
		       m_c[i][j]=1;
		    else 
			m_c[i][j]=0;
	     }
	}
}

  // distruttore
config:: ~config() {;}
	

int config::getN(){
	
	return m_N=34;
	
}


int config::getm_c(int i, int j){
	
	return m_c[i][j];
	
}


void config::setm_c(int i, int j, double value){
	
    m_c[i][j]=value;
	
}


config config:: operator=( config & copy){ //overload operatore =
	//config copy(c);
	for(int i=0; i< m_N; i++){
       for(int j=0; j< m_N; j++){
	        setm_c(i, j,copy.getm_c(i,j));
	   }
	}
return copy;
}

void config:: permutation(int i, int j){ //metodo che permuta le città i e j

	   double a[m_N], b[m_N];
	   a[0]=0; a[1]=0;
	   if (i>0 and j>0){
	   if (i!=j){
		  for (int l=0; l<m_N; l++){
		    a[l]=getm_c(l,i);
		    b[l]=getm_c(l,j);
			setm_c(l,i, b[l]);
			setm_c(l,j, a[l]);
		  }
	   }
	   //else{cout << "messaggio di ERRORE dal metodo di permutazione: si chiede di scambiare una città con se stessa" << endl;}
	   }
	   else{cout << "messaggio di ERRORE dal metodo di permutazione: la città 1 deve restare nella prima tappa" << endl;}
}

void config:: permutation_contiguous(int m, int k, int l){//metodo che permuta le città dalla k-esima alla k+m esima con quelle dalla l+k-esima alla l+m+k esima
    if(k+m < l){
	   for (int i=k; i<k+m; i++){
          permutation(i, l+i);
	   }
	}
    else{cout << "messaggio di ERRORE dal metodo di permutazione contigua: le città da permutare devono essere diverse tra loro!" << endl;}
} 

void config:: crossover( config & copy, int cut, double  index1[],double index2[] ){ //metodo che applica il crossover a due città
	//config copy(c);
	int conta=0;
	for(int i=0; i< m_N; i++){
       for(int j=0; j< cut; j++){
	        copy.setm_c(i, j,getm_c(i,j));
	   }
	}conta=cut;
	for(int k=0; k< m_N; k++){
        for(int l=cut; l< m_N; l++){
			if(index2[k]==index1[l]){
				for(int i=0; i< m_N; i++){
					copy.setm_c(i,conta, getm_c(i, l));
				}
			conta++;}
		}
	}
	
}







void config:: shift(int m, int n, int k){ //metodo che sposta di n posizioni m città dalla k esima città

       double copia[m_N][m_N];
	   for (int i=1; i<m_N; i++){
			  for (int j=1; j<m_N; j++){
				copia[i][j]=m_c[i][j];
			  }
		 }

	   if (k==0){cout << "messaggio di ERRORE dal metodo di shift: la città 1 deve restare nella prima tappa" << endl;}
	   if (m>=m_N-1){cout << "messaggio di ERRORE dal metodo di shift: deve essere m<m_N!" << endl;}
	     else{
	       for (int i=1; i<m_N; i++){
			   for (int j=1; j<m_N; j++){
                   if(i<k or i>=k+m+n) {copia [j][i]=m_c[j][i];}
                   if(k<=i and i<k+m) {copia[j][i+n]=m_c[j][i];}
                   if(i>=k+m and i< k+m+n) {copia[j][i-m]=m_c[j][i];}

		       }   
		   }
		   for (int i=1; i<m_N; i++){
			  for (int j=1; j<m_N; j++){
				m_c[i][j]=copia[i][j];
			  }
	       }
		 }
} 

void config:: inversion(int m, int k){ //metodo che inverte m città a partire dalla k-esima
       int conta=0;
	   int km=0;
	   if (m%2==0) {km=(m)*0.5;} //se devo invertire un numero pari di città le inverto tutte
	   if (m%2==1) {km=(m+1)*0.5;} //se devo invertire un numero dispari di città le inverto tutte tranne quella a k+m/2
	   if (k==0){cout << "messaggio di ERRORE dal metodo di inversione: la città 1 deve restare nella prima tappa" << endl;}
	   if (m>m_N){cout << "messaggio di ERRORE dal metodo di inversione: deve essere m<m-_N!" << endl;}
	     else{
	       for (int i=k; i<k+km; i++){
				   permutation(i, (k+m-conta));
			
				   //cout << k+m-conta << "   " << i << endl;  conta++;
		   
		 }
	}
}


 void config:: check(){ //metodo di controllo
	 int a=0;
	 double v[m_N];
	 
	 for (int k=0; k<m_N; k++){
		a=0;
        for (int j=0; j<m_N; j++){
		   if(getm_c(j,k)==1){
			v[k]=j;
		   }
		   a+=getm_c(j,k);
		}
		if(a<1){ cout << "ERRORE segnalato dalla funzione di controllo: nello step "  << k << "non si va in nessuna città!" << endl;}
		if(a>1){ cout << "ERRORE segnalato dalla funzione di controllo: nello step"  << k << " si va in più di una città!" << endl;}
       // if (a==1){cout << "avviso dalla funzione di controllo: OK in ogni step si va in una sola città!" << endl;}
	 }
    for  (int  k=0; k<m_N; k++){
	   for  (int  j=k+1; j<m_N; j++){
		if (v[k]==v[j])
		  {cout << "ERRORE segnalato dalla funzione di controllo: negli step " <<k  <<" e" << j << "si visita la stessa città!" <<  endl;}
	
	   }
 }
 }

void config::print(){ //metodo che stampa la matrice del percorso
	for (int i=0; i<m_N; i++){
	cout << endl;
		for (int j=0; j<m_N; j++){
		 cout << getm_c(i,j)<< setw(5) ;
	    }
    cout << endl;
	}
	cout << endl;
	cout << endl;
}
