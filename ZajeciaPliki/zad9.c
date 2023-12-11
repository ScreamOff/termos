#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void calculateSum(const char *filename) {
    int file = open(filename, O_RDONLY);

    if (file == -1) {
        perror("Error opening file");
        return;
    }

    int number;
    int evenSum = 0;
    int oddSum = 0;

    while (scanf("%d", &number) == 1) {
        if (number % 2 == 0) {
            evenSum += number;
        } else {
            oddSum += number;
        }
    }

    close(file);

    printf("Even sum: %d\n", evenSum);
    printf("Odd sum: %d\n", oddSum);
}

int main() {
    const char *filename = "numbers.txt";

    // Tworzenie procesu potomnego
    pid_t childPid = fork();

    if (childPid == 0) {
        // Proces potomny
        calculateSum(filename);
        exit(0);
    } else if (childPid < 0) {
        perror("Error forking");
        exit(1);
    }

    wait(NULL);  // Oczekiwanie na zakończenie procesu potomnego

    return 0;
}
