#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void lockExample(const char *filename) {
    int fileDescriptor = open(filename, O_RDWR | O_CREAT, 0666);

    if (fileDescriptor == -1) {
        perror("open");
        return;
    }

    // Blokowanie pliku dla zapisu
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;  // Zablokuj cały plik

    if (fcntl(fileDescriptor, F_SETLK, &lock) == -1) {
        perror("fcntl");
        close(fileDescriptor);
        return;
    }

    printf("lock");

    // Symulacja długiego działania
    sleep(5);

    // Odblokowanie pliku
    lock.l_type = F_UNLCK;
    if (fcntl(fileDescriptor, F_SETLK, &lock) == -1) {
        perror("fcntl");
    } else {
        printf("unlock");
    }

    close(fileDescriptor);
}

int main() {
    lockExample("lockedFile.txt");
    return 0;
}
