//Marcin Sztukowski

#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;




int main()
{

    cout << setprecision(17) << fixed;

    int m;
    int n;
    cin >> m;
    cin >> n;
    vector<double> xx( m ) ;
    vector<double> yy( m ) ;
    vector<double> tt( n ) ;
    vector<double> wyniki( n ) ;
    vector<vector< double>> diff(m, vector<double>(m,-3.1415 )) ;

    for ( int i = 0 ; i < m ; i++ ) {cin >> xx[i] ;}
    for ( int i = 0 ; i < m ; i++ ) {cin >> yy[i] ;}
    for ( int i = 0 ; i < n ; i++ ) {cin >> tt[i] ;}


    diff[0][0] = yy[0] ;
    int count = 1;
    int count_silnia = 1;
    for ( int i = 1 ; i < m ; i++ ) {
        if ( xx[i] == xx[i-1] ) {

            diff[i][0] = diff[i-1][0] ;
            diff[i][count] = yy[i] / count_silnia ;
            count++;
            count_silnia *= count ;
        } else {
            count = 1 ;
            count_silnia = 1;
            diff[i][0] = yy[i] ;

        }
    }


    for ( int i = 1 ; i < m ; i ++ ) {
        for ( int j = i ; j < m ; j++ ) {

            if ( xx[j] != xx[ j-i ] ) {
                diff[j][i] = ( diff[j][i-1] - diff[j-1][i-1] ) / (  xx[j] - xx[ j-i ] ) ;
            } else {
                if ( diff[j][i] == -3.1415 ) {
                    diff[j][i] = diff[j-1][i] ;
                }
            }
        }
    }

    for ( int i = 0 ; i < m ; i++ ) {
        cout << diff[i][i] << " " ;
    }
    cout << endl ;


    for (int i = 0; i < n; i++) {
        double wynik = diff[m-1][m-1];
        for (int j = m-2; j >= 0; j--) {
            wynik = wynik * (tt[i] - xx[j]) + diff[j][j];
        }
        wyniki[i] = wynik;
    }





    for ( int i = 0 ; i < n ; i++ ) {
        cout << wyniki[i] << " " ;
    }





    return 0;
}