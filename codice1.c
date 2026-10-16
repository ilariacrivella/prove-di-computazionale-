#include <math.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

#define G  9.81
#define M 1.0
 void euler_cromer_step(double *x, double *v, double dt, double omega0) {
      double x_old = *x;
      double v_old = *v;

      //Ricorda che eulero cromer fa l'opposto di euler: aggiorna prima la velocità e poi la posizione                  

      *v = v_old - (omega0 * omega0 * x_old) * dt;
      *x = x_old + (*v) * dt; //Qui c'è il nuovo valore della velocità                                                  

    }
 void euler_step(double *x, double *v, double dt, double omega0) {
      double x_old = *x;
      double v_old = *v;

      *x = x_old + v_old * dt;
      *v = v_old - (omega0 * omega0 * x_old) *dt;

 }



int main(int argc, char *argv[]) {
  if(argc != 8) {
    fprintf(stderr, "Uso: %s <euler/euler-cromer> <dt> <nsteps> <stride> <x0> <v0> <omega0>\n", argv[0]);
      return  1;
    }
    
    //Convertiamo i parametri in un array argv[] e atoi e atof
    char *metodo = argv[1]; //Il primo argomento memorizza sempre il metodo, è una stringa
    double dt = atof(argv[2]); //dt è un decimale
    int nsteps = atoi(argv[3]); //numero intero
    int stride = atoi(argv[4]); //numero intero
    double x0 = atof(argv[5]); //numero decimale, che indica la posizione iniziale, già definita all'inizio nel main
    double v0 = atof(argv[6]);
    double omega0 = atof(argv[7]);

    //Applichiamo il metodo eulero o eulero-cromer, utilizzando void, che a differenza di int, non ci darà un numero intero, non ci restutuirà nulla. farà semplicemente il lavoro attraverso i puntatori.

   
    //Prima di iniziare il ciclo, poniamo i due metodi che si possono scegliere nel calcolo
    int usa_euler_cromer = 0;
    if(strcmp(metodo, "euler-cromer") == 0) {
      usa_euler_cromer = 1;
    } else if(strcmp(metodo, "euler") != 0) {
      fprintf(stderr, "Errore: metodo sconosciuto. Usa 'euler' oppure 'euler-cromer' .\n");
	return 1;
    }

    //Passiamo al ciclo di integrazione (che definirò in for e poi deciderò quante volte far girare il codice con stride steps, senza riscrivere ogni volta l'indice del risultato sotto il comando printf,) Partiamo con Eulero.

    //Stampiamo le condizioni iniziali

    double t = 0.0;
    double E = 0.5 * v0 * v0 + 0.5 * omega0 * omega0 * x0 * x0; //Energia iniziale
    printf("% .4f % .4f % .4f % .4f\n", t, x0, v0, E);

    //Scriviamo posizione e velocità iniziali, da cui partirà il ciclo di integrazione

    double x = x0;
    double v = v0;

    //Ciclo di integrazione

    for (int step = 1; step <= nsteps; step ++) {
      t = step * dt;
      //Chiamiamo il metodo e definiamo le variabili con i puntatori
      if (usa_euler_cromer) {
	euler_cromer_step(&x, &v, dt, omega0);
      } else {
	euler_step(&x, &v, dt, omega0);
      }
    

      //Controlliamo lo stride per la stampa, per assicurarci che in caso di erroe, errno,h stampi l'errore avvenuto nel programma
      if (step % stride == 0) {
	E = 0.5 * v * v + 0.5 * omega0 * omega0 * x * x; //Energia aggiornata la valore iniziale
	printf("% .4f % .4f % .4f % .4f\n", t, x, v, E);

      }
    }
    return 0;
    }

   
    

    
    
    

    


    

   

    

    
			 
    
    
