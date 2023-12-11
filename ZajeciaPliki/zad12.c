#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

const char *filename = "plik.txt";
const size_t dataSize = 4 * 1024;  // 4 KiB
const size_t numIterations = 1000;

void writeToFile(const char *mode) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    char data[dataSize];
    for (size_t i = 0; i < dataSize; ++i) {
        data[i] = 'A' + i % 26;
    }

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (size_t i = 0; i < numIterations; ++i) {
        if (write(fd, data, dataSize) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        // Synchronizacja w zależności od trybu
        if (mode == NULL) {
            // Brak synchronizacji
        } else if (strcmp(mode, "fsync") == 0) {
            if (fsync(fd) == -1) {
                perror("fsync");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(mode, "fdatasync") == 0) {
            if (fdatasync(fd) == -1) {
                perror("fdatasync");
                exit(EXIT_FAILURE);
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsedTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("Time taken (%s): %.6f seconds\n", mode, elapsedTime);

    close(fd);
}

int main() {
    writeToFile(NULL);          // Bez synchronizacji
    writeToFile("fsync");       // Z użyciem fsync()
    writeToFile("fdatasync");   // Z użyciem fdatasync()

    return 0;
}
