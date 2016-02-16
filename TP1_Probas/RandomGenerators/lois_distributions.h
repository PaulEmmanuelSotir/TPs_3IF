#ifndef LOIS_DISTRIBUTIONS_H
#define LOIS_DISTRIBUTIONS_H

#include <stdlib.h>
#include <stdio.h>

double Alea();
double Exponentielle(double lambda);
double Gauss(double sigma, double m);
double f_inversion();
double f_rejet();

#endif // LOIS_DISTRIBUTIONS_H