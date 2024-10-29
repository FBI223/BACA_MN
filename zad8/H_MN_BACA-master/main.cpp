//Marcin Sztukowski

#include "source.h"


int main(int argc, char** argv) {


    cout << fixed;
    cout.precision(15);

    int size = 6;
    double xx[] = {0, 0.2, 0.4, 0.6, 0.8, 1};
    double yy[] = {-3,-2.56,-2.04,-1.44,-0.76,0};

    spline s(size);
    s.set_points(xx, yy);

    for(int i=0; i < size - 1; i++) {
        std::cout << s(xx[i]) << "  " << s(xx[i]+0.02) << "  "<< s(xx[i]+0.07) <<  std::endl;
    }

    return 0;
}
