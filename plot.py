import matplotlib.pyplot as plt
import numpy as np #Qui importo dal sistema le librerie necessarie, uno con tutte le formule ed il linguaggio matematico, l'altra che invece che contiene gli operatori. Il computer così riuscirà ad eseguire

#1. Carichiamo le costanti ed i dati necessari
#Partiamo organizzando i dati in colonne, che andranno seguite con precisione per tutto il codice

try:
    t_e, x_e, v_e, E_e = np.loadtxt('euler.txt', unpack = True)
    t_ec, x_ec, v_ec, E_ec = np.loadtxt('euler_cromer.txt', unpack = True) #Metto le varibili e assegno subito il metodo, per poi caricare i file e spacchettarli in colonne diverse con unpack e true

except Exception as e:
    print(f"Errore nel caricamento del file: {e}") #Definisco il messaggio TESTUALE di errore, senza codici alfanumerici
    exit() #L'equivalente di return, ma qui posso anche lasciarlo vuoto

#2. Grafico, dopo aver assegnato le variabili. Il grafico sarà in R^2, e quindi farò due grafici distinti per ciò che voglio calcolare, e curo l'estetica. Uso matplotlib e le sue funzioni

plt.figure(figsize=(10,5))
plt.plot(t_e, E_e, label = 'Metodo di Eulero', color = 'crimson', linewidth = 1.5)
plt.plot(t_ec, E_ec, label = 'Metodo Eulero-cromer', color = 'teal', linewidth = 1.5)
plt.xlabel('Tempo $t$', fontsize = 12) #il $ dice a python di scrivere tutto in formato matematico latex
plt.ylabel('Energia meccanica $E$', fontsize = 12)
plt.title('Confronto dei due metodi di integrazione')
plt.legend(fontsize = 11)
plt.grid(True, linestyle= '--', alpha = 0.6)
plt.tight_layout()
plt.savefig('confronto_energia.png', dpi = 300)
print("Grafico dell'energia con il confronto dei due metodi salvato 'confronto_energia.png'")

#3. Secondo grafico: posizione rispetto al tempo
plt.figure(figsize =(10,5))
plt.plot(t_e, x_e, label= 'Posizione con Eulero', color = 'orange', alpha = 0.7)
plt.plot(t_ec, x_ec, label ='Posizione con Eulero Cromer', color = 'blue', alpha = 0.8)
plt.xlabel('Tempo $t$', fontsize = 12)
plt.ylabel('Posizione $x$', fontsize = 12)
plt.title("Traiettoria dell'oscillatore rispetto al tempo", fontsize = 14)
plt.legend(fontsize = 11)
plt.grid(True, linestyle = '--', alpha = 0.6)
plt.tight_layout()
plt.savefig('grafico_traiettoria.png', dpi = 300) #i dpi indicano quanti pixel ho nell'immagine
print("Grafico della traiettoria salvato come 'grafico_traiettoria.png'")

plt.show()
