#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void hill_cipher_encrypt(int plain_matrix[], int key[][10], int size, int length, char *cipher_text);
void print_encrypt(char *cipher_text);

int main()
{
        char plain_text[100];
        int size, i, j;
        system("cls");
        printf("-------------------Implementing Hill Cipher------------------------");
        printf("\n\n\tEnter Plain Text (IN UPPERCASE): \n\t>");
        fgets(plain_text, sizeof(plain_text), stdin);
        plain_text[strcspn(plain_text,"\n")] = '\0';
        printf("\n\tEnter size of key matrix: ");
        scanf("%d", &size);
        printf("\n\tEnter the key values (%dX%d): \n", size, size);

        int key[10][10], plain_matrix[10];
        for(i = 0; i < size; i++)
        {
            for(j = 0; j < size; j++)
            {
                scanf("%d", &key[i][j]);
            }
        }

        int plain_text_num[strlen(plain_text)];

        for(i = 0; plain_text[i]; i++)
        {
            plain_text_num[i] = plain_text[i] - 'A';
        }

        char cipher_text[100] = "";
        int loop = 0;
        while(loop < strlen(plain_text))
        {
          for(j = 0; j < size; j++)
          {
            if(loop+j < strlen(plain_text))
            {
              plain_matrix[j] = plain_text_num[loop+j];
            }
          }
          hill_cipher_encrypt(plain_matrix, key, size, strlen(plain_text), cipher_text);
          loop = loop + size;
        }
        print_encrypt(cipher_text);
        return 0;
}

void hill_cipher_encrypt(int plain_matrix[], int key[][10], int size, int length, char *cipher_text)
{
        int cipher_text_num[10] = {0};
        char temp[10];
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                cipher_text_num[i] += plain_matrix[j] * key[j][i];
            }
            cipher_text_num[i] %= 26;
            temp[i] = cipher_text_num[i] + 'A';
        }
        temp[size] = '\0';
        strcat(cipher_text,temp);
}

void print_encrypt(char* cipher_text){
          for(int i = 0; cipher_text[i]; i++)
          {
              printf("%c ",cipher_text[i]);
          }
          printf("\n");
}
