#include <stdio.h>
#include <string.h>

FILE *fp, *fs, *fo, *f1;

void headerFile(char *);        // Header file inclusion
void commentRemoval(char *);    // Comment removal
void macroReplacement(char *); // Macro replacement

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./a.out filename\n");
        return 1;
    }

    headerFile(argv[1]);
    commentRemoval(argv[1]);
    macroReplacement("temp.i");

    return 0;
}
