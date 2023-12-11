#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void copyFile(const char *sourceFilename, const char *destinationFilename) {
    int sourceFile = open(sourceFilename, O_RDONLY);
    int destinationFile = open(destinationFilename, O_WRONLY | O_CREAT | O_TRUNC, 0666);

    if (sourceFile == -1 || destinationFile == -1) {
        perror("Error opening files");
        return;
    }

    char buffer[4096];  // Bufor kopiowania

    ssize_t bytesRead;
    while ((bytesRead = read(sourceFile, buffer, sizeof(buffer))) > 0) {
        write(destinationFile, buffer, bytesRead);
    }

    if (bytesRead == -1) {
        perror("Error reading file");
    }

    close(sourceFile);
    close(destinationFile);

    printf("File copied successfully.\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    copyFile(argv[1], argv[2]);

    return 0;
}
