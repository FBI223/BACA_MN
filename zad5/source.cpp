// Marcin Sztukowski

#include <iostream>
#include "funkcja.h"
#include <iomanip>
#include <cmath>



using namespace std;


template <typename T>
class Jetta {
public:

    T f;
    T fx;
    T fy;
    T fxx;
    T fxy;
    T fyy;



    // OK
    Jetta() : f(0), fx(0), fy(0), fxx(0), fxy(0) , fyy(0) {}
    Jetta(T f_in, T fx_in, T fy_in, T fxx_in, T fxy_in, T fyy_in) : f(f_in), fx(fx_in), fy(fy_in), fxx(fxx_in), fxy(fxy_in) , fyy(fyy_in) {}
    Jetta(const Jetta& other) : f(other.f), fx(other.fx), fy(other.fy), fxx(other.fxx), fxy(other.fxy) , fyy(other.fyy) {}




    // OK
    Jetta operator-() const {

        Jetta<T> wynik;
        wynik.f = (-1)*this->f ;

        wynik.fx = (-1)*this->fx ;
        wynik.fy = (-1)*this->fy  ;



        wynik.fxx = (-1)*this->fxx  ;
        wynik.fxy = (-1)*this->fxy  ;
        wynik.fyy = (-1)*this->fyy  ;

        return wynik;
    }


    // OK
    Jetta& operator=(const Jetta& other)  {

        if ( this != &other )
        {
            this->f =  other.f ;
            this->fx =  other.fx ;
            this->fy =  other.fy ;

            this->fxx =  other.fxx ;
            this->fxy =  other.fxy ;
            this->fyy = other.fyy ;
        }

        return *this;
    }


    // OK
    Jetta operator+(const Jetta& other) const {

        Jetta<T> wynik;
        wynik.f = this->f + other.f ;

        wynik.fx = this->fx + other.fx ;
        wynik.fy = this->fy + other.fy ;



        wynik.fxx = this->fxx + other.fxx ;
        wynik.fxy = this->fxy + other.fxy ;
        wynik.fyy = this->fyy + other.fyy ;

        return wynik;
    }

    // OK
    Jetta operator-(const Jetta& other) const {

        Jetta<T> wynik;
        wynik.f = this->f - other.f ;

        wynik.fx = this->fx - other.fx ;
        wynik.fy = this->fy - other.fy ;



        wynik.fxx = this->fxx - other.fxx ;
        wynik.fxy = this->fxy - other.fxy ;
        wynik.fyy = this->fyy - other.fyy ;

        return wynik;
    }



    //OK
    Jetta operator*(const Jetta& other) const {

        Jetta<T> wynik;
        wynik.f = this->f * other.f ;

        wynik.fx = this->fx*other.f + this->f * other.fx ;
        wynik.fy = this->fy*other.f + this->f * other.fy   ;

        wynik.fxx = this->f * other.fxx +  2 * this->fx * other.fx + this->fxx * other.f ;
        wynik.fyy = this->f * other.fyy +  2 * this->fy * other.fy + this->fyy * other.f ;
        wynik.fxy = this->f * other.fxy +   this->fx * other.fy + this->fy * other.fx  + this->fxy * other.f ;

        return wynik;
    }


    Jetta operator/(const Jetta& other) const {

        Jetta<T> wynik;
        wynik.f = this->f / other.f ;

        wynik.fx = ( this->fx - (this->f / other.f ) * other.fx ) / ( other.f )  ;
        wynik.fy = ( this->fy - (this->f / other.f ) * other.fy ) / ( other.f )  ;

        wynik.fxx = ( this->fxx - 2 * wynik.fx * other.fx - (this->f / other.f ) * other.fxx  )/(other.f) ;
        wynik.fyy = ( this->fyy - 2 * wynik.fy * other.fy - (this->f / other.f ) * other.fyy  )/(other.f) ;
        wynik.fxy = ( this->fxy -  wynik.fy * other.fx - wynik.fx * other.fy - (this->f / other.f ) * other.fxy  )/(other.f) ;

        return wynik;
    }

















    // OK
    friend Jetta sin(const Jetta& dzet)
    {

        Jetta<T> wynik;

        T sin_temp = std::sin(dzet.f) ;
        T cos_temp = std::cos(dzet.f) ;

        wynik.f = sin_temp;
        wynik.fx = cos_temp * dzet.fx ;
        wynik.fy = cos_temp * dzet.fy ;


        wynik.fxx = -sin_temp * dzet.fx * dzet.fx + cos_temp * dzet.fxx ;
        wynik.fyy = -sin_temp * dzet.fy * dzet.fy + cos_temp * dzet.fyy ;
        wynik.fxy = -sin_temp * dzet.fy * dzet.fx + cos_temp * dzet.fxy ;


        return wynik ;
    }


    //OK
    friend Jetta cos(const Jetta& dzet)
    {
        Jetta<T> wynik;

        T sin_temp = std::sin(dzet.f) ;
        T cos_temp = std::cos(dzet.f) ;

        wynik.f = cos_temp;
        wynik.fx = -sin_temp * dzet.fx ;
        wynik.fy = -sin_temp * dzet.fy ;



        wynik.fxx = -cos_temp * dzet.fx * dzet.fx - sin_temp * dzet.fxx ;
        wynik.fyy = -cos_temp * dzet.fy * dzet.fy - sin_temp * dzet.fyy ;
        wynik.fxy = -cos_temp * dzet.fy * dzet.fx - sin_temp * dzet.fxy ;


        return wynik ;
    }


    // OK
    friend Jetta exp(const Jetta& dzet ){
        Jetta<T> wynik;

        T ef = std::exp(dzet.f);
        wynik.f = ef ;

        wynik.fx = ef * dzet.fx ;
        wynik.fy = ef * dzet.fy ;



        wynik.fxx = ef * dzet.fx * dzet.fx + ef * dzet.fxx ;
        wynik.fyy = ef * dzet.fy * dzet.fy + ef * dzet.fyy ;
        wynik.fxy = ef * dzet.fy * dzet.fx + ef * dzet.fxy ;

        return wynik ;
    }




















    Jetta operator+( T constant ) const {

        Jetta<T> wynik;
        wynik.f = this->f + constant ;

        wynik.fx = this->fx  ;
        wynik.fy = this->fy ;


        wynik.fxx = this->fxx  ;
        wynik.fxy = this->fxy ;
        wynik.fyy = this->fyy  ;

        return wynik;
    }


    Jetta operator-( T constant ) const {

        Jetta<T> wynik;
        wynik.f = this->f - constant ;

        wynik.fx = this->fx  ;
        wynik.fy = this->fy ;


        wynik.fxx = this->fxx  ;
        wynik.fxy = this->fxy ;
        wynik.fyy = this->fyy  ;

        return wynik;
    }

    Jetta operator*( T constant ) const {

        Jetta<T> wynik;
        wynik.f = this->f * constant ;

        wynik.fx = this->fx * constant ;
        wynik.fy = this->fy * constant;


        wynik.fxx = this->fxx * constant ;
        wynik.fxy = this->fxy * constant;
        wynik.fyy = this->fyy * constant ;

        return wynik;
    }


    Jetta operator/( T constant ) const {

        Jetta<T> wynik;
        wynik.f = this->f / constant ;

        wynik.fx = this->fx / constant  ;
        wynik.fy = this->fy / constant ;


        wynik.fxx = this->fxx / constant  ;
        wynik.fxy = this->fxy / constant ;
        wynik.fyy = this->fyy / constant  ;

        return wynik;
    }





















    friend Jetta<T> operator*( T literal, const Jetta<T>& other) {
        Jetta<T> wynik;
        wynik.f = literal * other.f;
        wynik.fx = literal * other.fx;
        wynik.fy = literal * other.fy;



        wynik.fxx = literal * other.fxx;
        wynik.fxy = literal * other.fxy;
        wynik.fyy = literal * other.fyy;

        return wynik;
    }

    friend Jetta<T> operator/( T literal, const Jetta<T>& other) {
        Jetta<T> wynik;
        wynik.f = literal / other.f;
        wynik.fx = literal * other.fx;
        wynik.fy = literal * other.fy;



        wynik.fxx = literal / other.fxx;
        wynik.fxy = literal / other.fxy;
        wynik.fyy = literal / other.fyy;

        return wynik;
    }

    friend Jetta<T> operator+( T literal, const Jetta<T>& other) {
        Jetta<T> wynik;
        wynik.f = literal + other.f;
        wynik.fx = other.fx;
        wynik.fy =  other.fy;



        wynik.fxx =  other.fxx;
        wynik.fxy =  other.fxy;
        wynik.fyy =  other.fyy;

        return wynik;
    }

    friend Jetta<T> operator-( T literal, const Jetta<T>& other) {
        Jetta<T> wynik;
        wynik.f = literal - other.f;
        wynik.fx =  -other.fx;
        wynik.fy =  -other.fy;



        wynik.fxx =  -other.fxx;
        wynik.fxy =  -other.fxy;
        wynik.fyy =  -other.fyy;

        return wynik;
    }


















    void calculate(T x_in , T y_in)
    {

        Jetta<T> x_jetta ;
        x_jetta.f = x_in;
        x_jetta.fx = 1.0;
        Jetta<T> y_jetta ;
        y_jetta.f = y_in;
        y_jetta.fy = 1.0;

        *this = funkcja(x_jetta,y_jetta) ;

    }


    void print() const {
        cout << fixed << setprecision(15);
        cout << f << " " << fx << " " << fy << " " << fxx << " " << fxy << " " << fyy << endl;
    }


};


int main() {

    int m;
    cin >> m ;

    double x_in ;
    double y_in;

    for ( int i = 0 ; i < m ; i++ )
    {

        cin >> x_in;
        cin >> y_in;

        Jetta<double> wynik ;
        wynik.calculate(x_in,y_in) ;
        wynik.print() ;



    }


    return 0;
}