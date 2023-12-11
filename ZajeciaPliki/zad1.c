#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void copyFragment(int source, int destination) {
    char buffer[41];

    // Kopiowanie 40 znaków z początku pliku
    read(source, buffer, 40);
    write(destination, buffer, 40);

    // Przesunięcie na koniec pliku i kopiowanie 40 znaków z końca pliku
    lseek(source, -40, SEEK_END);
    read(source, buffer, 40);
    write(destination, buffer, 40);
}

int main() {
    int sourceFile, destinationFile;

    sourceFile = open("source.txt", O_RDONLY);
    destinationFile = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (sourceFile == -1 || destinationFile == -1) {
        perror("Error opening files");
        return 1;
    }

    copyFragment(sourceFile, destinationFile);

    close(sourceFile);
    close(destinationFile);

    printf("Copy successful.\n");

    return 0;
}
