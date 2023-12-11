#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

// Funkcja do ustawiania trybu niekanonicznego terminala
void setNonCanonicalMode() {
    struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("setNonCanonicalMode - tcgetattr");
        exit(EXIT_FAILURE);
    }

    term.c_lflag &= ~(ICANON | ECHO);  // Wyłącz tryb kanoniczny i echo
    term.c_cc[VMIN] = 0;               // Minimalna liczba znaków do odczytu
    term.c_cc[VTIME] = 0;              // Czas oczekiwania (w dziesiętnych sekundach)

    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
        perror("setNonCanonicalMode - tcsetattr");
        exit(EXIT_FAILURE);
    }
}

// Funkcja do przywracania trybu kanonicznego terminala
void restoreCanonicalMode() {
    struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("restoreCanonicalMode - tcgetattr");
        exit(EXIT_FAILURE);
    }

    term.c_lflag |= (ICANON | ECHO);  // Przywróć tryb kanoniczny i echo

    if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1) {
        perror("restoreCanonicalMode - tcsetattr");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Użycie: %s <tryb>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *mode = argv[1];

    setNonCanonicalMode();

    printf("Program w trybie niekanonicznym. Naciśnij 'q' aby wyjść, 'h' aby uzyskać pomoc.\n");

    char input;
    while (1) {
        read(STDIN_FILENO, &input, 1);  // Odczytaj jeden znak

        // Obsługa klawiszy
        switch (input) {
            case 'q':
                printf("Wyjście z programu.\n");
                restoreCanonicalMode();
                exit(EXIT_SUCCESS);
            case 'h':
                printf("Pomoc: Ten program reaguje na klawisze 'q' (wyjście) i 'h' (pomoc).\n");
                break;
            default:
                // Ignoruj inne klawisze
                break;
        }
    }

    return 0;
}
