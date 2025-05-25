#include "Zipp.h"
#include <stdio.h>
#include <string.h>

int main() {
    char type;
    printf("for zip enter z ,for unzip enter u : ");
    scanf(" %c", &type);  // note the space before %c to skip newline

    if (type == 'z') {
        printf("file name : ");
        char name[1000];
        scanf("%s", name);

        FILE *file = fopen(name, "r+");
        if (file == NULL) {
            printf("Failed to open file.\n");
            return 1;
        }

        Zip(file);
        fclose(file);

    } else if (type == 'u') {
        printf("compressed file name (without .zipp): ");
        char name[1000];
        scanf("%s", name);
        Decompress(name, "output.txt");
        printf("Decompressed into output.txt\n");

    } else {
        printf("Invalid option.\n");
    }

    return 0;
}
