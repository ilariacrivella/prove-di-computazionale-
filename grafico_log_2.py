import subprocess
import os
import numpy as np
import matplotlib.pyplot as plt

dts = [0.1, 0.05, 0.02, 0.01, 0.005, 0.002, 0.001]
metodi = ["rk2", "rk4"]
x0, v0, t0, omega0, gamma = "1.0", "0.0", "0.0", "5.0", "0.5"

plt.figure(figsize=(9, 7))

# 1. Ciclo principale sui metodi e sui dt
for metodo in metodi:
    errori_massimi = []
    
    for dt_val in dts:
        nsteps_val = int(10.0 / dt_val)
        nome_file = f"dati_{metodo}_dt_{dt_val}.txt"
        
        # Scrittura output da C
        with open(nome_file, "w") as f:
            subprocess.run(
                ["./oscillatore_smorzato", metodo, str(dt_val), str(nsteps_val), "10", x0, v0, t0, omega0, gamma],
                stdout=f,
                check=True
            )
        
        # Lettura errore
        with open(nome_file, "r") as f:
            righe = f.readlines()
            
        ultima_riga = righe[-1].strip().split()
        errore_max = float(ultima_riga[1])
        errori_massimi.append(errore_max)
        
        # Pulizia file temporaneo
        os.remove(nome_file)
    
    # Plot della curva per il metodo corrente (INTERNO al ciclo dei metodi, ma ESTERNO al ciclo dei dt)
    plt.loglog(dts, errori_massimi, marker='o', linestyle='-', label=f"Metodo {metodo.upper()}")

# 2. Linee teoriche e formattazione (ESTERNE a tutti i cicli, così usa i dati completi)
dts_arr = np.array(dts)
plt.loglog(dts_arr, dts_arr**2 * (errori_massimi[0] / (dts_arr[0]**2)), 'k--', alpha=0.5, label="Teorico $O(dt^2)$")
plt.loglog(dts_arr, dts_arr**4 * (errori_massimi[0] / (dts_arr[0]**4)), 'k-.', alpha=0.5, label="Teorico $O(dt^4)$")

plt.xlabel("Passo temporale $dt$ (scala logaritmica)", size=12)
plt.ylabel("Errore massimo (scala logaritmica)", size=12)
plt.title("Confronto dei metodi RK2 e RK4", size=14)
plt.grid(True, which="both", linestyle="--", alpha=0.6)
plt.legend()

# 3. Salvataggio e visualizzazione corretti
plt.tight_layout()                          # <-- Con il trattino basso!
plt.savefig("grafico_convergenza.png", dpi=300)
plt.show()
