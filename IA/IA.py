"""
Dans le C++ main a chaque fois que un coup est jouer le C++ envoie un socket de la grille (placer, courant, joker). Ici on calcul alors le coup optimal et on renvoie donc les action a faire (deplacer*x, tourner*y, changerjoker:true/false, etc...)
"""

import socket
import numpy as np

HOST = '127.0.0.1'
PORT = 63424

"Les heuristique"
def aggregateheight(grille):
    heights = []
    for col in range(np.shape(grille)[1]):
        hmax = 0
        for lig in range(np.shape(grille)[0]):
            if grille[lig, col] == 1:
                hmax = lig
        heights.append(hmax)
    return np.sum(heights)

def completelines(grille):
    complete = 0
    for lig in range(np.shape(grille)[0]):
        for col in range(np.shape(grille)[1]):
            if grille[lig, col] == 0:
                break
            elif (col == np.shape(grille)[1]) && (grille[lig, col] == 1):
                complete+=1
    return complete

def hole(grille):
    hole = 0
    for col in range(np.shape(grille)[0]):
        block = False
        for lig in range(np.shape(grille)[0]):
            if grille[lig, col] == 1:
                block = True
            elif block:
                hole += 1
    return hole
            
def bumpiness(grille):
    heights = []
    for col in range(np.shape(grille)[1]):
        hmax = 0
        for lig in range(np.shape(grille)[0]):
            if grille[lig, col] == 1:
                hmax = lig
        heights.append(hmax)
    bump = 0
    for i in range(len(heights)-1):
        bump += np.abs(heights[i] - heights[i+1])
    return bump

"Le score"
def score(grille, a, b, c, d):
    height = aggregateheight(grille)
    lines = completelines(grille)
    holes = hole(grille)
    bumpiness = bumpiness(grille)
    return a*height + b*lines + c*hole + d*bumpiness


def client():
    print("connexion au serveur jeu (C++): {HOST}:{PORT}")
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    print("[+]: IA connecter")
    BUFFER = ''
    while True:
        chunk = s.recv(4096).decode('utf-8')
        if not chunk:
            print("[!]: IA deconnecter")
            break
        buffer += chunk
