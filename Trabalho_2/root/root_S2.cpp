
void root_S2()
{

  static const Double_t length=10;
  static const Int_t N=5;
  static const Int_t N_iter=50000;
  static const Double_t dt =0.001;

  //Vamos por numa file os tempos, as posições e as velocidades
  ofstream file;
  file.open("output.txt");
  

   
  // Parametros

  Double_t sig=1;
  Double_t m=4* M_PI;
  Double_t n_0=1;

  Double_t x_i=1;
  Double_t v_i=0;

  Double_t w_p=sqrt(4 * M_PI*pow(sig,2)/m);


  TGraph *gr[N];
  
  Double_t *x_eq;
  x_eq=new Double_t [N];
  Double_t **x=new Double_t* [N];
  Double_t **v=new Double_t* [N];
  Double_t *t=new Double_t[N_iter];

  

  //Inicialização
  file << "0 "; 
  for (int i=0;i<N;i++)
    {  
      x[i]=new Double_t[N_iter];
      v[i]=new Double_t[N_iter];
      
      x_eq[i]=(length/(2*N))+ (i * length/N);
      x[i][0]=x_eq[i]+1*pow((+1),i);
      // x[i][0]=x_eq[i];      
      v[i][0]=v_i;
      file << x[i][0] << " " << v[i][0] << " ";
      if (x[i][0]>length || x[i][0]<0)
	{

	  cout <<"Não é possível introduzir condições iniciais fora dos limites das paredes favor certifique-se que as folhas se encontram dentro do intervalo [0,"<<length<<"]"<<endl;
	  return;
	}
    }
  v[N-1][0]=3;
  
  file << endl;
  Double_t dx,dv;


  for(int i=1;i<N_iter;i++)
    {
      Double_t taux=i*dt;
      t[i]=taux;
      file << taux << " ";
      /*
	for(int j=0;j<N;j++)
	{
	  
	dx_old=x[j][i-1]-x_eq[j][i-1];
	// cout << dx<<endl;
	dv_old=v[j][i-1]-v_eq[j][i-1];
	  
	//Força=-dx
	dv=dv_old-dx_old*dt;	  
	//	  incremento nas velocidades
	v_eq[j][i]=v_eq[j][i-1];
	v[j][i]=dv+v_eq[j][i];
	 	  

	//incremento nas posições
	dx=dx_old+dv*dt;
	 
	x_eq[j][i]=x_eq[j][i-1];
	x[j][i]=x_eq[j][i]+dx;
		  
	 
	//	 cout << x[j][i] <<endl;   
	file << x[j][i] << " " << v[j][i] << " ";	  
	}
      */

      
      for(int j=0;j<N;j++)
	{
	  dx=(+1)*(x[j][i-1]-x_eq[j]);
	  v[j][i]=v[j][i-1]*cos(w_p*dt)-w_p*dx*sin(w_p)*dt;	
	  x[j][i]=x[j][i-1]+v[j][i-1]*sin(w_p*dt)-dx*(1-cos(w_p*dt));

	
	  //Condições de Fronteira periódicas
	  if (x[j][i]<0)
	  {
	  x[j][i]=length;
	  x_eq[j]=x_eq[j] + length;	 
	  }

	  if (x[j][i]>length)
	  {
	  x[j][i]=0;
	  x_eq[j]=x_eq[j]-length;	 
	  }
	  file << x[j][i] << " " << v[j][i] << " ";
        
	}
      file << endl;
    }
  
  //Output
  for(int i=0;i<N;i++)
    {
      gr[i]=new TGraph(N_iter,x[i],t);
      gr[i]->GetYaxis()->SetRange(0,20);

             auto *axis = gr[i]->GetXaxis();
 
         axis->SetLimits(0-2,length+2);                 // along X
	 /*
	 gr[i]->GetHistogram()->SetMaximum(10);   // along          
      gr[i]->GetHistogram()->SetMinimum(-10);  //   Y     
	 */
      if (i==0)
	{
	  gr[i]->Draw();
     
	}
      else
	gr[i]->Draw("same");
    }

   
  delete x_eq;
  delete[] x;
  delete[] v;

  file.close();
  
}
