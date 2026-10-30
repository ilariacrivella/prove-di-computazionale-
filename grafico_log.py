import matplotlib.pyplot as plt
import numpy as np
import subprocess

#Lista dei passi e dei metodi da testare (li calcola python)

dts = [0.1, 0.05, 0.02, 0.01, 0.005, 0.002, 0.001]
metodi = ["rk2", "rk4"]

#Parametri fissi del sistema

x0, v0, t0, omega0, gamma = "1.0", "0.0", "0.0", "5.0", "0.5"

plt.figure(figsize=(9,7))

#Doppio ciclo:

for metodo in metodi:
    errori_massimi = []

    for dt_val in dts:
        nsteps_val = int(10.0  / dt_val)
        nome_file = f"dati_{metodo}_dt_v{dt_val}.txt"

        #Eseguiamo di nuovo il programma in C a prescindere dalla riga di comando

        with open(grafico_loglog.txt, "w") as f:
            subprocess.run(x
            [
                "./oscillatore_smorzato",
                metodo,
                str(dt_val),
                str(nsteps_val),
                "10", #stride
                x0, v0, t0, omega0, gamma
            ],
            stdout = f,
            check = True
            )

            #Leggiamo il file appena creato per ottenere l'errore
