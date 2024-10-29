//Marcin Sztukowski

#include "vectalg.h"
using namespace std;

void print_matrix(Matrix matriks)
{
    for ( int i = 0 ; i < matriks.size() ; i++ )
    {
        for ( int j = 0 ; j < matriks.size() ; j++ )
        {
            cout << matriks(i,j) << " " ;
        }
        cout << endl;
    }
}

void print_vector(Vector wektor)
{
    for ( int i = 0 ; i < wektor.size() ; i++ )
    {
        cout << wektor[i] << endl ;
    }
    cout << endl;
}



Vector rozwiaz_rownania(
        const Matrix & A,   // Macierz
        const Vector & b   // Wektor
){

    int n = A.size();
    Matrix U = Matrix(n);
    Vector skala = Vector(n) ;
    Vector bb = Vector(n) ;
    Vector rozwiazania = Vector(n) ;

    for (int i = 0; i < n; i++) {
        double temp_skala_max = 0;
        for (int j = 0; j < n; j++) {
            U(i, j) = A(i, j);
            if ( std::abs(A(i,j)) > temp_skala_max )
            {
                temp_skala_max = std::abs(A(i,j)) ;
            }

        }
        skala[i] = temp_skala_max ;
        bb[i] = b[i] ;
    }


    for ( int i =0 ; i < n-1 ; i++  )
    {
        int idx_piv = i ;
        double stosunek_piv_max = std::abs( U(i,i) / skala[i] ) ;
        double temp_stosunek_piv ;
        for ( int j = i+1 ; j < n ; j++)
        {
            temp_stosunek_piv = std::abs( U(j,i) / skala[j] );
            if ( temp_stosunek_piv > stosunek_piv_max )
            {
                idx_piv = j ;
                stosunek_piv_max = temp_stosunek_piv ;
            }
        }

        if ( idx_piv != i )
        {
            double temp = 0.0 ;
            for ( int j = 0 ; j < n ; j++)
            {
                temp = U(i,j);
                U(i,j) = U(idx_piv,j);
                U(idx_piv,j) = temp;
            }
            temp = skala[i] ;
            skala[i] = skala[idx_piv];
            skala[idx_piv] = temp;

            temp = bb[i] ;
            bb[i] = bb[idx_piv];
            bb[idx_piv] = temp ;
        }

        for ( int j = i+1 ; j < n ; j++  )
        {
            double pivot = U(i,i) ;
            if ( U(j,i) != 0.0 )
            {
                double temp_mnoznik = (-1*( U(j,i) ))/pivot ;
                U(j,i)  = 0.0 ;
                for ( int k = i+1 ; k < n ; k++ )
                {
                    U(j,k) += (temp_mnoznik * U(i,k)) ;
                }
                //L(j,i) = -temp_mnoznik ;
                bb[j] += (temp_mnoznik*bb[i]) ;

            }
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        double suma = 0.0;
        for (int k = i + 1; k < n; k++) {
            suma += U(i, k) * rozwiazania[k];
        }
        rozwiazania[i] = (bb[i] - suma ) / U(i, i);
    }

    return rozwiazania ;
}

Vector solveEquations(
        const Matrix & A,   // Macierz
        const Vector & b,   // Wektor
        double  eps         // dopuszczalny błąd
){
    int n = b.size() ;
    Vector rozwiazania = rozwiaz_rownania(A,b) ;
    Vector rezydualny = residual_vector(A,b,rozwiazania);
    double norma_rezydualna = rezydualny.max_norm();

    int kk = 0 ;
    int max_iteracji = 1;
    while ( norma_rezydualna >= eps  )
    {

        if ( kk == max_iteracji )
        {
            break;
        }

        Vector poprawka = rozwiaz_rownania(A,rezydualny) ;
        for ( int i = 0 ; i < n ; i++ )
        {
            rozwiazania[i] += poprawka[i] ;
        }
        rezydualny = residual_vector(A,b,rozwiazania);
        norma_rezydualna = rezydualny.max_norm();


        kk++;
    }

    return rozwiazania ;
}