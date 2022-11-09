#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <time.h>
using namespace std;
#define pi 3.141592653589793238462643
static int Np=300;
static double rho=0.8;
static int ens=1000;
static double L = sqrt(double(Np) / 0.8);


int output(double *s2,double *c2){
  int i;
  char filename[128];   
  sprintf(filename,"Sq_T1.0.dat");
  ofstream File;
  File.open(filename);

  File <<"#"<<" "<< "q"<<" "<<"sq"<< endl; 
  for(i=1;i<100;i++)
    File << double(i)*2.*pi/L << " " << s2[i]+c2[i]<< endl; 
  File.close(); 
  return 0;
}

int sq(double *x,double *y,double *c2,double *s2,double ens){
  int i,nx,ny;
  double si=0.,co=0.;

  for(nx=0;nx<100;nx++)
    for(ny=0;ny<100;ny++){
      co=0.0;
      si=0.0;      
      for(i=0;i<Np;i++){
	///(0.5*pi*int(sqrt(nx*nx+ny*ny)))/Np/ens
	co+=cos(2.*pi*(nx*x[i]+ny*y[i])/L);
	si+=sin(2.*pi*(nx*x[i]+ny*y[i])/L);
      }  
      if(nx*nx+ny*ny!=0){
	c2[int(sqrt(nx*nx+ny*ny))]+=co*co/(0.5*pi*int(sqrt(nx*nx+ny*ny)))/Np/ens;
	s2[int(sqrt(nx*nx+ny*ny))]+=si*si/(0.5*pi*int(sqrt(nx*nx+ny*ny)))/Np/ens;
      }
    }
  return 0;
}


int main(){
  
  double s2[1000],c2[1000],s[1000],x[Np],y[Np];
  double dummy;
  char filename[128];   
  int i,j;
  for(i=0;i<1000;i++){
    s2[i]=0.0;
    c2[i]=0.0;
  }
  
  ifstream file;
  
  for(i=1;i<ens;i++){
    sprintf(filename,"bina2d_%d_T1.0.dat",i*100);
    file.open(filename);   
    for(j=0;j<Np;j++){
      file >> x[j] >> y[j] >> dummy; 
      //      cout << x[j]<<endl;
    }
    file.close();
    sq(x,y,s2,c2,ens);
  }
  
  output(s2,c2);
  
  return 0;
}
