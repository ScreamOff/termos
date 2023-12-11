#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/sendfile.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int openSourceFile(const char *sourceFile) {
    int sourceFd = open(sourceFile, O_RDONLY);
    if (sourceFd == -1) {
        perror("Nie można otworzyć pliku źródłowego");
        exit(EXIT_FAILURE);
    }
    return sourceFd;
}

int getSourceFileSize(int sourceFd, struct stat *sourceStat) {
    if (fstat(sourceFd, sourceStat) == -1) {
        perror("Błąd podczas pobierania informacji o pliku źródłowym");
        exit(EXIT_FAILURE);
    }
    return sourceStat->st_size;
}

int openDestinationFile(const char *destinationFile) {
    int destFd = open(destinationFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destFd == -1) {
        perror("Nie można otworzyć pliku docelowego");
        exit(EXIT_FAILURE);
    }
    return destFd;
}

void closeFile(int fd, const char *fileName) {
    if (close(fd) == -1) {
        perror("Błąd podczas zamykania pliku");
        exit(EXIT_FAILURE);
    }
}

void copyFile(const char *sourceFile, const char *destinationFile) {
    int sourceFd = openSourceFile(sourceFile);

    struct stat sourceStat;
    int fileSize = getSourceFileSize(sourceFd, &sourceStat);

    int destFd = openDestinationFile(destinationFile);

    off_t offset = 0;
    ssize_t bytesSent = sendfile(destFd, sourceFd, &offset, fileSize);

    if (bytesSent == -1) {
        perror("Błąd podczas kopiowania pliku");
        exit(EXIT_FAILURE);
    }

    printf("Plik skopiowany pomyślnie: %zd bajtów skopiowano\n", bytesSent);

    closeFile(sourceFd, sourceFile);
    closeFile(destFd, destinationFile);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Użycie: %s <źródło> <cel>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *sourceFile = argv[1];
    const char *destinationFile = argv[2];

    copyFile(sourceFile, destinationFile);

    return 0;
}
