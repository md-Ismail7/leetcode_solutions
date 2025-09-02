#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>


void *map_file(const char *filename, size_t *file_size)
{
    int fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return NULL;
    }

    struct stat sb;
    if (fstat(fd, &sb) == -1)
    {
        perror("fstat");
        close(fd);
        return NULL;
    }
    *file_size = sb.st_size;

    void *mapped = mmap(NULL, *file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);

    if (mapped == MAP_FAILED)
    {
        perror("mmap");
        return NULL;
    }

    return mapped;
}


void search_keyword(const char *file_data, size_t file_size, const char *keyword)
{
    size_t keyword_len = strlen(keyword);
    size_t match_count = 0;

    if (keyword_len == 0)
    {
        printf("Keyword cannot be empty.\n");
        return;
    }

    for (size_t i = 0; i + keyword_len <= file_size; i++)
    {
        if (memcmp(file_data + i, keyword, keyword_len) == 0)
        {
            printf("Match found at byte offset %zu\n", i);
            match_count++;
        }
    }

    if (match_count == 0)
    {
        printf("No matches found for '%s'.\n", keyword);
    }
    else
    {
        printf("Total matches: %zu\n", match_count);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <filename> <keyword>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    const char *keyword = argv[2];
    size_t file_size;

    char *file_data = map_file(filename, &file_size);
    if (file_data == NULL)
    {
        fprintf(stderr, "Error: Could not map file '%s'\n", filename);
        return EXIT_FAILURE;
    }

    search_keyword(file_data, file_size, keyword);

    if (munmap(file_data, file_size) == -1)
    {
        perror("munmap");
    }

    return EXIT_SUCCESS;
}