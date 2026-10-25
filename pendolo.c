#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define M 1.0
#define G 9.81

typedef struct {
  double t;
  double theta;
  double omega;
  double E;
} Stato;

double alfa(double L, double theta) {
  return -(G / L) * sin(theta);
}

double E(double L, double theta, double omega) {
  return 0.5 * (M * L * L * omega * omega) + M * G * L * (1 -cos(theta));
}
							  

int main(int argc, char *argv[]) {
  if (argc != 7) {
    fprintf(stderr, "Uso corretto: %s dt nsteps stride theta0 omega0 length\n", argv[0]);
      return 1;
  }

  double dt = atof(argv[1]);
  int nsteps = atoi(argv[2]);
  int stride = atoi(argv[3]);
  double theta0 = atof(argv[4]);
  double omega0 = atof(argv[5]);
  double length = atof(argv[6]);
  double E_nuova = E(length, theta0, omega0);


double t = 0.0;
double theta = theta0;
double omega = omega0;

for (int  i = 1; i <= nsteps; i++) {
  double alfa_vecchia = alfa(length, theta);
  double theta_nuova = theta + omega * dt + 0.5 * (alfa_vecchia * dt * dt);
  double alfa_nuova = alfa(length, theta_nuova);
  double omega_nuova = omega + 0.5 * (alfa_vecchia + alfa_nuova) * dt;

  theta = theta_nuova;
  omega = omega_nuova;
  t = t + dt;
  
  if(i % stride == 0) {
    printf("%f %f %f %f \n", t, theta, omega, E_nuova);
  }
 }

 return 0;
}
