#include <stdio.h>
#include "word.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int getNextWord(FILE *fp, char *buf, int bufsize);

int CharToInt32(char number[]);

int simplePowerOf(int x, int exp);

void dummyProtocol()
{
    printf("It appears that you've tried to use the command line arguments without knowing what it does...\n");
    printf("This command takes two arguments. One of which is required. And the other being optional.\n");
    printf("The first argument is the path to the file you would like to read. For example \"a.exe ./path/to/file\"");
    printf("The second and optional command is the word rankings you would like to display. \nFor example if you would like to see the 5 most common words, you may write \"a.exe ./path/to/file 5\"");
    printf("NOTE: if you do not use the second argument it will always show the top 10 most commmon words.\n");

    return;
}

int main(int argc, char *argv[])
{

    int max = 10;
    if (argc == 3)
    {
        max = atoi(argv[2]);
    }
    if (max == 0)
    {
        dummyProtocol();
        return 0;
    }
    if (argv[1] == NULL || atoi(argv[1]) != 0)
    {
        dummyProtocol();
        return 0;
    }

    FILE *fp;
    fp = fopen(argv[1], "r");
    char buffer[MAX_WORD];

    WordListPtr AddressOfWords[10];

    // Get the first word and put it in a new node
    getNextWord(fp, buffer, MAX_WORD);
    WordListPtr firstWord = createNode(buffer);

    while (getNextWord(fp, buffer, MAX_WORD))
    {

        WordListPtr temp = firstWord;

        while (temp != NULL)
        {
            if ((strcmp(buffer, temp->WordValue.str)) == 0)
            {
                // A word already exists in our list
                temp->WordValue.freq++;
                break;
                // Add and escape loop
            }
            if (temp->next == NULL)
            {
                // End of List and still no match.
                // Add word to LinkedList
                temp->next = createNode(buffer);
                temp = temp->next;
                break;
            }
            temp = temp->next;
        }
    }

    fclose(fp);

    WordListPtr temp = merge_sort_bottom_up(firstWord);
    WordListPtr sorted;

    int i = 0;
    printf("WORD FREQUENCIES (TOP %d): \n", max);
    while (temp != NULL)
    {
        if (i == max)
        {
            break;
        }
        printf("%s\t%d\n", temp->WordValue.str, temp->WordValue.freq);
        temp = temp->next;
        i++;
    }

    return 0;
}

int simplePowerOf(int x, int exp)
{
    int i;
    int result = x;
    for (i = 0; i < exp; i++)
    {
        result *= x;
    }
    return result;
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