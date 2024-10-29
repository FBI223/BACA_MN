//Marcin Sztukowski

#ifndef SPLINE_H
#define SPLINE_H

#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

class spline {
    vector<double> xx, yy;  // Węzły i ich wartości
    vector<double> a, b, c, d;  // Współczynniki splines
    int n;  // Liczba węzłów

public:
    spline(int nn);
    void set_points(const double* xs, const double* ys);
    double operator()(double z) const;
};

#endif
