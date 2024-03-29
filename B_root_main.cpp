//Marcin Sztukowski


#include <iostream>
#include <cmath>

using namespace std;



double wielomian(double x){
    return (((x-6)*x+11)*x)-6;	}
double wielomianSinExp(double x)
{
    return ((((x-6)*x+11)*x)-4 + sin(15*x))*exp(-x*x);
}
double kwadrat(double x){
    return (x*x-2);	 }
double kwadrat100(double x){
    return 1e100*(x*x-2);	}
double kwadrat_10(double x){
    return 1e-10*(x*x-2);	}



double findZero(
        double (*f)(double),  // funkcja której zera szukamy w [a, b]
        double a,             // lewy koniec przedziału
        double b,             // prawy koniec przedziału
        int M,                // maksymalna dozwolona liczba wywołań funkcji f
        double eps,           // spodziewana dokładność zera
        double delta          // wystarczający błąd bezwzględny wyniku
)
{


    int i = 2  ;


    double f_a = f(a);
    double f_b = f(b);

    if (abs(f_a) < eps )
    {
        return a;
    }

    if (abs(f_b) < eps )
    {
        return b;
    }

    double f_c;

    double d = b-a ;
    double c;
    double przelacznik = 0.8 ;


    if ( f_a*f_b < 0.0  )
    {

        while  ( (i < M)  && ( d > przelacznik )  )
        {
            d = d/2 ;
            c = a + d;

            f_c = f(c);


            if ( ( std::abs(f_c) < eps ) || (std::abs(b-a) < delta ) )
            {
                return c;
            }


            if (std::signbit(f_c) != std::signbit(f_a)) {
                b = c;
                f_b = f_c;
            } else {
                a = c;
                f_a = f_c;
            }

            if (abs(f_a) < eps )
            {
                return a;
            }

            if (abs(f_b) < eps )
            {
                return b;
            }

            i+=1;
        }


        while ( (i<M)  )
        {

            c = b - (f_b*(b-a)/(f_b-f_a)) ;
            f_c = f(c) ;

            if ( ( std::abs(f_c) < eps ) || (  std::abs(b-a) < delta )  )
            {
                return c;
            } else
            {
                f_a = f_b;
                a=b;

                f_b = f_c;
                b=c;


                if (abs(f_a) < eps )
                {
                    return a;
                }

                if (abs(f_b) < eps )
                {
                    return b;
                }
            }

            i++;
        }



    } else
    {



        while ( (i<M) && ( f_a*f_b > 0.0  ) )
        {

            c = b - (f_b)*(b-a)/(f_b-f_a) ;
            f_c = f(c) ;

            if ( ( std::abs(f_c) < eps ) || (  std::abs(b-a) < delta )  )
            {
                return c;
            }

            f_a = f_b;
            a=b;

            f_b = f_c;
            b=c;


            if (abs(f_a) < eps )
            {
                return a;
            }

            if (abs(f_b) < eps )
            {
                return b;
            }

            i++;
        }


        if ( b < a )
        {
            double temp = b ;
            b = a;
            a = temp;

            temp = f_b ;
            f_b = f_a;
            f_a = temp;
        }

        d = b-a ;
        while  ( (i < M) && ( d >= przelacznik )  )
        {
            d = d/2 ;
            c = a + d;

            f_c = f(c);


            if ( ( std::abs(f_c) < eps ) || (std::abs(b-a) < delta ) )
            {
                return c;
            }


            if (std::signbit(f_c) != std::signbit(f_a)) {
                b = c;
                f_b = f_c;
            } else {
                a = c;
                f_a = f_c;


                if (abs(f_a) < eps )
                {
                    return a;
                }

                if (abs(f_b) < eps )
                {
                    return b;
                }
            }

            i+=1;
        }


        while ( (i<M)  )
        {

            c = b - (f_b)*(b-a)/(f_b-f_a) ;
            f_c = f(c) ;

            if ( ( std::abs(f_c) < eps ) || (  std::abs(b-a) < delta )  )
            {
                return c;
            }

            f_a = f_b;
            a=b;

            f_b = f_c;
            b=c;



            if (abs(f_a) < eps )
            {
                return a;
            }

            if (abs(f_b) < eps )
            {
                return b;
            }

            i++;
        }

    }



    return -0.0;
};







int main() {



    cout.precision(17);                                               // Spodziewany wynik
    cout << findZero(wielomian, 0, 4, 20, 1e-15, 1e-14) << endl;      // 1 lub 2 lub 3
    cout << findZero(wielomian, 0, 40, 20, 1e-15, 1e-14) << endl;     // 1 lub 2 lub 3
    cout << findZero(wielomian, 1, 2, 2, 1e-15, 1e-14) << endl;       // 1 lub 2
    cout << findZero(wielomian, -150, 1.9, 20, 1e-15, 1e-14) << endl; // 1
    cout << findZero(wielomian, 1.5, 2.99, 20, 1e-15, 1e-14) << endl; // 2
    cout << findZero(wielomian, 2.01, 40, 20, 1e-15, 1e-14) << endl;  // 3
    cout << findZero(wielomian, 1.5, 6, 20, 1e-15, 1e-14) << endl;    // 1 lub 2 lub 3

    cout << findZero(wielomianSinExp, -1, 3, 60, 1e-60, 1e-14) << endl;  // 0.43636925909804245
    cout << findZero(wielomianSinExp, -3, 3, 60, 1e-160, 1e-14) << endl; // 0.43636925909804245

    cout << findZero(kwadrat, 0, 4, 15, 1e-11, 1e-14) << endl;          // 1.414213562373095
    cout << findZero(kwadrat100, 0, 4, 15, 1e-11, 1e-14) << endl;       // 1.414213562373095
    cout << findZero(kwadrat_10, 0, 4, 10, 1e-10, 1e-14) << endl;       // każdy punkt z przedziału [1, 1.73205]
    cout << findZero(kwadrat_10, 0, 4, 15, 1e-160, 1e-14) << endl;      // 1.414213562373095

    cout << "Hello, World!" << endl;
    return 0;
}
