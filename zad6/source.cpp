//Marcin Sztukowski

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

void print_vector(const vector<double>& v_in) {
    std::cout << std::scientific << std::setprecision(10);
    for ( int i = 0 ; i < v_in.size() ; i++ ) {
        cout << v_in[i] << endl;
    }

}

void wydrukuj_wektor(const vector<double>& v_in) {
    cout << endl ;
    for ( int i = 0 ; i < v_in.size() ; i++ ) {
        cout << v_in[i] << endl;
    }
    cout << endl ;

}

vector<double> metoda_sor(int n , int m , const vector<std::vector<double>>& wstegi , const vector<double>& diagonala
                        , const vector<double>& yy ,  vector<double> xx
                        , double omega , int ile_iteracji) {


    for ( int i = 0 ; i < ile_iteracji ; i++ ) {

        for ( int j = 0 ; j < n ; j++ ) {
            int ile_gornych_wsteg = min(m, n - j - 1);
            int ile_dolnych_wsteg = min(m, j);

            //cout << " ile gornych wsteg " << ile_gornych_wsteg << endl;
            //cout << " ile dolnych wsteg " << ile_dolnych_wsteg << endl;

            double suma = yy[j] ;
            int kk = m - 1  ;
            for ( int k = 0 ; k < ile_gornych_wsteg ; k++ ) {
                suma -= wstegi[kk-k][j] * xx[ j+1+k ] ;
                //cout << "u " <<wstegi[kk-k][j] << endl;
            }
            kk = m - 1  ;
            for ( int k = 0 ; k < ile_dolnych_wsteg ; k++ ) {
                suma -= wstegi[ kk-k ][j-1-k] * xx[j-1-k ] ;
                //cout << "d " << wstegi[ kk-k ][j-1-k]  << endl;
            }
            //cout << endl ;
             xx[j] =   ( (suma * omega) / diagonala[j] ) + (1.0 - omega )*xx[j];
        }

    }

    return xx;
}


int main() {

    int n ;
    int m ;
    double omega ;
    int ile_iteracji;
    cin >> n ;
    cin >> m ;
    std::vector<std::vector<double>> wstegi;
    for (int i = 0 ; i < m ; i++) {
        wstegi.push_back(std::vector<double>(n-m+i))   ;
    }
    std::vector<double> diagonala(n);
    std::vector<double> yy(n);
    std::vector<double> xx(n);

    // wstegi
    for ( int i = 0 ; i < m ; i++ ) {
        for ( int j = 0 ; j < n-m+i ; j++ ) {
            cin >> wstegi[i][j] ;
        }
    }
    // przekatna
    for ( int j = 0 ; j < n ; j++ ) {
        cin >> diagonala[j] ;
    }
    //prawa strona rownaia
    for ( int j = 0 ; j < n ; j++ ) {
        cin >> yy[j] ;
    }
    // x
    for ( int j = 0 ; j < n ; j++ ) {
        cin >> xx[j] ;
    }

    cin >> omega ;
    cin >> ile_iteracji ;


    vector<double> v1 =  metoda_sor(n,m,wstegi ,diagonala , yy , xx ,  omega,ile_iteracji);
    print_vector(v1) ;


    return 0;
}