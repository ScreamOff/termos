#include <stdio.h>
#include <termios.h>
#include <unistd.h>

// Funkcja do wyłączania echo
void disableEcho() {
    struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("tcgetattr");
    }
    term.c_lflag &= ~ECHO;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1) {
        perror("tcsetattr");
    }
}

// Funkcja do przywracania echo
void enableEcho() {
    struct termios term;
    if (tcgetattr(STDIN_FILENO, &term) == -1) {
        perror("tcgetattr");
        return;
    }
    term.c_lflag |= ECHO;
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &term) == -1) {
        perror("tcsetattr");
    }
}

int main(void) {
    printf("Echo jest obecnie włączone. Naciśnij Enter, aby wyłączyć echo.\n");
    getchar();  // Czekaj na Enter

    // Wyłącz echo
    disableEcho();
    printf("Echo zostało wyłączone. Naciśnij Enter, aby przywrócić echo.\n");
    getchar();  // Czekaj na Enter

    // Przywróć echo
    enableEcho();
    printf("Echo zostało przywrócone.\n");
    return 0;
} 
