#include <stdio.h>
#include <string.h>


#define MAX_NODES 21000000
#define BACK_MAX 1024

typedef struct {
    char element;
    int length;
    int offset;
} Table;

FILE *final;
Table node[MAX_NODES];
char allText[MAX_NODES];
int size = 0;
int textLength = 0;

void AddToBinaryFile() {
    FILE *out = fopen("compres.bin", "wb");
    if (!out) return;

    for (int i = 0; i < size; i++) {
        unsigned short offset = (unsigned short)node[i].offset;
        unsigned char length = (unsigned char)node[i].length;
        char ch = node[i].element;

        fwrite(&offset, sizeof(unsigned short), 1, out);
        fwrite(&length, sizeof(unsigned char), 1, out);
        fwrite(&ch, sizeof(char), 1, out);
    }
    fclose(out);
}

void Zip(FILE *file) {
    int ch;
    while ((ch = getc(file)) != EOF && textLength < MAX_NODES) {
        allText[textLength++] = (char)ch;
    }

    for (int i = 0; i < textLength;) {
        int maxLen = 0, bestOffset = 0;
	int beforeStart = (i > BACK_MAX) ? (i - BACK_MAX) : 0;
        for (int j = beforeStart; j<i; j++) {
            int k = 0;
            while (i + k < textLength && allText[j + k] == allText[i + k]) {
                k++;
            }
            if (k > maxLen) {
                maxLen = k;
                bestOffset = i - j;
            }
        }

        Table entry;
        entry.offset = (maxLen > 0) ? bestOffset : 0;
        entry.length = maxLen;
        entry.element = (i + maxLen < textLength) ? allText[i + maxLen] : '#';

        node[size++] = entry;
        i += (maxLen > 0) ? maxLen + 1 : 1;
    }

    AddToBinaryFile();
}

