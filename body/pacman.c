void movePacman(Pacman *p, char key) {
    int newX = p->x;
    int newY = p->y;

    if (key) { // Hanya ubah arah jika ada input
        switch (key) {
            case 75: p->direction = 1; break; // Kiri
            case 77: p->direction = 0; break; // Kanan
            case 72: p->direction = 2; break; // Atas
            case 80: p->direction = 3; break; // Bawah
        }
    }

    // Tetap bergerak dalam arah terakhir
    switch (p->direction) {
        case 0: newX += 10; break;
        case 1: newX -= 10; break;
        case 2: newY -= 10; break;
        case 3: newY += 10; break;
    }

    if (!isColliding(p, newX, newY)) {
        clearPacman(p);
        p->x = newX;
        p->y = newY;
        drawPacman(p);
    }
}
