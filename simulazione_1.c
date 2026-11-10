#include <stdio.h>
#include <stlib.h>
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

void oscillatore(double t, Punto *p, Punto *dpdt, Sistema *s) {
  dpdt->x = p.v;
  dpdt->v = -(s->omega0 * s->omega0) * p.x;
}

typedef void(*FunzioneDerivata)(double, 

void rk4(double t, Punto *p, Sistema *s, 
