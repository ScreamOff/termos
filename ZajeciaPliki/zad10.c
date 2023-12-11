// Program 1
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

const char *filename = "numery.txt";
const int chunkSize = 100;

int main() {
    srand(static_cast<unsigned>(time(0)));

    int descriptor = open(filename, O_RDWR | O_CREAT, 0600);
    if (descriptor == -1) {
        perror("open");
        return 1;
    }

    for (int i = 0; i < 1000; ++i) {
        int randomNumber = rand() % 1000;
        write(descriptor, &randomNumber, sizeof(randomNumber));

        if (i % chunkSize == 0) {
            flock(descriptor, LOCK_EX);
            usleep(1000);
        }
    }

    flock(descriptor, LOCK_UN);
    close(descriptor);

    return 0;
}

}
//Program 2
#include <iostream>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

const char *filename = "numery.txt";
const int chunkSize = 100;

void process_chunk(int *data) {
    int maxNumber = data[0];
    for (int i = 1; i < chunkSize; ++i) {
        if (data[i] > maxNumber) {
            maxNumber = data[i];
        }
    }

    std::cout << "Maximum value in chunk: " << maxNumber << std::endl;
}

int main() {
    int descriptor = open(filename, O_RDONLY);
    if (descriptor == -1) {
        perror("open");
        return 1;
    }

    int *data = static_cast<int*>(mmap(NULL, chunkSize * sizeof(int), PROT_READ, MAP_PRIVATE, descriptor, 0));
    if (data == MAP_FAILED) {
        perror("mmap");
        close(descriptor);
        return -1;
    }

    for (int i = 0; i < 1000 / chunkSize; ++i) {
        process_chunk(data);
        data += chunkSize;

        if (i % chunkSize == 0) {
            flock(descriptor, LOCK_SH);
            usleep(1000);
        }
    }

    flock(descriptor, LOCK_UN);
    munmap(data, chunkSize * sizeof(int));
    close(descriptor);

    return 0;
}

