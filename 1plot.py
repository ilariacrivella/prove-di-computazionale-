import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

#Carichiamo i dati
t_e, x_e = np.loadtxt('euler.txt', unpack = True, usecols=(0, 1)) #usiamo le prime due colonne, che python sa prendere
t_ec, x_ec = np.loadtxt('euler_cromer.txt', unpack = True, usecols=(0, 1))

#1. facciamo l'animazione dei due moti con i metodi eulero ed eulero cromer

#Imposto di nuovo il grafico(le variabili al limite le prendo dai grafici calcolati prima per rendere il tutto coerente, lascerò semplicemente un po' più di spazio affinché la pallina non tocchi esattamente il bordo

fig, ax = plt.subplots(figsize =(8,4))
ax.set_xlim(0,100)
ax.set_ylim(-1.2, 1.2)
ax.set_xlabel('Tempo $t$')       #Lascio un po' di margine sugli assi x e y 
ax.set_ylabel('Posizione $x$')
ax.set_title("Animazione dell'oscillatore armonico, Eulero ed Eulero Cromer")
ax.grid(True, linestyle= '--', alpha = 0.6)

#Creiamo, dopo aver fatto il grafico, l'oggetto che andrò ad animare (un punto materiale)

punto_e, = ax.plot([], [], 'ro', markersize = 6, label= 'Punto') #marcatore o per il punto, rosso r, red
linea_traccia_e, = ax.plot([], [], 'b-', alpha = 0.4, label = 'Traiettoria')  #linea continua -, blu b

punto_ec, = ax.plot([], [], 'go', markersize = 6, label = 'Punto Euler cromer')
linea_traccia_ec, = ax.plot([], [], 'g-', alpha = 0.3, label = ' Traiettoria Ec')

#Le parentesi quadre sono chiuse perché ancora non ho definito ciò che metterò nell'animazione, meterò solo gli oggetti. La virgola dopo punto e linea traccia serve a concentare tutto in un punto nell'animazione

#facciamo in modo che nel grafico tutto parta da zero

def init():
    punto_e.set_data([], [])
    linea_traccia_e.set_data([],[])
    punto_ec.set_data([],[])
    linea_traccia_ec.set_data([],[])
    return punto_e, linea_traccia_e, punto_ec, linea_traccia_ec
def update(i): #aggiorno l'animazione ad ogni frame per ogni indice i. In python i due punti esprimono una parentesi op un ciclo in questo caso
    punto_e.set_data([t_e[i]], [x_e[i]])
    linea_traccia_e.set_data([t_e[:i]], [x_e[:i]])
    punto_ec.set_data([t_ec[i]], [x_ec[i]])
    linea_traccia_ec.set_data([t_ec[:i]], [x_ec[:i]])
    

    #idue punti segnano la traiettoria e l'intervallo di tempo della traoettoria disegnata fino al momento t percorso dal punto

    return punto_e, linea_traccia_e, punto_ec, linea_traccia_ec
#Creiamo l'animazione, il movimento
anim = animation.FuncAnimation(
    fig, update, init_func=init,
    frames=len(t_e), interval = 30 , blit = True
    )
plt.legend()
plt.show()
