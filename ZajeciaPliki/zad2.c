#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void createFileWithHole(const char *filename) {
    int holedFile = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (holedFile == -1) {
        perror("Error opening file");
        return;
    }

    // Pisanie 256 bajtów
    for (int i = 0; i < 256; ++i) {
        write(holedFile, "A", 1);
    }

    // Przesunięcie na pozycję 512 bajtów
    lseek(holedFile, 512, SEEK_SET);

    // Pisanie 256 bajtów
    for (int i = 0; i < 256; ++i) {
        write(holedFile, "B", 1);
    }

    close(holedFile);

    printf("File with hole created successfully.\n");
}

int main() {
    createFileWithHole("holedFile.txt");
    return 0;
}
