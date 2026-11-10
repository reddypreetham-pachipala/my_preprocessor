#include <stdio.h>
#include <string.h>

extern FILE *fp, *f1;

void commentRemoval(char *s)
{
    f1 = fopen("temp.i", "w");
    fp = fopen(s, "r+");

    char ch;

    if (fp == NULL)
    {
        printf("File is not present\n");
        return;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '/')
        {
            ch = fgetc(fp);

            if (ch == '/')
            {
                while ((ch = fgetc(fp)) != '\n')
                    continue;
            }
            else if (ch == '*')
            {
                while ((ch = fgetc(fp)) != '*')
                    continue;

                if ((ch = fgetc(fp)) == '/')
                {
                    while ((ch = fgetc(fp)) != '\n')
                        continue;
                }
            }
        }

        fprintf(f1, "%c", ch);
    }

    fclose(fp);
    fclose(f1);
}
