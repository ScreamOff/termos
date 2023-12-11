#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <termios.h>

int main() {
    // Sprawdź, czy stdin jest związane z terminalem
    if (isatty(STDIN_FILENO)) {
        // Pobierz nazwę pliku urządzenia terminala
        char *terminal_name = ttyname(STDIN_FILENO);
        if (terminal_name == NULL) {
            perror("Nie można uzyskać nazwy terminala");
            exit(EXIT_FAILURE);
        }

        // Pobierz bieżące ustawienia terminala
        struct termios term_settings;
        if (tcgetattr(STDIN_FILENO, &term_settings) == -1) {
            perror("Błąd podczas pobierania ustawień terminala");
            exit(EXIT_FAILURE);
        }

        // Wypisz nazwę pliku urządzenia terminala
        printf("Nazwa pliku urządzenia terminala: %s\n", terminal_name);

        // Wypisz kilka bieżących ustawień terminala
        printf("Bieżące ustawienia terminala:\n");
        printf("  Baud rate: %lu\n", cfgetospeed(&term_settings));
        printf("  Liczba bitów danych: %d\n", term_settings.c_cflag & CSIZE);
        printf("  Bit stopu: %s\n", (term_settings.c_cflag & CSTOPB) ? "2" : "1");
        printf("  Parzystość: %s\n", (term_settings.c_cflag & PARENB) ? "Włączona" : "Wyłączona");
    } else {
        printf("stdin nie jest związane z terminalem.\n");
    }

    return 0;
}
