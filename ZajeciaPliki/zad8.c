#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void writeFile(const char *filename, int processNumber) {
    int file = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0666);

    if (file == -1) {
        perror("Error opening file");
        return;
    }

    dprintf(file, "Message from process %d\n", processNumber);

    close(file);
}

void readFile(const char *filename) {
    int file = open(filename, O_RDONLY);

    if (file == -1) {
        perror("Error opening file");
        return;
    }

    char buffer[4096];  // Bufor odczytu

    ssize_t bytesRead;
    while ((bytesRead = read(file, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    if (bytesRead == -1) {
        perror("Error reading file");
    }

    close(file);
}

int main() {
    const char *filename = "sharedFile.txt";

    // Tworzenie trzech procesów potomnych
    for (int i = 1; i <= 3; ++i) {
        pid_t childPid = fork();

        if (childPid == 0) {
            // Proces potomny
            writeFile(filename, i);
            exit(0);
        } else if (childPid < 0) {
            perror("Error forking");
            exit(1);
        }
    }

    // Oczekiwanie na zakończenie procesów potomnych
    for (int i = 0; i < 3; ++i) {
        wait(NULL);
    }

    // Odczytywanie pliku z procesu macierzystego
    readFile(filename);

    return 0;
}
