#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void displayFileContent(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct stat fileStat;
    if (fstat(fd, &fileStat) == -1) {
        perror("fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }

    char *fileContent = mmap(NULL, fileStat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (fileContent == MAP_FAILED) {
        perror("mmap");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Wyświetlenie zawartości pliku
    printf("%.*s", (int)fileStat.st_size, fileContent);

    if (munmap(fileContent, fileStat.st_size) == -1) {
        perror("munmap");
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Użycie: %s <nazwa_pliku>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    displayFileContent(filename);

    return 0;
}
