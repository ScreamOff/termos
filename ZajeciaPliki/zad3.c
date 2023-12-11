#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

void replicateFileDescriptors(int source, int *replica) {
    *replica = dup(source);
}

int main() {
    int file1, file2;

    file1 = open("file1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(file1<0){
      perror("open");
    }
    dprintf(file1, "Content of file1.txt");
    

    // Replikacja deskryptora pliku
    replicateFileDescriptors(file1, &file2);

    dprintf(file2, "Content of file2.txt");

    close(file1);
    close(file2);

    printf("Files replicated successfully.\n");

    return 0;
}
