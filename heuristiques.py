# heuristique.py


def get_hauteurs(grille: list[list[str]]) -> list[int]:
    """Calcule la hauteur de chaque colonne (distance du bas au premier bloc)."""
    nb_lignes = len(grille)
    nb_cols = len(grille[0])
    hauteurs = [0] * nb_cols
    for j in range(nb_cols):
        for i in range(nb_lignes):
            if grille[i][j] != " ":
                hauteurs[j] = nb_lignes - i
                break
    return hauteurs


def compte_trous(grille: list[list[str]], hauteurs: list[int]) -> int:
    """
    CRITIQUE : Compte les vides qui ont au moins un bloc au-dessus d'eux.
    Un trou est une cellule vide (j) à une ligne (i) où i > (sommet de la colonne j).
    """
    trous = 0
    nb_lignes = len(grille)
    for j in range(len(grille[0])):
        sommet = nb_lignes - hauteurs[j]
        for i in range(sommet + 1, nb_lignes):
            if grille[i][j] == " ":
                trous += 1
    return trous


def rugosite(hauteurs: list[int]) -> int:
    """Calcule la somme des différences de hauteur entre colonnes adjacentes."""
    return sum(abs(hauteurs[j] - hauteurs[j + 1]) for j in range(len(hauteurs) - 1))


def lignes_completes(grille: list[list[str]]) -> int:
    """Nombre de lignes totalement remplies."""
    return sum(1 for ligne in grille if " " not in ligne)


# --- Nouveaux Coefficients (Optimisés pour la survie) ---
# Ces poids sont issus de l'algorithme de Pierre Dellacherie,
# reconnus comme les plus stables pour Tetris.
A = -0.510066
B = 0.760666
C = -0.35663
D = -0.184483


def score(grille: list[list[str]]) -> float:
    """Calcule le score de qualité d'une grille (plus c'est haut, mieux c'est)."""
    h = get_hauteurs(grille)

    a = COEFF_HAUTEUR * sum(h)  # Hauteur agrégée
    b = COEFF_LIGNES * lignes_completes(grille)
    c = COEFF_TROUS * compte_trous(grille, h)
    d = COEFF_RUGOSITE * rugosite(h)

    return a + b + c + d
