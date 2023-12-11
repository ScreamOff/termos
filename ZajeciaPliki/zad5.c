#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void lockFragment(const char *filename, off_t start, off_t length) {
    int fileDescriptor = open(filename, O_RDWR | O_CREAT, 0666);

    if (fileDescriptor == -1) {
        perror("open");
        return;
    }

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = start;
    lock.l_len = length;

    // Blokowanie fragmentu pliku
    if (fcntl(fileDescriptor, F_SETLK, &lock) == -1) {
        perror("fcntl");
    } else {
        printf("zablokowane");
    }

    // Symulacja długiego działania
    sleep(5);

    // Odblokowanie fragmentu pliku
    lock.l_type = F_UNLCK;
    if (fcntl(fileDescriptor, F_SETLK, &lock) == -1) {
        perror("odblokowane");
    } else {
        printf("File fragment unlocked.\n");
    }

    close(fileDescriptor);
}

int main() {
    lockFragment("fragmentedFile.txt", 0, 40);
    return 0;
}
