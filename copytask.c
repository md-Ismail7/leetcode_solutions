#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int fd_src = open(argv[1], O_RDONLY);
    if (fd_src == -1) {
        perror("open source");
        exit(EXIT_FAILURE);
    }

    int fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_dest == -1) {
        perror("open destination");
        close(fd_src);
        exit(EXIT_FAILURE);
    }

    char buffer[BUF_SIZE];
    ssize_t bytes_read, bytes_written;

    while ((bytes_read = read(fd_src, buffer, BUF_SIZE)) > 0) {
        bytes_written = write(fd_dest, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("write");
            close(fd_src);
            close(fd_dest);
            exit(EXIT_FAILURE);
        }
    }

    if (bytes_read == -1) {
        perror("read");
    }

    close(fd_src);
    close(fd_dest);

    printf("File copied successfully!\n");

    // Compare files automatically (Windows -> fc)
    
}
