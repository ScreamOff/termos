// Program reader.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void readAndPrintFile(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct stat fileStat;
    if (fstat(fd, &fileStat) == -1) {
        perror("fstat");
        exit(EXIT_FAILURE);
    }

    char *fileContent = mmap(NULL, fileStat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (fileContent == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("Read: %.*s\n", (int)fileStat.st_size, fileContent);
        sleep(1);
    }

    if (munmap(fileContent, fileStat.st_size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    readAndPrintFile(filename);

    return 0;
}

// Program modifier.c

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void modifyFile(const char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct stat fileStat;
    if (fstat(fd, &fileStat) == -1) {
        perror("fstat");
        exit(EXIT_FAILURE);
    }

    char *fileContent = mmap(NULL, fileStat.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (fileContent == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Modyfikacja pliku
        char currentChar = fileContent[0];
        char modifiedChar = (currentChar == 'X') ? 'A' : 'X';
        fileContent[0] = modifiedChar;

        sleep(1);
    }

    if (munmap(fileContent, fileStat.st_size) == -1) {
        perror("munmap");
        exit(EXIT_FAILURE);
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    modifyFile(filename);

    return 0;
}

