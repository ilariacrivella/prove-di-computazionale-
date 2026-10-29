#include <math.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h> //Esempio di oscillatore sottosmorzato. Primo codice

#define M 1.0

typedef struct {
  double x;
  double v;
  double t; //Qui la velocità serve per spezzare il sistema del secondo ordine

  double omega0;
  double gamma; //Costanti fisse
}Sistema;

//Definiamo il sistema di equazioni differenziali, da far chiamare al main. E' il sistema principale

double derivata_x(Sistema s) {
  return s.v;
}
double accelerazione(Sistema s) {
  return -(s.omega0 * s.omega0) * s.x - s.gamma * s.v;
}

double calcola_energia(Sistema s) {
  return 0.5 * s.v * s.v + 0.5 * s.omega0 * s.omega0 * s.x * s.x;
}

double x_analitica(Sistema s, double x0, double v0) {
  double beta = s.gamma / 2.0;
  double omega_sq = (s.omega0 * s.omega0) - (s.gamma * s.gamma) / 4.0;

  // Regime sottosmoezato ( omega^2 > 0)
  if (omega_sq > 0) {
    double omega = sqrt(omega_sq);
    double A = x0;
    double B = (v0 + beta * x0) / omega;
    return exp(-beta * s.t) * (A * cos(omega * s.t) + B * sin(omega * s.t));
  }
  //Regime critico (omega^2 == 0)
  else if (fabs(omega_sq) < 1e-9) {
    double A = x0;
    double B = v0 + beta * x0;
    return exp(-beta * s.t) * (A + B * s.t);
  }
  //Regime sovrasmorzato (omega^2 < 0)
  else {
    double alpha = sqrt(-omega_sq);
    double A = 0.5 * (x0 +(v0 + beta * x0) / alpha);
    double B = 0.5 * (x0 -(v0 + beta * x0) / alpha);
    
}
}


void rk2(Sistema *s, double dt) {
  double x0 = s->x;
  double v0 = s->v;

  double kx1 = v0;
  double kv1 = accelerazione(*s); //Calcoliamo la prima derivata,k1

  //Creiamo uno stato temporaneo a dt/2

  Sistema temp = *s;
  temp.x = x0 + 0.5 * dt * kx1;
  temp.v = v0 + 0.5 * dt * kv1;

  //Calcola k2 nel punto medio

  double kx2 = temp.v;
  double kv2 = accelerazione(temp);

  s->x = x0 + dt * kx2;
  s->v = v0 + dt * kv2;

}

void rk4(Sistema *s, double dt) {
  double x0 = s->x;
  double v0 = s->v;

  double kx1 = v0;
  double kv1 = accelerazione(*s);

  Sistema temp = *s;
  temp.x = x0 + 0.5 * dt * kx1;
  temp.v = v0 + 0.5 * dt * kv1;

  double kx2 = temp.v;
  double kv2 = accelerazione(temp);

  Sistema temp_2 = *s;
  temp_2.x = x0 + 0.5 * dt * kx2;
  temp_2.v = v0 + 0.5 * dt * kv2;

  double kx3 = temp_2.v;
  double kv3 = accelerazione(temp_2);

  Sistema temp_3 = *s;
  temp_3.x = x0 + dt * kx3;
  temp_3.v = v0 + dt * kv3;

  double kx4 = temp_3.v;
  double kv4 = accelerazione(temp_3);

  s->x = x0 +(dt / 6.0) * (kx1 + 2.0 * kx2 + 2.0 * kx3 + kx4); //Moltiplicazione per i coefficient della media pesata e raccoglimento a fattor comune
  s->v = v0 + (dt / 6.0) * (kv1 + 2.0 * kx2 + 2.0 * kx3 + kv4);
}

//Qui metti i due metodi con void per il calcolo dei coefficienti

int main(int argc, char *argv[]) {
  if(argc != 10) {
    fprintf(stderr,"Parametri errati: %s <metodo> <dt> <nsteps> <stride> <x0> <v0> <t0> <omega0> <gamma>\n", argv[0]);
    return 1;
  }

  char *metodo = argv[1];
  double dt = atof(argv[2]);
  int nsteps = atoi(argv[3]);
  int stride = atoi(argv[4]);
  double x0 = atof(argv[5]);
  double v0 = atof(argv[6]);
  double t0 = atof(argv[7]);
  double omega0 = atof(argv[8]);
  double gamma = atof(argv[9]);

  Sistema s; //Condizioni iniziali
  s.x = x0;
  s.v = v0;
  s.t = t0;
  s.omega0 = omega0;
  s.gamma = gamma;
  double E_iniziale = calcola_energia(s);
    printf("Energia iniziale: %f\n", E_iniziale);

    double max_errore = 0.0;
  
  for(int i = 0; i<= nsteps; i ++) {
    if(strcmp(metodo, "rk2") == 0) {
      rk2(&s, dt);
    } else if(strcmp(metodo, "rk4") == 0) {
	rk4(&s, dt);
      }
    
      double E = calcola_energia(s);
      double x_esatta = x_analitica(s, x0, v0);
      double errore = fabs(x_esatta - s.x);
      if (errore > max_errore) {
	max_errore = errore;
      }
      
    if(i % stride == 0) {
      printf("%f %f %f %f\n", s.t, s.x, s.v, E);

    }
      s.t += dt;

  }

  return 0;
}

