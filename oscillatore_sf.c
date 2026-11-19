#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define G 9.81
#define M 1
#define PI 3.14159265358979323846

typedef struct {
  double theta;
  double omega;
} Punto;

typedef struct {
  double dt;
  double q;
  double f;
  double Omega;
} Sistema;

typedef Punto (*Accelerazione) (double t, Punto s, const Sistema *sist);

typedef void (*Integratore) (double t, Punto *s, const Sistema *sist, Accelerazione f);

Punto pendolo (double t, Punto s, const Sistema *sist) {
  Punto d = {s.omega, -sin(s.theta) - sist->q * s.omega + sist->f * cos(sist->Omega *t)};

  return d;
}

double energia(Punto s, const Sistema *sist) {
  double Ec = 0.5 * s.omega * s.omega;
  double Ep = 1.0 - cos(s.theta);

  return Ec + Ep;
}

void rk4 (double t, Punto *s, const Sistema *sist, Accelerazione f) {
  Punto temp;
  
  //K1
  Punto d1 = f(t, *s, sist);
  
  //K2
  temp.theta = s->theta + 0.5 * sist->dt * d1.theta;
  temp.omega = s->omega + 0.5 * sist->dt * d1.omega;
  
  Punto d2 = f(t + 0.5 * sist->dt, temp, sist);
  
  //K3
  temp.theta = s->theta + 0.5 * sist->dt * d2.theta;
  temp.omega = s->omega + 0.5 * sist->dt * d2.omega;
  
  Punto d3 = f(t + 0.5 * sist->dt, temp, sist);
  
  //k4
  temp.theta = s->theta + 0.5 * sist->dt * d3.theta;
  temp.omega = s->omega + 0.5 * sist->dt * d3.omega;
  
  Punto d4 = f(t + sist->dt, temp, sist);
  
  s->theta = s->theta + (sist->dt / 6.0) * (d1.theta + 2.0 * d2.theta + 2.0 * d3.theta + d4.theta);
  s->omega = s->omega + (sist->dt / 6.0) * (d1.omega + 2.0 * d2.omega + 2.0 * d3.omega + d4.omega);
}

int main(int argc, char *argv[]) {
  
  if(argc != 9) {
    fprintf(stderr, "Uso: %s ND  nsteps stride theta0 omega0 q f Omega\n", argv[0]);
    return 1;
  }
  
  Punto s;
  Sistema sist;
  
  int ND = atoi(argv[1]);
  int nsteps = atoi(argv[2]);
  int stride = atoi(argv[3]);
  
  s.theta = atof(argv[4]);
  s.omega = atof(argv[5]);
  
  sist.q = atof(argv[6]);
  sist.f = atof(argv[7]);
  sist.Omega = atof(argv[8]);
  

  if (ND <= 0 || nsteps <= 0 ||
    stride <= 0 || sist.q <= 0 || sist.Omega <= 0) {

    fprintf(stderr, "Errore nei parametri\n");
    return 1;
  }

  //Periodo della forzante
  double TD = 2.0 * PI / sist.Omega;

  //Passo d'integrazione
  sist.dt = TD / ND;

  FILE *fp = fopen("poincare.dat", "w");

  if (fp == NULL) {
    fprintf(stderr, "Errore apertura file\n");
    return 1;
  }

  
  printf("%.10f %.10f %.10f %.10f\n", 0.0, s.theta, s.omega, energia(s, &sist));

  for(int i = 1; i <= nsteps; i++) {
    double t= (i - 1) * sist.dt;
    rk4(t, &s, &sist, pendolo);

    if(i % stride == 0) {
      double t = i * sist.dt;
      printf("%.10f %.10f %.10f %.10f\n", t, s.theta, s.omega, energia(s, &sist));
    }
    if (i % ND == 0) {
      double theta_ridotto = atan2(sin(s.theta), cos(s.theta));
      
      fprintf(fp, "%.10f %.10f\n", theta_ridotto, s.omega);
    }
  }
  fclose(fp);
  return 0;
}
