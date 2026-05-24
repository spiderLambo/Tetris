import copy

HAUTEUR = 20
LARGEUR = 10

# Dans grille.py

# 1. Vérifie le nom ici :
TETROMINOS_ABS = {
    "I": [(0, 3), (0, 4), (0, 5), (0, 6)],
    "O": [(0, 4), (0, 5), (1, 4), (1, 5)],
    "T": [(0, 4), (0, 5), (0, 6), (1, 5)],
    "L": [(0, 4), (0, 5), (0, 6), (1, 4)],
    "J": [(0, 4), (0, 5), (0, 6), (1, 6)],
    "Z": [(0, 4), (0, 5), (1, 5), (1, 6)],
    "S": [(0, 5), (0, 6), (1, 4), (1, 5)],
}


def apparait(grille, piece):
    # 2. Utilise le MÊME nom ici :
    if piece not in TETROMINOS_ABS:
        return False

    shape = TETROMINOS_ABS[piece]
    for r, c in shape:
        if grille[r][c] != " ":
            return False
        grille[r][c] = "C"
    return True


class Plateau:
    def __init__(self, gr=None):
        self.gr = (
            copy.deepcopy(gr)
            if gr
            else [[" " for _ in range(LARGEUR)] for _ in range(HAUTEUR)]
        )


def tourner(p, sens=True):
    # On récupère les blocs de la pièce actuelle 'C'
    coords = [
        (r, c) for r in range(HAUTEUR) for c in range(LARGEUR) if p.gr[r][c] == "C"
    ]
    if not coords:
        return

    # Centre de rotation (le premier bloc par défaut)
    r0, c0 = coords[0]
    new_coords = []
    for r, c in coords:
        # Rotation 90° : (r, c) -> (r0 + (c - c0), c0 - (r - r0))
        nr, nc = r0 + (c - c0), c0 - (r - r0)
        if not (0 <= nr < HAUTEUR and 0 <= nc < LARGEUR) or (
            p.gr[nr][nc] != " " and p.gr[nr][nc] != "C"
        ):
            return  # Collision : on ne tourne pas
        new_coords.append((nr, nc))

    for r, c in coords:
        p.gr[r][c] = " "
    for r, c in new_coords:
        p.gr[r][c] = "C"


def deplacer(grille, direction):
    coords = [
        (r, c) for r in range(HAUTEUR) for c in range(LARGEUR) if grille[r][c] == "C"
    ]
    dr, dc = 0, 0
    if direction == "B":
        dr = 1
    elif direction == "G":
        dc = -1
    elif direction == "D":
        dc = 1

    for r, c in coords:
        nr, nc = r + dr, c + dc
        if not (0 <= nr < HAUTEUR and 0 <= nc < LARGEUR) or (
            grille[nr][nc] != " " and grille[nr][nc] != "C"
        ):
            return False

    # On trie pour ne pas s'auto-écraser pendant le déplacement
    coords.sort(reverse=(direction == "B"))
    for r, c in coords:
        grille[r][c] = " "
        grille[r + dr][c + dc] = "C"
    return True


def placer(grille):
    for r in range(HAUTEUR):
        for c in range(LARGEUR):
            if grille[r][c] == "C":
                grille[r][c] = "P"


def peuxSupprimerLigne(g, r):
    return " " not in g[r]


def supprimerLigne(g, r):
    del g[r]
    g.insert(0, [" " for _ in range(LARGEUR)])
