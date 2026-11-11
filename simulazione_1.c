#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <math.h>

#define M 1.0

typedef struct {
  double x;
  double v;
} Punto;

typedef struct {
  double dt;
  double omega0;
} Sistema;

//Passaggio del sistema di equazioni differenziali con il puntatore a funzione

double energia(Punto p, Sistema *sist) {
  return 0.5 * (p.v * p.v + (sist->omega0 * sist->omega0) * p.x * p.x);
}
		

typedef Punto(*Derivate)(double t, Punto p, Sistema *sist);

void rk4(double t, Punto *p, Sistema *sist, Derivate f) {
  double dt = sist->dt;
  Punto k1 = f(t, *p, sist);
  Punto tmp = {p->x + 0.5 * dt * k1.x, p->v + 0.5 * dt * k1.v};
  Punto k2 = f(t + 0.5 * dt, tmp, sist);
  tmp.x = p->x + 0.5 * dt * k2.x;
  tmp.v = p->v + 0.5 * dt * k2.v;
  Punto k3 = f(t + 0.5 * dt, tmp, sist);
  tmp.x = p->x + 0.5 * dt * k3.x;
  tmp.v = p->v + 0.5 * dt * k3.v;
  Punto k4 = f(t + 0.5 * dt, tmp, sist);
  p->x += dt / 6.0 * (k1.x + 2.0 * k2.x + 2.0 * k3.x + k4.x);
  p->v += dt / 6.0 * ( k1.v + 2.0 * k2.v + 2.0 * k3.v + k4.v);
}

Punto oscillatore(double t, Punto p, Sistema *sist) { // E' la funzione che viene chiamata dal punatyore a funzione f per calcolare le pendenze e fare le derivate. lei fornisce i dati per calcolare le derivate e le restituisce con una struct d
  Punto d = {p.v, -(sist->omega0 * sist->omega0) * p.x};
    return d;
}

int main (int argc, char *argv[]) {
  if (argc != 9) {
    fprintf(stderr, "I parametri devono essere: %s <metodo> <dt> <tf> <nsteps> <stride> <x0> <v0> <omega0>\n", argv[0]);
    return 1;
  }

  int metodo = atoi(argv[1]);
  int nsteps = atoi(argv[2]);
  int stride = atoi(argv[3]);

  Punto p;
  p.x = atof(argv[4]);
  p.v = atof(argv[5]);

  Sistema sist;
  sist.omega0 = atof(argv[6]);
  sist.dt = atof(argv[7]);

  double tf = atof(argv[8]);

  if(sist.dt <= 0.0 || nsteps <= 0.0 || stride <= 0.0 || p.x < 0.0) {
    fprintf(stderr, "Attenzione: queste variabili o parametri devono essere non negative\n");
    return 1;
  }


  double x0 = p.x;
  double v0 = p.v;
  double omega0 = sist.omega0;
  double t = 0.0;

  for(int n = 1; n <= nsteps; n++) {
    if (metodo == 4) {
      rk4(t, &p, &sist, oscillatore);
    }
    t = n * sist.dt;
    if (n % stride == 0) {
      printf("%f %f %f %f\n", t, p.x, p.v, energia(p, &sist));
    }
  }

  //Calcolo errore
  double x_esatta = x0 * cos(omega0 * tf) + (v0 / omega0) * sin(omega0 * tf);

  double errore_globale = fabs(p.x - x_esatta);

  printf("%e %e\n", sist.dt, errore_globale);

  return 0;
}
  
  

  
