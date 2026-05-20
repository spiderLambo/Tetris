"""
Dans le C++ main a chaque fois que un coup est jouer le C++ envoie un socket de la grille (placer, courant). Ici on calcul alors le coup optimal et on renvoie donc les action a faire (deplacer*x, tourner*y)
"""

import socket
import numpy as np
import random

HOST = '127.0.0.1'
PORT = 63424

W = 10
H = 20

#Les heuristique
def aggregate_height(g):
    total = 0
    for col in range(W):
        for lig in range(H):
            if g[lig, col] == 1:
                total += H - lig
                break
    return total


def completelines(g):
        return int(np.sum(np.all(g == 1, axis=1)))

def holes(g):
    total = 0
    for col in range(W):
        block = False
        for lig in range(H):
            if g[lig, col] == 1:
                block = True
            elif block:
                total += 1
    return total

            
def bumpiness(g):
    heights = []
    for col in range(W):
        h = 0
        for lig in range(H):
            if g[lig, col] == 1:
                h = H - lig
                break
        heights.append(h)
    return sum(abs(heights[i] - heights[i+1]) for i in range(len(heights)-1))


"Le score"
def score(grille, a, b, c, d):
    height = aggregate_height(grille)
    lines = completelines(grille)
    hole = holes(grille)
    bump = bumpiness(grille)
    return a*height + b*lines + c*hole + d*bump

"optimisation de a, b, c, d"

"-------------------"
def normalisation(v):
    norm = np.linalg.norm(v)
    if norm == 0:
        return random_vect()
    return v/norm

def random_vect():
    v = np.random.uniform(-1, 1, 4)
    return normalisation(v)
"-------------------"

def totaline(v):
    grille = np.zeros((H, W), dtype=np.int8)
    lignes = 0
    a, b, c, d = v

    for _ in range(500):
        piece_type = random.choice(PIECES)
        rot, col = best_move(grille, piece_type, a, b, c, d)
        piece = rotate(TETROMINOS[piece_type], rot)
        ph, pw = piece.shape
        lig = 0
        while not collision(grille, piece, lig + 1, col):
            lig += 1
            if lig + ph >= H:
                break
        if collision(grille, piece, lig, col):
            break
        tmp = grille.copy()
        for i in range(ph):
            for j in range(pw):
                if piece[i, j] == 1:
                    tmp[lig + i, col + j] = 1
        pleines = int(np.sum(np.all(tmp == 1, axis=1)))
        lignes += pleines
        mask = ~np.all(tmp == 1, axis=1)
        tmp  = tmp[mask]
        tmp  = np.vstack([np.zeros((H - len(tmp), W), dtype=np.int8), tmp])
        grille = tmp

        if np.any(grille[0] == 1):
            break

    return lignes


def fitness(v):
    total_lines = 0
    for _ in range(100):
        total_lines += totaline(v)
    return total_lines

def tournament_selection(population):
    sample = random.sample(population, 100)
    sample.sort(key=lambda x: x["fitness"], reverse=True)
    return sample[0], sample[1]

def crossover(p1, p2):
    child = ((p1["vector"]*p1["fitness"]) + (p2["vector"]*p2["fitness"]))
    return normalisation(child)

def mutation(v):
    if np.random.random() < 0.05:
        i = np.random.randint(0, 3)
        v[i] += np.random.uniform(-0.02, 0.02)
        v = normalisation(v)
    return v

def genetic_algo():
    population = []
    for _ in range(1000):
        population.append({"vector": random_vect(), "fitness": 0})

    for i in range(len(population)):
        population[i]["fitness"] = fitness(population[i]["vector"])
    
    children = []
    while len(children) < 300:
        p1, p2 = tournament_selection(population)
        child = crossover(p1, p2)
        child = mutation(child)
        children.append({"vector": child, "fitness": 0})

    population.sort(key=lambda x: x["fitness"], reverse=True)
    population = population[:300]
    population.extend(children)

    population.sort(key=lambda x: x["fitness"], reverse=True)
    best = population[0]
    return best["vector"][0], best["vector"][1], best["vector"][2], best["vector"][3] 

"Jeu"
TETROMINOS = {
    'I': np.array([[0, 0, 0, 0], [1, 1, 1, 1], [0, 0, 0, 0], [0, 0, 0, 0]]),
    'O': np.array([[0, 0, 0, 0], [0, 1, 1, 0], [0, 1, 1, 0], [0, 0, 0, 0]]),
    'T': np.array([[0, 0, 0, 0], [0, 0, 0, 0], [0, 1, 1, 1], [0, 0, 1, 0]]),
    'L': np.array([[0, 0, 0, 0], [0, 0, 0, 0], [0, 1, 1, 1], [0, 1, 0, 0]]),
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
                r, c = lig + i, col + j
                if r < 0 or r >= H or c < 0 or c >= W:
                    return True
                if grille[r, c] == 1:
                    return True
    return False

def descente(g, piece, col):
    ph, pw = np.shape(piece)
    if col + pw > W or col < 0:
        return None
    lig = 0
    while not collision(g, piece, lig + 1, col):
        lig += 1
        if lig + ph > H:
            break
    if collision(g, piece, lig, col):
        return None
    new_g = g.copy()
    for i in range(ph):
        for j in range(pw):
            if piece[i, j] == 1:
                new_g[lig + i, col + j] = 1
    full = np.all(new_g == 1, axis=1)
    new_g = new_g[~full]
    new_g = np.vstack([np.zeros((full.sum(), W), dtype=np.int8), new_g])
    return new_g


"meilleur coup"
def mllrcoup(g, piece_type, a, b, c, d):
    best_s  = -float('inf')
    best_action = (0, 0)
    base_piece = TETROMINOS[piece_type]
 
    for rot in range(4):
        piece = tourner(base_piece, rot)
        pw = piece.shape[1]
        for col in range(W - pw + 1):
            new_g = descente(g, piece, col)
            if new_g is None:
                continue
            s = score(new_g, a, b, c, d)
            if s > best_s:
                best_s = s
                best_action = (rot, col)
 
    return best_action


"Connexion et jouer"
def lire_grille():
    with open("grille.txt", "r") as f:
        lignes = f.read().splitlines()
    piece_type = lignes[0].strip()
    g = np.zeros((H, W), dtype=np.int8)
    for i in range(H):
        ligne = lignes[i + 1] if i + 1 < len(lignes) else ''
        for j in range(W):
            c = ligne[j] if j < len(ligne) else ' '
            g[i, j] = 1 if c == 'P' else 0
    return piece_type, g

def ecrire_coup(rot, col):
    with open("coup.txt", "w") as f:
        f.write(f"{rot} {col}\n")

def client():
    print(f"connexion au serveur jeu (C++): {HOST}:{PORT}")
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    print("[+]: IA connecté")
    while True:
        msg = s.recv(4096).decode().strip()
        if not msg:
            print("[-]: IA deconnecté")
            break
        if msg.strip() == "GO":
            piece, grille = lire_grille()
            print(f"Pièce: {piece}")
            print("Grille reçue:")
            print(grille)
            rot, col = mllrcoup(grille, piece, a=-0.510066, b=0.760666, c=-0.35663, d=-0.184483)
            ecrire_coup(rot, col)
            print(f"Coup calculé → rot={rot}, col={col}")
            s.send(b"OK\n")
    s.close()

client()
