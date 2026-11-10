#include <stdio.h>
#include <string.h>

extern FILE *fp, *fo;

void macroReplacement(char *s)
{
    int i=0,j=0,flag=0,k=0,count=0,m=0;
    int x=0,a=0,n=0,r=0,t=0,found=0;

    char b[100],ch,buffer[100];
    char function_args[100][100];
    char function_value[100][100];
    char actual_args[10][50];
    char temp[100],word[20],result[100];

    fp=fopen(s,"r+");
    fo=fopen("data.i","a");

    if(fp==0)
    {
        printf("No file\n");
        return;
    }

    while(fgets(b,100,fp))
    {
        if(strncmp(b,"#define ",8)==0)
            count++;
    }

    rewind(fp);

    char macro_body[count][20];
    char macro_value[count][100];
    char macro_function[count][20];

    while(fgets(b,100,fp))
    {
        if(strncmp(b,"#define ",8)==0)
        {
            char *p=b+8;

            while(*p==' ')
                p++;

            j=0;

            if(strchr(p,'(')!=NULL && strchr(p,'(')<strchr(p,' '))
            {
                while(*p!='(')
                    macro_function[m][j++]=*p++;

                macro_function[m][j]='\0';
                p++;

                n=0;

                while(*p!=')' && *p!='\0')
                    function_args[m][n++]=*p++;

                function_args[m][n]='\0';

                if(*p==')')
                    p++;

                while(*p==' ')
                    p++;

                strcpy(function_value[m],p);
                function_value[m][strcspn(function_value[m],"\n")]='\0';

                m++;
            }
            else
            {
                while(*p!=' ' && *p!='\n' && *p!='\0')
                    macro_body[i][j++]=*p++;

                macro_body[i][j]='\0';

                while(*p==' ')
                    p++;

                strcpy(macro_value[i],p);
                macro_value[i][strcspn(macro_value[i],"\n")]='\0';

                i++;
            }
        }
    }

    rewind(fp);

    while(fgets(b,100,fp))
    {
        if(strcmp(b,"int main()\n")==0 ||
           strcmp(b,"void main()\n")==0)
            break;
    }

    fseek(fp,-strlen(b),SEEK_CUR);

    i=0;

    while((ch=fgetc(fp))!=-1)
    {
        if(ch=='"' && flag==0)
        {
            flag=1;
            fprintf(fo,"%c",ch);
            continue;
        }
        else if(ch=='"' && flag==1)
        {
            flag=0;
            fprintf(fo,"%c",ch);
            continue;
        }

        if(flag==1)
        {
            fprintf(fo,"%c",ch);
            continue;
        }

        if((ch>='A'&&ch<='Z') ||
           (ch>='a'&&ch<='z') ||
           (ch>='0'&&ch<='9') ||
           ch=='_')
        {
            buffer[i++]=ch;
        }
        else
        {
            buffer[i]='\0';

            if(i>0)
            {
                for(k=0;k<count;k++)
                {
                    if(k<m && strcmp(buffer,macro_function[k])==0)
                        break;
                }

                if(k<m && ch=='(')
                {
                    a=0;
                    x=0;

                    while((ch=fgetc(fp))!=-1 && ch!=')')
                    {
                        if(ch==',')
                        {
                            actual_args[a][x]='\0';
                            a++;
                            x=0;
                        }
                        else
                        {
                            actual_args[a][x++]=ch;
                        }
                    }

                    actual_args[a][x]='\0';

                    strcpy(temp,function_value[k]);
                    strcpy(result,"");

                    r=0;
                    t=0;

                    while(temp[r]!='\0')
                    {
                        if((temp[r]>='A'&&temp[r]<='Z') ||
                           (temp[r]>='a'&&temp[r]<='z') ||
                           temp[r]=='_')
                        {
                            word[t++]=temp[r++];
                        }
                        else
                        {
                            word[t]='\0';

                            if(t>0)
                            {
                                char args_copy[100];
                                strcpy(args_copy,function_args[k]);

                                char *p=strtok(args_copy,",");

                                int z=0;
                                found=0;

                                while(p!=NULL)
                                {
                                    if(strcmp(word,p)==0)
                                    {
                                        strcat(result,actual_args[z]);
                                        found=1;
                                        break;
                                    }

                                    z++;
                                    p=strtok(NULL,",");
                                }

                                if(found==0)
                                    strcat(result,word);

                                t=0;
                            }

                            x=strlen(result);
                            result[x++]=temp[r++];
                            result[x]='\0';
                        }
                    }

                    word[t]='\0';

                    if(t>0)
                    {
                        char args_copy[100];
                        strcpy(args_copy,function_args[k]);

                        char *p=strtok(args_copy,",");

                        int z=0;
                        found=0;

                        while(p!=NULL)
                        {
                            if(strcmp(word,p)==0)
                            {
                                strcat(result,actual_args[z]);
                                found=1;
                                break;
                            }

                            z++;
                            p=strtok(NULL,",");
                        }

                        if(found==0)
                            strcat(result,word);
                    }

                    fprintf(fo,"%s",result);
                }
                else
                {
                    for(k=0;k<count;k++)
                    {
                        if(strcmp(buffer,macro_body[k])==0)
                            break;
                    }

                    if(k<count)
                        fprintf(fo,"%s",macro_value[k]);
                    else
                        fprintf(fo,"%s",buffer);

                    fprintf(fo,"%c",ch);
                }
            }
            else
            {
                fprintf(fo,"%c",ch);
            }

            i=0;
        }
    }

    fclose(fp);
    fclose(fo);

    remove("temp.i");
}
