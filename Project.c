#include <stdio.h>
#include "word.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getNextWord(FILE *fp, char *buf, int bufsize);

int main(int argc, char *argv[])
{
    char text[] = "./alice.txt";
    FILE *fp;
    fp = fopen(text, "r");
    char buffer[32];

    while (getNextWord(fp, buffer, 32))
    {
        printf("%s", buffer);
    }

    return 0;
}

int getNextWord(FILE *fp, char *buf, int bufsize)
{
    char *p = buf;
    char c;
    // skip all non-word characters
    do
    {
        c = fgetc(fp);
        if (c == EOF)
            return 0;
    } while (!isalpha(c));
    // read word chars
    do
    {
        if (p - buf < bufsize - 1)
            *p++ = tolower(c);
        c = fgetc(fp);
    } while (isalpha(c));
    // finalize word
    *p = '\0';
    return 1;
}