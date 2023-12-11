#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

void displayFileInfo(const char *filename) {
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

    printf("Informacje o pliku: %s\n", filename);
    printf("Rozmiar pliku: %ld bajtów\n", (long)fileStat.st_size);
    printf("Liczba bloków alokowanych na plik: %ld\n", (long)fileStat.st_blocks);
    printf("Liczba bloków we/wy: %ld\n", (long)fileStat.st_blksize);
    printf("Numer urządzenia: %lu\n", (unsigned long)fileStat.st_dev);
    printf("Numer i-węzła: %lu\n", (unsigned long)fileStat.st_ino);
    printf("Tryb: %o\n", fileStat.st_mode);
    printf("Liczba dowiązań: %lu\n", (unsigned long)fileStat.st_nlink);
    printf("Numer użytkownika (UID): %u\n", fileStat.st_uid);
    printf("Numer grupy (GID): %u\n", fileStat.st_gid);
    printf("Czas ostatniego dostępu: %ld\n", (long)fileStat.st_atime);
    printf("Czas ostatniej modyfikacji: %ld\n", (long)fileStat.st_mtime);
    printf("Czas ostatniego statusu: %ld\n", (long)fileStat.st_ctime);

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Użycie: %s <nazwa_pliku>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *filename = argv[1];
    displayFileInfo(filename);

    return 0;
}
