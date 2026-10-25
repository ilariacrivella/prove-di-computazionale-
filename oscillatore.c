#include <string.h>
#include <math.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define M 1.0
#define G 9.81

typedef struct {
  double x;
  double v;
  double omega;
  double E;
}Sistema;

  double calcola_energia(Sistema s) {
    return 0.5 * s.v * s.v + 0.5 * s.omega * s.omega * s.x * s.x;
  }

void euler_step(Sistema *s, double dt) {
  double x_vecchia  = s->x; //Salva la veccia posizione prima di aggiornarla

  s->x = s->x + s->v * dt;
  s->v = s->v + (-s->omega * s->omega * x_vecchia) * dt;
}

void euler_cromer(Sistema *s, double dt) {
  double x_vecchia = s->x;

  s->v = s->v + (-s->omega * s->omega * x_vecchia) * dt;
  s->x = s->x + s->v * dt;
}
  
  void velocity_verlet(Sistema  *s, double dt) {
    double a_vecchia = -(s->omega * s->omega * s->x);
    
    s->x = s->x + s->v * dt + 0.5 * a_vecchia * dt * dt;
    double a_nuova = -s->omega * s->omega * s->x;
    s->v = s->v + 0.5 * (a_vecchia + a_nuova) * dt;
  }



int main(int argc, char *argv[]) {
  if (argc !=8) {
    fprintf(stderr,"Uso corretto dei parametri: %s <metodo> <dt> <nsteps> <stride> <x0> <v0> <omega0>\n", argv[0]);
    return 1;
  }

  char *metodo = argv[1];
  double dt = atof(argv[2]);
  int nsteps = atoi(argv[3]);
  int stride = atoi(argv[4]);
  double x0 = atof(argv[5]);
  double v0 = atof(argv[6]);
  double omega0 = atof(argv[7]);

  Sistema s;
  s.x = x0;
  s.v = v0;
  s.omega = omega0;
  
  s.E = calcola_energia(s);
  double t = 0.0;

  double max_errore = 0.0;
  double E_iniziale = s.E;
  
  for (int i = 1; i <= nsteps; i ++) {
    t = t + dt;
    if(strcmp(metodo, "euler") == 0) {
      euler_step(&s, dt);
    } else if(strcmp(metodo, "euler-cromer") == 0) {
      euler_cromer(&s, dt);
    } else if(strcmp(metodo, "velocity-verlet") == 0) {
      velocity_verlet(&s, dt);
    }

    s.E = calcola_energia(s);

    double errore = fabs(s.E - E_iniziale);
    if(errore > max_errore) {
      max_errore = errore;
    }

    if(i % stride == 0) {
      printf("%f %f %f %f\n", t, s.x, s.v, s.E);

    }

  }

  printf("%f %f\n", dt, max_errore);
  
  return 0;
}
      
    
