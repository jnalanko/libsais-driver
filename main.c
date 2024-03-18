#include <stdio.h>
#include <stdlib.h>
#include "libsais/include/libsais64.h"

void write(int64_t* SA, int64_t n_elements, char* filename){
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file\n");
        exit(1);
    }

    fwrite(SA, sizeof(int64_t), n_elements, file);
    fclose(file);

}

int main(int argc, char** argv) {

    if(argc != 3){
        printf("Usage: %s input.txt output.sa\n", argv[0]);
        return 1;
    }

    FILE *file;
    uint8_t *buffer;
    long fileLength;

    // Open the file in binary mode
    file = fopen(argv[1], "rb");
    if (file == NULL) {
        fprintf(stderr, "Unable to open file\n");
        return 1;
    }

    // Get the file length
    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the buffer
    buffer = (char *)malloc(fileLength * sizeof(char));
    if (buffer == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return 1;
    }

    // Read the file into the buffer
    fread(buffer, fileLength, 1, file);

    // Close the file
    fclose(file);

    int64_t* SA = malloc(fileLength * sizeof(int64_t));
    libsais64_omp(buffer, SA, fileLength, 0, 0, 4);

    write(SA, fileLength, argv[2]);

    // Free the allocated memory
    free(buffer);

    return 0;
}

