import socket
import os

HOST = "127.0.0.1"
PORT = 63424


# =========================================================================
# EXTRACTION ET NORMALISATION DE LA PIÈCE ACTIVE 'C'
# =========================================================================
def extraire_et_nettoyer_piece(grid):
    coords = []
    for r in range(20):
        for c in range(10):
            if grid[r][c] == "C":
                coords.append((r, c))

    if not coords:
        return None, grid

    clean_grid = [row[:] for row in grid]
    for r, c in coords:
        clean_grid[r][c] = " "

    min_r = min(r for r, c in coords)
    min_c = min(c for r, c in coords)

    base_shape = [(r - min_r, c - min_c) for r, c in coords]
    return base_shape, clean_grid


def generer_rotations(base_shape):
    rotations = {}
    current_shape = base_shape
    for rot in range(4):
        min_r = min(r for r, c in current_shape)
        min_c = min(c for r, c in current_shape)
        normalized = sorted([(r - min_r, c - min_c) for r, c in current_shape])
        rotations[rot] = normalized
        current_shape = [(c, -r) for r, c in current_shape]
    return rotations


# =========================================================================
# LECTURE ET PARSING SÉCURISÉ DE LA GRILLE
# =========================================================================
def lire_grille():
    if not os.path.exists("grille.txt"):
        return None
    try:
        with open("grille.txt", "r", encoding="utf-8", errors="ignore") as f:
            lines = f.readlines()

        grid = []
        for line in lines:
            if "|" in line:
                # Supprime les espaces insécables (\xa0) et résidus bizarres
                clean_line = line.replace("\xa0", " ").replace("\t", " ").strip()
                # On découpe par les barres de séparation |
                parts = clean_line.split("|")

                # Une ligne valide de 10 colonnes entourée de '|' doit donner au moins 11 segments
                if len(parts) >= 11:
                    raw_cells = parts[
                        1:11
                    ]  # On extrait strictement les 10 cases du milieu
                    row = []
                    for cell in raw_cells:
                        if "P" in cell or "p" in cell:
                            row.append("P")
                        elif "C" in cell or "c" in cell:
                            row.append("C")
                        else:
                            row.append(" ")
                    grid.append(row)

        if len(grid) >= 20:
            return grid[
                -20:
            ]  # On garde les 20 lignes du bas (le plateau de jeu complet)
        return None
    except Exception:
        return None


# =========================================================================
# SIMULATION DE CHUTE ET ÉVALUATION
# =========================================================================
def evaluer_coup(clean_grid, coords, target_col):
    for pr, pc in coords:
        abs_col = target_col + pc
        if abs_col < 0 or abs_col >= 10:
            return None

    final_r_offset = None
    for r_offset in range(-4, 21):
        collision = False
        for pr, pc in coords:
            curr_row = r_offset + pr
            curr_col = target_col + pc
            if curr_row >= 0:
                if curr_row >= 20 or clean_grid[curr_row][curr_col] == "P":
                    collision = True
                    break
        if collision:
            final_r_offset = r_offset - 1
            break

    if final_r_offset is None or final_r_offset < -4:
        return None

    heights = [0] * 10
    for c in range(10):
        for r in range(20):
            if clean_grid[r][c] == "P":
                heights[c] = 20 - r
                break

    for pr, pc in coords:
        curr_row = final_r_offset + pr
        curr_col = target_col + pc
        if 0 <= curr_row < 20:
            h_virtuel = 20 - curr_row
            if h_virtuel > heights[curr_col]:
                heights[curr_col] = h_virtuel

    hauteur_max = max(heights)
    hauteur_penalite = 20 - final_r_offset
    rugosite = sum(abs(heights[c] - heights[c + 1]) for c in range(9))

    score = (hauteur_penalite * 5.0) + (hauteur_max * 15.0) + (rugosite * 4.0)
    return score


# =========================================================================
# MOTEUR PRINCIPAL
# =========================================================================
def choisir_coup(grid):
    base_shape, clean_grid = extraire_et_nettoyer_piece(grid)
    if not base_shape:
        return 0, 4

    piece_rotations = generer_rotations(base_shape)
    best_score = float("inf")
    best_rot = 0
    best_col = 4

    for rot in (0, 1, 2, 3):
        coords = piece_rotations[rot]
        for col in range(10):
            score = evaluer_coup(clean_grid, coords, col)
            if score is not None and score < best_score:
                best_score = score
                best_rot = rot
                best_col = col

    return best_rot, best_col


def ecrire_coup(rot, col):
    try:
        with open("coup.txt", "w") as f:
            f.write(f"0 {rot} {col}\n")
            f.flush()
            os.fsync(f.fileno())
    except Exception:
        pass


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        sock.connect((HOST, PORT))
        print("[IA - SYSTEM] Connecté au serveur réseau Tetris")
    except Exception:
        return

    buffer = ""
    while True:
        try:
            data = sock.recv(1024).decode("utf-8", errors="ignore")
            if not data:
                break
            buffer += data

            if "GO" in buffer:
                buffer = buffer.split("GO", 1)[1]

                grid = lire_grille()
                if grid:
                    rot, col = choisir_coup(grid)
                    print(
                        f"[IA - ACTION] Grille lue ! Décision -> rot: {rot}, col: {col}"
                    )
                    ecrire_coup(rot, col)
                else:
                    print("[IA - ALERTE] Grille illisible, coup par défaut")
                    ecrire_coup(0, 4)

                sock.sendall(b"OK\n")
        except Exception:
            break
    sock.close()


if __name__ == "__main__":
    main()
