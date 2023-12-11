#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

const char *filename = "plik.txt";
const int dataSize = 100;

void writerProcess() {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char data[dataSize];
    for (int i = 0; i < dataSize; ++i) {
        data[i] = 'A' + i % 26;
    }

    if (write(fd, data, dataSize) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    close(fd);
    exit(EXIT_SUCCESS);
}

void readerProcess() {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char buffer[dataSize];
    if (read(fd, buffer, dataSize) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    printf("Reader Process %d read: %s\n", getpid(), buffer);

    close(fd);
    exit(EXIT_SUCCESS);
}

int main() {
    // Tworzenie pliku
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    close(fd);

    // Tworzenie procesu pisarza
    pid_t writerPid = fork();
    if (writerPid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (writerPid == 0) {
        // Proces potomny (pisarz)
        writerProcess();
    }

    // Tworzenie trzech procesów czytających
    for (int i = 0; i < 3; ++i) {
        pid_t readerPid = fork();
        if (readerPid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (readerPid == 0) {
            // Proces potomny (czytelnik)
            readerProcess();
        }
    }

    // Oczekiwanie na zakończenie wszystkich procesów potomnych
    for (int i = 0; i < 4; ++i) {
        wait(NULL);
    }

    return 0;
}
