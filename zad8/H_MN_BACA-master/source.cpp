//Marcin Sztukowski

#include "source.h"


spline::spline(int nn) : n(nn) {
    a.resize(n);
    b.resize(n-1);
    c.resize(n);
    d.resize(n-1);
}

void spline::set_points(const double* xs, const double* ys) {
    xx.assign(xs, xs + n);
    yy.assign(ys, ys + n);

    vector<double> h(n-1);

    vector<double> alpha(n-1, 0.0);

    vector<double> l(n, 0.0);
    vector<double> m(n, 0.0);
    vector<double> z(n, 0.0);

    for (int i = 0; i < n - 1; i++ ) {
        h[i] = xx[i+1] -xx[i];
    }

    for (int i = 1; i < n - 1; i++)
        {
        alpha[i] = 3.0 * ( yy[i+1] -  yy[i] ) /
            h[i] - (3.0 *(yy[i] - yy[i-1])/ h[i-1]);
    }

    l[0] = 1.0;
    z[0] = 0.0;
    m[0] = 0.0;

    for (int i = 1; i < n - 1; i++) {
        l[i]  = 2.0 * (xx[i+1] - xx[i-1]) - h[i-1] * m[i-1];
        m[i]  = h[i]/ l[i];
        z[i] = (alpha[i] - h[i-1] * z[i-1]) / l[i];
    }

    l[n-1] = 1.0;
    z[n-1] = 0.0;

    c[n-1] = 0.0;
    for (int j = n-2; j >= 0; j--) {
        c[j] = z[j] - m[j] * c[j+1];
        b[j] = (yy[j+1] - yy[j]) / h[j] - h[j] * (c[j+1] + 2.0 * c[j]) / 3.0;

        d[j] = (c[j+1] - c[j]) / (3.0 * h[j]);
        a[j] = yy[j];
    }
}

double spline::operator()(double z) const {
    if (xx.empty()) return 0;

    // znajdź segment, który zawiera z
    int i = lower_bound(xx.begin(), xx.end(), z) - xx.begin() - 1;
    i = std::max(i, 0);

    double dx = z - xx[i];
    return a[i] + b[i] * dx + c[i] * dx * dx + d[i] * dx * dx * dx;
}

