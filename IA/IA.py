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

def fitness (v):
    total_lines = 0
    for _ in range(100):
        total_lines += 
    return total_lines

def tournament_selection(population):
    sample = np.random.sample(population, 100)
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
        population.append({"vector": random_vector(), "fitness": 0})

    for generation in range(100):
        for i in range(len(population)):
            population[i]["fitness"] = fitness(population[i]["vector"])
        children = []
        while len(children) < 300:
            p1, p2 = tournament_selection(population)
            child = crossover(p1, p2)
            child = mutate(child)
            children.append({"vector": child, "fitness": 0})
        population = population[:300]
        population.extend(children)

    population.sort(key=lambda x: x["fitness"], reverse=True)
    best = population[0]
    return best["vector"][0], best["vector"][1], best["vector"][2], best["vector"][3] 

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
                if grille[lig+i, col+j] == 1:
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
def lire_grille():
    with open("grille.txt", "r") as f:
        lignes = f.read().splitlines()
    piece = lignes[0]
    grille = np.zeros(20, 10)
    for ligne in lignes[1:]:
        grille[]
    return piece, grille

def ecrire_coup(rot, col):
    with open("coup.txt", "w") as f:
        f.write(f"{rot} {col}")

def client():
    print("connexion au serveur jeu (C++): {HOST}:{PORT}")
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    print("[+]: IA connecter")
    a, b, c, d = genetic_algo()
    while True:
        msg = s.recv(4096).decode()
        if not msg:
            print("[!]: IA deconnecter")
            break
        if msg == "GO":
            piece, grille = lire_grille()
            rot, col = mllrcoup(grille, piece, a, b, c, d)
            s.send(b"OK")

client()
