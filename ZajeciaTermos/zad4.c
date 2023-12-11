#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Funkcja do ustawiania trybu duże litery
void setUpperCaseMode() {
    printf("\033[0;31m"); // Ustawia kolor tekstu na czerwony
    printf("\033[1m");    // Ustawia tekst na duże litery
}

// Funkcja do przywracania normalnego trybu
void restoreNormalMode() {
    printf("\033[0m"); // Przywraca normalny kolor i rozmiar tekstu
}

int main() {
    // Sprawdź, czy program został już uruchomiony
    char *env_var = getenv("UPPER_CASE_MODE");
    bool is_upper_case_mode = (env_var && strcmp(env_var, "1") == 0);

    if (!is_upper_case_mode) {
        setUpperCaseMode();
        printf("TERMINAL W TRYBIE DUŻYCH LITER\n");
        // Ustaw zmienną środowiskową informującą o trybie dużych liter
        setenv("UPPER_CASE_MODE", "1", 1);
    } else {
        printf("TERMINAL W NORMALNYM TRYBIE\n");
        // Usuń zmienną środowiskową informującą o trybie dużych liter
        unsetenv("UPPER_CASE_MODE");
        restoreNormalMode();
    }

    return 0;
}
