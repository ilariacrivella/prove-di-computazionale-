#include <math.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h> //Esempio di oscillatore sottosmorzato. Primo codice

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
  return 0.5 * s.v * s.v + 0.5 * omega0 * omega0 * x * x;
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
    prinf("Energia iniziale: %f\n", E_iniziale);
  double max_errore = 0.0

  
  for(int i = 0; i<= nsteps; i ++) {
    s.t += dt;
    if(strcmp(metodo, "rk2") == 0) {
      rk2(&s, dt);
    } else if(strcmp(metodo, "rk4") == 0 {
	rk4(&s, dt);
      }

      double E = calcola_energia(s);

       double errore = fabs(E - E_iniziale);
    if(errore > max_errore) {
      max_errore = errore;
    }  //Ricorda poi di mettere l'altro errore stasera

    if(i % stride == 0) {
      printf("%f %f %f %f\n", s.t, s.x, s.v, E);

    }

  }

  printf("%f %f\n", dt, max_errore);

  return 0;
}

