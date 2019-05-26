//
//  main.cpp
//  metod vrachenii
//
//  Created by Руднев Павел Сергеевич on 26/05/2019.
//  Copyright © 2019 Руднев Павел Сергеевич. All rights reserved.
//

#include <iostream>
#include <math.h>
#include <locale>
#include <cstdlib>
#include <ctime>
#include <stdio.h>

#define _N 100 // ˜ËÒÎÓ Û‡‚ÌÂÌËÈ

using namespace std;

void print(double *a, int n);
void print_vector(double *b,int n);

void vrash (double *a, double *b, int n)
{
    double c;
    double s;
    double akk,alk,save;
    
    for (int k=0; k<n-1; k++)
    {
        for (int l=k+1; l<n; l++)
        {
            if(sqrt(a[k*n+k]*a[k*n+k] + a[l*n+k]*a[l*n+k] ) < 1.e-7)
                cout<<"error"<<'\n';
            // "Ã‡Î˚È" ¯‡„
            c = a[k*n+k] / (sqrt( a[k*n+k]*a[k*n+k] + a[l*n+k]*a[l*n+k] ));
            //cout << c << '\t';
            s = -(a[l*n+k] / (sqrt( a[k*n+k]*a[k*n+k] + a[l*n+k]*a[l*n+k] )));
            //cout << s << '\n';
            for (int g=k;g<n; g++)
            {
                akk=a[k*n+g];  alk=a[l*n+g];
                a[k*n+g] = c*akk - s*alk;
                a[l*n+g] = s*akk + c*alk;
            }
            save = b[k];
            b[k] =  c*b[k] - s*b[l];
            b[l] =  s*save + c*b[l];
        
        }
    }
    // Œ·‡ÚÌ˚È ıÓ‰
    for (int l=(n-1);l>=0;l--)
    {
        b[l]/=a[l*n+l];
        for (int k=0;k<l;k++)
            b[k]=b[k] - a[k*n+l] * b[l];
    }
}


int main()
{
    setlocale(LC_ALL, "Russian");
    double *a;
    double *b;
    double *a2,t,s;
    int i;
    int n=_N;
    a = new double[n*n];
    a2 = new double[n*n];
    b = new double [n];
    srand(time(NULL));
    for (int i = 0; i<n; i++)
        b[i] = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            b[i]+=(a2[i*n+j]=a[i*n+j] = rand()%100);
    
    print(a,n);
    t=clock();
    vrash(a,b,n);
    print_vector(b,n);
    t=clock()-t;
    
    for(i=0,s=0.;i<n;i++)
        s+=(b[i]-1.)*(b[i]-1.);
    printf("Time is %lf seconds\nResidual:\n", t/CLOCKS_PER_SEC,sqrt(s));
    
    delete [] a;
    delete [] b;
    delete [] a2;
    return 0;
}

void print(double *a, int n)
{
    int i,j;
    if(n>10){
        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                cout<<a[i*n+j]<<"\t";
            }
            cout<<". . .\t"<<a[i*n+(n-1)]<<"\t";
            cout<<"\n";
        }
        cout<<"\n";
        
        
        for(i=0;i<3;i++)
        {
            for (j = 0; j < 10; j++)
                cout<<'.'<<'\t';
            cout<<'\t'<<'.'<<'\n';
        }
        cout<<'\n';
        
        for (j = 0; j < 10; j++) {
            cout<<a[(n-1)*n+j]<<"\t";
        }
        cout<<". . .\t"<<a[(n-1)*n+(n-1)]<<"\t";
    }
    else{
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                cout<<a[i*n+j]<<"\t";
            }
            cout<<"\n";
        }
    }
    
}

void print_vector(double *b,int n)
{
    if (n<11)
        for (int i = 0; i < n; i++)
        {cout << "b[" << i << "]=" <<b[i] << '\n';}
    else
    {
        cout <<'\n';
        {for (int i = 0; i < 10; i++)
        {cout << "b[" << i << "]=" << b[i] << '\n';}
            cout <<'.'<<'.'<<'.'<<'\n';
            cout << "b[" << n-1 << "]=" << b[n-1] << '\n';}
    }
}


