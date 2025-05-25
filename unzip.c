#include <stdio.h>
#include <stdlib.h>

#define MAX_OUTPUT 21000000

char output[MAX_OUTPUT];
int outputIndex = 0;


void Decompress(const char *inputFile, const char *outputFile) {
    FILE *in = fopen(inputFile, "rb");
    if (!in) {
        printf("Failed to open input file.\n");
        return;
    }

    unsigned short offset;
    unsigned char length;
    char ch;

    while (fread(&offset, sizeof(unsigned short), 1, in) == 1 &&
           fread(&length, sizeof(unsigned char), 1, in) == 1 &&
           fread(&ch, sizeof(char), 1, in) == 1) {

        if (length > 0 && offset > 0) {
            int start = outputIndex - offset;
            for (int i = 0; i < length && outputIndex < MAX_OUTPUT; i++) {
                output[outputIndex] = output[start + i];
                outputIndex++;
            }
        }
        if (ch != '#') {
            output[outputIndex++] = ch;
        }
    }

    fclose(in);

    FILE *out = fopen(outputFile, "w");
    if (!out) {
        printf("Failed to open output file.\n");
        return;
    }

    fwrite(output, sizeof(char), outputIndex, out);
    fclose(out);
}

