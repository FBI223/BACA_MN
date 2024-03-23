//Marcin Sztukowski

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {

    int n = 0;
    cin >> n;
    float iloczyn = 0;
    float suma = 0;


    for (int i = 0; i < n; i++) {
        cin >> iloczyn;
        cin >> suma;


        float a = 1.0;
        float b = a - suma/cbrt(iloczyn) ;
        //float b =  ( cbrt(iloczyn) - suma )/(cbrt(iloczyn)) ;

        float c = 1.0 ;


        float p = (-1) * b / 2;
        float q = 1.0 ;



        float q_a = 1.0;
        float a1 = 0.0;
        float a2 = 0.0;
        float a3 = 0.0;

        float q_b = 1.0;
        float b1 = 0.0;
        float b2 = 0.0;
        float b3 = 0.0;

        float zero = 0.0;


        if (sqrt(p * p) >= sqrt(q)  ) {

            if (sqrt(p * p) > sqrt(q)) {

                if ( p >= 0.0 )
                {
                    q_a = p + sqrt(p*p - q) ;
                    q_b = q / q_a ;
                } else
                {
                    q_b = p - sqrt(p*p - q) ;
                    q_a = q / q_b ;
                }


            } else if ( sqrt(p * p) == sqrt(q) ) {

                q_a = p ;
                q_b = p ;
            }

            a1 = cbrt(iloczyn) / q_a;
            b1 = cbrt(iloczyn) / q_b;

            a2 = a1 * q_a;
            a3 = a2 * q_a ;

            b2 = b1 * q_b ;
            b3 = b2 * q_b ;
        }


        cout << std::setprecision(10) << std::scientific ;


        if ( a1 >= a3 )
        {
            cout << a1 << " " << a2 << " " << a3 << endl;
        } else if ( b1 >= b3 )
        {
            cout << b1 << " " << b2 << " " << b3  << endl;
        } else
        {
            cout << zero << " " << zero << " " << zero << endl;
        }


        //cout << a1 << " " << a2 << " " << a3 << endl<< b1 << " " << b2 << " " << b3  <<endl << endl;




    }





    return 0;
}



