#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void readAndPrintFile(const char *filename) {
    int fileDescriptor = open(filename, O_RDONLY);

    if (fileDescriptor == -1) {
        perror("Error opening file");
        return;
    }

    char buffer[4096];  // Bufor odczytu

    ssize_t bytesRead;
    while ((bytesRead = read(fileDescriptor, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    if (bytesRead == -1) {
        perror("Error reading file");
    }

    close(fileDescriptor);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    readAndPrintFile(argv[1]);

    return 0;
}
