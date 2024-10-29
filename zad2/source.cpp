//Marcin Sztukowski

#include <iostream>
#include <cmath>

using namespace std;



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
    double przelacznik = 0.1 ;


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