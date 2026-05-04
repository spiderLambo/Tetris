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
    h, w = np.shape(grille)
    for col in range(w):
        height = 0
        for lig in range(h):
            if grille[lig, col] == 1:
                height = h - lig
        heights.append(height)
    return np.sum(heights)

def completelines(grille):
    complete = 0
    for lig in range(np.shape(grille)[0]):
        for col in range(np.shape(grille)[1]):
            if grille[lig, col] == 0:
                break
            elif (col == np.shape(grille)[1]) and (grille[lig, col] == 1):
                complete+=1
    return complete

def hole(grille):
    h, w = np.shape(grille)
    total = 0
    for col in range(w):
        block = False
        for lig in range(h):
            if grille[lig, col] == 1:
                block = True
            elif block:
                total += 1
    return total
            
def bumpiness(grille):
    heights = []
    h, w = np.shape(grille)
    for col in range(w):
        height = 0
        for lig in range(h):
            if grille[lig, col] == 1:
                height = h - lig
        heights.append(height)
    bump = 0
    for i in range(len(heights)-1):
        bump += np.abs(heights[i] - heights[i+1])
    return bump

"Le score"
def score(grille, a, b, c, d):
    height = aggregateheight(grille)
    lines = completelines(grille)
    holes = hole(grille)
    bump = bumpiness(grille)
    return a*height + b*lines + c*hole + d*bump

"optimisation de a, b, c, d"



"Jeu"
Tetromino = {
    'I': np.array([[0, 0, 0, 0], [1, 1, 1, 1], [0, 0, 0, 0], [0, 0, 0, 0]]),
    'O': np.array([[0, 0, 0, 0], [0, 1, 1, 0], [0, 1, 1, 0], [0, 0, 0, 0]]),
    'T': np.array([[0, 0, 0, 0], [0, 0, 0, 0], [0, 1, 1, 1], [0, 0, 1, 0]]),
    'L': np.array([[0, 0, 0, 0], [0, 0, 0, 0], [0, 1, 1, 1], [0, 0, 1, 0]]),
    'J': np.array([[0, 0, 0, 0], [0, 0, 0, 0], [0, 1, 1, 1], [0, 0, 0, 1]]),
    'Z': np.array([[0, 0, 0, 0], [0, 0, 0, 0], [0, 1, 1, 0], [0, 0, 1, 1]]),
    'S': np.array([[0, 0, 0, 0], [0, 0, 0, 0], [0, 0, 1, 1], [0, 1, 1, 0]]),
}

def tourner(piece, n):
    for _ in range(n%4):
        piece = np.rot90(piece, k=-1)
    return piece

def collision(grille, piece, lig, col):
    h, w = np.shape(piece)
    for i in range(h):
        for j in range(w):
            if piece[i, j] == 1:
                if grille[lig+i, row+j] == 1:
                    return True

def placer(grille, piece, lig, col):
    new_grille = grille.copy()
    h, w = np.shape(piece)
    for i in range(h):
        for j in range(w):
            if piece[i, j] == 1:
                new_grille[lig+i, col+j] = 1
    return new_grille

def fairetomber(grille, piece, col):
    h, w = np.shape(piece)
    H, W = np.shape(grille)
    if col+w > W:
        return None
    for lig in range(H-h + 1):
        if collision(grille, piece, lig, col):
            return placer(grille, piece, lig-1, col)
    return placer(grille, piece, H-h, col)

"meilleur coup"
def mllrcoup(grille, piece, a, b, c, d):
    mllr = -float("inf")
    mllr_action = None

    for rot in range(4):
        p = tourner(piece, rot)
        for col in range(np.shape(grille)[1]):
            new_grille = fairetomber(grille, p, col)
            s = score(new_grille, a, b, c, d)
            if s > mllr:
                mllr = s
                mllr_action = (rot, col)
    return mllr_action

"Connexion et jouer"
def constructgrille(buffer):
    grille = np.zeros(20, 10)
    txt = buffer.strip(" ")
    lignes = txt[1:].split("\n")
    pos = []
    for i in lignes:
        pos.append(lignes.split(","))
    for j in range(len(pos)):
        for cle, valeur in Tetromino.items():
            if pos[j][0] == cle:
                grille[pos[j][1]:pos[j][1]+4, pos[j][2]:pos[j][2]+4] = valeur
            else:
                print("[!]> ERROR")
    return grille

def client():
    print("connexion au serveur jeu (C++): {HOST}:{PORT}")
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    print("[+]: IA connecter")
    BUFFER = ''
    while True:
        recv = s.recv(4096).decode('utf-8')
        if not recv:
            print("[!]: IA deconnecter")
            break
        buffer += recv
        piece = buffer.split("\n")
        grille = constructgrille(buffer)


        rot, col = mllrcoup(grille, piece[0], a, b, c, d)
        msg = f'deplacement: {col}, rotation: {rot}'
        s.send(msg.encode())
