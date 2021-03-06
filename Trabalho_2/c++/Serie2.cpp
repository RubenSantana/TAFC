#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "gnuplot-iostream.h"

using namespace std;

static const int N=1;

static const int N_iter=100;

static const double dt =0.01;


int main(int argc, char *argv[])
{
  //Vamos por numa file os tempos, as posições e as velocidades
  ofstream file;
  file.open("output.txt");
  
  Gnuplot gp; //Isto vai para o final
  if (argc!=3)
    {
      cout << "This program works with two arguments, execute it by the following line" << endl << "[directory]/thisfile [length] [N_sheets]" << endl;
      return 0;
    }
  //Aquisição dos argumentos, comprimento da caixa e o número de folhas 
  double length=atof(argv[1]);    
  int N_sheets=atoi(argv[2]);
   
  //Posições iniciais
  double x_i=1;
  double v_i=0;

  
    
  /*
    cout << "teste" << endl;
    cout	<< "Nsheet=" << N_sheets<< endl;
    cout	<<"length="<<length<<endl ;
  */
  double *x_eq;
  double *x;
  double *v;
  double *v_eq;
  


  
  x_eq=new double[N_sheets];
  v_eq=new double[N_sheets]; 
  x=new double[N_sheets];
  v=new double[N_sheets];

  //Inicialização
  file << "0 ";
  for (int i=0;i<N_sheets;i++)
    {
      
      x_eq[i]=(length/(2*N_sheets))+ (i * length/N_sheets);
      x[i]=x_i;
      v[i]=v_i;
      v_eq[i]=0;
      file << x[i] << " " << v[i] << " ";
    }
  file << endl;

  for(int i=0;i<N_iter;i++)
    {
      file << (i+1)*dt << " ";
      for(int j=0;j<N_sheets;j++)
	{
	  double dx,dv;
	  dx=x[j]-x_eq[j];	   
	  dv=v[j]-v_eq[j];

	  //Força=-dx
	  
	  dv=dv-dx*dt;

	  //incremento nas velocidades

	  v[j]=dv+v_eq[j];
	  
	  //incremento nas posições
	  dx=dx+dv*dt;

	  x[j]=x_eq[j]+dx;
	    
	  file << x[j] << " " << v[j] << " ";
	}
      file << endl;
    }

  file.close();
  delete[] x_eq;
  delete[] v_eq;
  delete[] x;
  delete[] v;

  gp << "plot 'output.txt' using 1:2";
  
  //delete[] x_i;
  // delete[] v_i;
  return 0;   
}
