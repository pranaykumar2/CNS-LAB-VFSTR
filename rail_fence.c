#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void railFenceCipher(char* msg, int key)
{
    int msgLen = strlen(msg), i, j, k = -1, row = 0, col = 0;
    char railMatrix[key][msgLen];

    for(i = 0; i < key; i++)
    {
        for(j = 0; j < msgLen; j++)
        {
            railMatrix[i][j] = '\n';
        }
    }

    for(i = 0; i < msgLen; i++)
    {
        railMatrix[row][col++] = msg[i];

        if(row == 0 || row == key - 1)
        {
            k = k * (-1);
        }
        row = row + k;
    }

    printf("\nEncrypted Message: ");
    for(i = 0; i < key; i++)
    {
        for(j = 0; j < msgLen; j++)
        {
            if(railMatrix[i][j] != '\n')
            {
                printf("%c", railMatrix[i][j]);
            }
        }
    }
}


int main()
{
    system("cls");
    printf("\n---------------------- Implementation of Rail-fence Cipher --------------------\n");
    char message[1024];
    int depth, row = 0, col = 0, i, j, k;
    printf("\nEnter the mesage <=:=> ");
    fgets(message, sizeof(message), stdin);
    message[strcspn(message, "\n")] = '\0';

    printf("\nEnter the depth <=:=> ");
    scanf("%d", &depth);

    railFenceCipher(message, depth);
}
