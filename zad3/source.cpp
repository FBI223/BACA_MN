//Marcin Sztukowski

#include "stdio.h"
#include <iostream>
#include "cmath"

using namespace std;

typedef void (*FuncPointer)(const double* x, double* y, double* Df);



void printVector(const double* x, unsigned N){
    for(unsigned i=0;i<N;++i)
        printf("%17.17f ",x[i]);
    printf("\n");
}


int findCurve(FuncPointer f, double* x, unsigned k, double h)
{
    double eps = 0.1e-14 ; // 14 zer i jedna jedynka po przecinku

    double y[2] = {};
    double Df[6] = {};

    double max = 1 ;
    double det = 1 ;

    int limit = 10 ;
    int kk = 0 ;

    for ( int i = 0 ; i < k ; i++ )
    {
        x[2] += h ;
        max = 1 ;
        det = 1 ;

        kk = 0 ;
        while (  (eps <= max )  )
        {
            f(x,y,Df);
            if ( fabs( det ) <= eps || kk == limit )
            {
                return (i+1) ;
            }

            if ( kk == limit )
            {
                //break;
            }

            double a = Df[0];
            double b = Df[1];
            double c = Df[3];
            double d = Df[4];

            /*
            double a_nxt = ( (-y[0] + a*x[0]+b*x[1])*d  - (-y[1]+ c*x[0] + d*x[1] )*b ) / (a*d - b*c )  ;
            double b_nxt = ( (-y[0] + a*x[0]+b*x[1] - a*a_nxt)/b );
            x[0] = a_nxt;
            x[1] = b_nxt;
            */

            det = a*d-b*c;
            x[0] -= ((d*y[0] - b*y[1] )/(det))  ;
            x[1] -= ((a*y[1] - c*y[0] )/(det)) ;

            max = std::max( fabs ( y[0] ) , fabs( y[1] ) ) ;

            kk++;
        }
        printVector(x,3) ;
        //cout << " kk " << kk << endl;
    }
    return  0 ;
}


int findSurface(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2)
{

    double eps = 1e-14 ; // 14 zer i jedna jedynka po przecinku
    int iter = 30 ;

    double xx[3] = {};
    double y[1] = {} ;
    double Df[3] = {};

    xx[0] = x[0];
    xx[1] = x[1];
    xx[2] = x[2];


    double max = 1 ;
    for ( int i = 1 ; i <= k1 ; i++ )
    {
        xx[1] = x[1] + i*h1;
        for ( int j = 1 ; j <= k2 ; j++ )
        {
            max =1;
            xx[2] = x[2] + j*h2;
            double kk = 0 ;

            while ( eps <= max  )
            {
                f(xx,y,Df) ;
                if ( std::isnan(xx[0])  ||  std::isnan(y[0])
                     || std::isinf(xx[0])  ||  std::isinf(y[0])  )
                {
                    return (i*k1+j) ;
                }
                max = fabs(y[0]) ;
                xx[0] = xx[0] - (y[0])/(Df[0]) ;
            }
            printVector(xx,3) ;
        }
        printf("\n");
    }
    return 0;
}














int findFixedPoints(FuncPointer f, double* x, unsigned k1, unsigned k2, double h1, double h2)
{

    double eps = 1e-14 ; // 14 zer i jedna jedynka po przecinku
    double y[2] = {} ;
    double Df[8] = {};


    double max = 1 ;
    double det = 1 ;

    double cc1 = x[2] ;
    double cc2 = x[3] ;


    for ( int i = 1 ; i <= k1 ; i++ )
    {
        x[2] = cc1 + i*h1 ;
        for ( int j = 1 ; j <= k2 ; j++ )
        {
            x[3] = cc2 + j*h2 ;
            max = 1 ;
            det = 1 ;

            while ( eps <= max  )
            {
                f(x,y,Df);
                y[0] -= x[0] ;
                y[1] -= x[1] ;

                double a = Df[0]-1.0;
                double b = Df[1];
                double c = Df[4];
                double d = Df[5]-1.0;

                if (  det == 0.0  )
                {
                    return (i*k1+j) ;
                }

                det = a*d-b*c ;
                x[0] -= (( d*y[0] - b*y[1] )/(det))  ;
                x[1] -= ((a*y[1] - c*y[0] )/(det)) ;

                double max_a = fabs(y[0]) ;
                double max_b = fabs(y[1]) ;
                if ( max_a >= max_b )
                {
                    max = max_a ;
                } else
                {
                    max = max_b;
                }
            }
            printVector(x,4) ;
        }
        printf("\n");
    }
    return 0;
}