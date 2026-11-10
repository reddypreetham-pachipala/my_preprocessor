#include <stdio.h>
#include <string.h>

extern FILE *fp, *fs, *fo;

void headerFile(char *s)
{
    char ch, b[10];
    int flag = 0, i = 0, file = 0;

    fp = fopen(s, "r+");

    if (fp == NULL)
    {
        printf("File is not present\n");
        return;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        if (ch == '<')
        {
            flag = 1;
            continue;
        }
        else if (ch == '>')
        {
            char path[30] = "/usr/include/";

            flag = 0;
            b[i] = '\0';
            i = 0;

            strcat(path, b);

            fs = fopen(path, "r");

            if (fs == NULL)
                printf("File is not present\n");
            else
            {
                if (file == 0)
                {
                    fo = fopen("data.i", "w");
                    file = 1;
                }
                else
                {
                    fo = fopen("data.i", "a");
                }

                while ((ch = fgetc(fs)) != EOF)
                    fputc(ch, fo);

                fclose(fo);
            }
        }

        if (flag == 1)
        {
            b[i] = ch;
            i++;
        }
    }

    fclose(fs);
    fclose(fp);
}
