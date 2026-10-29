
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  double x;
  double v;
} Point;

typedef struct {
  double dt;
  double omega0;
} Sist;

typedef void (Integratore)(Point, Sist*);

double accelerazione (Point p, Sist s) {
  return -s.omega0 * s.omega0 * p.x;
}

double energia(Point p, Sist s) {
  double Ec = 0.5 * p.v * p.v;
  double Ep = 0.5 * s.omega0 * s.omega0 * p.x * p.x;

  return Ec + Ep;
}


double posizione_esatta(double t, double x, double v, double omega0) {
    return x * cos(omega0 * t) + (v / omega0) * sin(omega0 * t);
}

void euler(Point *p, Sist *s) {
  double a = accelerazione(*p, *s); //accelerazione attuale

  double x1 = (*p).x + (*p).x * (*s).dt; //nuova posizione
  double v1 = (*p).v + a * (*s).dt; //nuova volocità

  //aggiornamento struttura
  (*p).x = x1;
  (*p).v = v1;
}

void euler_cromer(Point *p, Sist *s) {
  double a = accelerazione(*p, *s);

  double v1 = (*p).v + a * (*s).dt;
  double x1 = (*p).x + v1 * (*s).dt;

  (*p).x = x1;
  (*p).v = v1;
}

void velocity_verlet(Point *p, Sist *s) {
  double a = accelerazione(*p, *s);

  //aggiornamento posizione
  double x1 = (*p).x + (*p).v * (*s).dt + 0.5 * a * (*s).dt * (*s).dt;
  (*p).x = x1;

  //calcolo nuova accelerazione
  double a1 = accelerazione(*p, *s);

  //aggiornamento velocità
  double v1 = (*p).v + 0.5 * (a + a1) * (*s).dt;
  (*p).v = v1;
}

int main(int argc, char *argv[]) {

  if(argc != 6) {
    printf("Uso: %s metodo nsteps x v omega\n", argv[0]);
    return 1;
  }

  char *metodo = argv[1];
  int nsteps = atoi(argv[2]);
  double x = atof(argv[3]);
  double v = atof(argv[4]);
  double omega0 = atof(argv[5]);

  Integratore integratore;

  if(strcmp(metodo, "euler") == 0) {
    integratore = euler;
  } else if(strcmp(metodo, "euler-cromer") == 0) {
    integratore = euler_cromer;
  } else if(strcmp(metodo, "velocity-verlet") == 0) {
    integratore = velocity_verlet;
  } else {
    printf("Metodo non valido\n");
    return 1;
  }

  //controllo degli argomenti
  if (omega0 <= 0 || nsteps < 32) {
    fprintf(stderr, "Errore: omega0 deve essere positiva e nsteps almeno 32\n");
    return 1;
  }

  //inizializzazione delle strutture
  Point p;
  p.x = x;
  p.v = v;

  Sist s;
  s.omega0 = omega0;

  double A = sqrt(x * x + (v / omega0) * (v / omega0));

  if (A == 0.0) {
    fprintf(stderr, "Errore: ampiezza nulla\n");
    return 1;
  }

  //Ciclo dei diversi valori di dt
  double passi[] = {0.001, 0.002, 0.004, 0.008, 0.016, 0.032, 0.064};

  double tf = nsteps * 0.001;

  for(int j = 0; j < 7; j++){

    double dt = passi[j];
    int passi_effettivi = (int)round(tf / dt);

    p.x = x;
    p.v = v;

    s.dt = tf / passi_effettivi;

    for(int step = 1; step <= passi_effettivi; step++) {
      integratore(&p, &s);
    }

    double x_esatta = posizione_esatta(tf, x, v, omega0);
    double errore = fabs(p.x - x_esatta) / A;
    printf("%.6f %.10e\n", s.dt, errore);
  }

  return 0;

}
