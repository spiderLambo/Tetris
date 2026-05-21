"""
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

#Connexion et jouer
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
"""
import socket
import numpy as np
import random

HOST = "127.0.0.1"
PORT = 63424

W = 10
H = 20

TETROMINOS = {
    'I': np.array([[1, 1, 1, 1]], dtype=np.int8),
    'O': np.array([[1, 1],[1, 1]], dtype=np.int8),
    'T': np.array([[1, 1, 1],[0, 1, 0]], dtype=np.int8),
    'L': np.array([[1, 1, 1],[1, 0, 0]], dtype=np.int8),
    'J': np.array([[1, 1, 1],[0, 0, 1]], dtype=np.int8),
    'S': np.array([[0, 1, 1],[1, 1, 0]], dtype=np.int8),
    'Z': np.array([[1, 1, 0],[0, 1, 1]], dtype=np.int8),
}

#optimisation de a, b, c, d
def normalisation(v):
    norm = np.linalg.norm(v)
    if norm == 0:
        return random_vect()
    return v/norm

def random_vect():
    v = np.random.uniform(-1, 1, 4)
    return normalisation(v)

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

#Jeu
def rotate(piece, n):
    return np.rot90(piece, -n)

def collision(grid, piece, row, col):
    ph, pw = piece.shape
    for i in range(ph):
        for j in range(pw):
            if piece[i, j] == 0:
                continue
            r = row + i
            c = col + j
            if c < 0 or c >= W:
                return True
            if r >= H:
                return True
            if r >= 0 and grid[r, c] == 1:
                return True
    return False

def drop_piece(grid, piece, col):
    ph, pw = piece.shape
    if col < 0 or col + pw > W:
        return None
    row = 0
    while not collision(grid, piece, row + 1, col):
        row += 1
    if collision(grid, piece, row, col):
        return None
    new_grid = grid.copy()
    for i in range(ph):
        for j in range(pw):
            if piece[i, j] == 1:
                new_grid[row + i, col + j] = 1
    full = np.all(new_grid == 1, axis=1)
    cleared = np.sum(full)
    new_grid = new_grid[~full]
    if len(new_grid) < H:
        top = np.zeros((H - len(new_grid), W), dtype=np.int8)
        new_grid = np.vstack((top, new_grid))

    return new_grid, cleared

def column_heights(grid):
    heights = []
    for col in range(W):
        h = 0
        for row in range(H):
            if grid[row, col] == 1:
                h = H - row
                break
        heights.append(h)
    return heights

def aggregate_height(grid):
    return sum(column_heights(grid))

def holes(grid):
    total = 0
    for col in range(W):
        block = False
        for row in range(H):
            if grid[row, col] == 1:
                block = True
            elif block:
                total += 1
    return total

def bumpiness(grid):
    h = column_heights(grid)
    total = 0
    for i in range(W - 1):
        total += abs(h[i] - h[i + 1])
    return total

A = -0.510066
B =  0.760666
C = -0.35663
D = -0.184483

def evaluate(grid, cleared):
    return (A * aggregate_height(grid) + B * cleared + C * holes(grid) + D * bumpiness(grid))

def best_move(grid, piece_type):
    best_score = -999999999
    best_rot = 0
    best_col = 0
    base_piece = TETROMINOS[piece_type]
    for rot in range(4):
        piece = rotate(base_piece, rot)
        ph, pw = piece.shape
        for col in range(W - pw + 1):
            result = drop_piece(grid, piece, col)
            if result is None:
                continue
            new_grid, cleared = result
            score = evaluate(new_grid, cleared)
            if score > best_score:
                best_score = score
                best_rot = rot
                best_col = col
    return best_rot, best_col

#client et lecture
def lire_grille():
    with open("IA/grille.txt", "r") as f:
        lines = f.read().splitlines()
    if len(lines) == 0:
        return None, np.zeros((H, W), dtype=np.int8)
    piece = lines[0].strip()
    grid = np.zeros((H, W), dtype=np.int8)
    for i in range(H):
        if i + 1 >= len(lines):
            break
        line = lines[i + 1]
        for j in range(min(W, len(line))):
            if line[j] == 'P':
                grid[i, j] = 1
    return piece, grid

def ecrire_coup(rot, col):
    with open("IA/coup.txt", "w") as f:
        f.write(f"{rot} {col}\n")

def client():

    print(f"connexion serveur : {HOST}:{PORT}")
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.connect((HOST, PORT))
    print("[+] connecté")

    while True:
        msg = s.recv(4096).decode().strip()
        if not msg:
            print("[-] serveur fermé")
            break
        if msg == "GO":
            piece, grid = lire_grille()
            print("PIECE :", piece)
            if piece not in TETROMINOS:
                print("piece invalide :", piece)
                s.send(b"OK\n")
                continue
            rot, col = best_move(grid, piece)
            print("rotation =", rot)
            print("colonne  =", col)
            ecrire_coup(rot, col)
            s.send(b"OK\n")
    s.close()

client()
