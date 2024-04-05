#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum State {
    Normal,
    FontTag,
    EndTag
};

void odstranZnackyFontu(char* html) {
    enum State state = Normal;
    char* output = html;
    char* input = html;

    while (*input != '\0') {
        switch (state) {
            case Normal:
                if (strncmp(input, "<font", 5) == 0) {
                    state = FontTag;
                } else {
                    *output++ = *input;
                }
                break;
            case FontTag:
                if (strncmp(input, "</font>", 7) == 0) {
                    state = EndTag;
                }
                break;
            case EndTag:
                if (*input == '>') {
                    state = Normal;
                }
                break;
        }
        input++;
    }
    *output = '\0';
}

int main() {
    FILE *inputFile = fopen("/Users/liborvyleta/Documents/Projekty/C/KA/test.txt", "r");
    if (inputFile == NULL) {
        printf("Nelze otevrit test.txt\n");
        return 1;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    char *html = malloc(fileSize + 1);
    fread(html, 1, fileSize, inputFile);
    html[fileSize] = '\0';

    fclose(inputFile);

    odstranZnackyFontu(html);

    FILE *outputFile = fopen("/Users/liborvyleta/Documents/Projekty/C/KA/output.txt", "w");
    if (outputFile == NULL) {
        printf("Nelze otevrit output.txt\n");
        free(html);
        return 1;
    }

    fprintf(outputFile, "%s", html);
    fclose(outputFile);

    free(html);

    return 0;
}
