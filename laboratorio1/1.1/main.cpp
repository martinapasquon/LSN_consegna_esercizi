#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


using namespace std;
 
int main ( int argc , char** argv) {

  if ( argc < 3 ) 
    cout << "Uso del programma : " << argv[0] << " <n_data> <filename> " << endl;
    return -1 ;
  }


  int ndata = atoi(argv[1]);
  char * filename = argv[2];


  double * data = ReadDataFromFile ( filename, ndata ) ;



   char * filename = argv[2];
   int M=100000;             
   int N=100;               
   int L=int(M/N);           
   float r[M];
   float x[N];
   float ave[N];
   float ave2[N];
   float sum_prog[N];
   float sum2_prog[N];
   float err_prog[N];
   float sum1=0;
   int i=0;

   ifstream input("randomnum");
    if (input.is_open()){
      while ( !input.eof() ){
          if (i<M):
            input >> r[i];
            i++;
      }
      input.close();
    } else cerr << "PROBLEM: Unable to open randomnum" << endl;

   for(int i=0; i<N; i++){
     x[N]=0;
     ave[N]=0;
     ave2[N]=0;
     sum_prog[N]=0;
     sum2_prog[N]=0;
     err_prog[N]=0;
    }

    for(int i=0; i<N; i++){
      sum1 = 0;   
       for(int j=0; j<N; j++){
         k = j+i*L;
         sum1 += r[k];
       }
    }
    ave[i] = sum1/L;   
    av2[i] = sum2/L;    
    av2[i] = (ave[i])**2; 
    
    for(int i=0; i<N; i++){
      for(int j=0; j<N; j++){
        sum_prog[i] += ave[j];
        su2_prog[i] += av2[j];
      }
    sum_prog[i]/=(i+1);
    sum2_prog[i]/=(i+1);
    err_prog[i] = error(sum_prog,su2_prog,i); 
    }
  ofstream output("sum_prog");
   for(int i=0; i<N; i++){
      output << sum_prog[i];
   }
   output.close();
  ofstream output("err_prog");
   for(int i=0; i<N; i++){
      output << err_prog[i];
   }
   output.close();

   return 0;
}