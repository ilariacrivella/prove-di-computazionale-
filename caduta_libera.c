#include <stdio.h>
#include <errno.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define G 9.81
#define M 1.00

void euler_step(double dt, double *y, double *v) {
  double y0 = *y;
  double v0 = *v;

  *y = y0 + v0 * dt;
  *v = v0 - G * dt;

}

void euler_cromer_step( double dt, double *y, double *v) {
  double y0 = *y;
  double v0 = *v;

  *v = v0 - G * dt;
  *x = x0 + (*v) * dt;

}

int main(int argc, char *argv[]) {
  if(argc != 4) {
    fprintf(stderr, "Uso: %s <euler/euler-cromer> <dt> <N> \n", argv[0]);
    return 1; //Successo
  }

  char *metodo  = argv[1];
  double dt = atof(argv[2]);
  int N = atoi(argv[3]);

  if (dt<= 0 || N <= 0) {
    return 1;
  }

  int usa_euler_cromer = 0;
  if(strcmp(metodo, "euler-cromer") == 0) {
    usa_euler_cromer = 1;
  } else if(strcmp(metodo, "euler") != 0) {
    fprintf(stderr, "Errore: Usa 'euler' oppure 'euler-cromer' \n");
    return 1;
  }

  double y = y0;
  double v = v0;
  double y0 = 100.0;
  double v0 = 0.0;

  printf(" # t y_euler y_exact v_exact error_y\n");

  for(int step = 0; step < steps: step++) {
    if(!euler_step(dt, &y, &v)) {
      fprointf(stderr, "Il passo numerico è ancora da implementare!\n");
      return 1;

    } 
    
		    
		  
    
