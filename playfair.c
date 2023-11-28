#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char list1[] = "abcdefghiklmnopqrstuvwxyz";

void generateKeyTable(char* key, char* table) {
   int len = strlen(key);
   int index = 0;
   for (int i = 0; i < len; i++) {
       if (key[i] == 'j') key[i] = 'i';
       int flag = 0;
       for (int j = 0; j < index; j++) {
           if (key[i] == table[j]) {
               flag = 1;
               break;
           }
       }
       if (flag == 0) {
           table[index++] = key[i];
       }
   }
   for (int i = 0; i < 25; i++) {
       int flag = 0;
       for (int j = 0; j < index; j++) {
           if (list1[i] == table[j]) {
               flag = 1;
               break;
           }
       }
       if (flag == 0) {
           table[index++] = list1[i];
       }
   }
   table[index] = '\0';
}

char* InsertString(char* str, int index, char* insert) {
    char* newStr = malloc(strlen(str) + strlen(insert) + 1);
    strncpy(newStr, str, index);
    newStr[index] = '\0';
    strcat(newStr, insert);
    strcat(newStr, str + index);
    free(str);
    return newStr;
}

char* AppendString(char* str, char* append) {
    char* newStr = malloc(strlen(str) + strlen(append) + 1);
    strcpy(newStr, str);
    strcat(newStr, append);
    free(str);
    return newStr;
}

void encryptByPlayfairCipher(char* table, char* plainText, char* cipherText) {
   int len = strlen(plainText);
   int cipherIndex = 0;
   for (int i = 0; i < len; i += 2) {
       int row1, col1, row2, col2;
       for (int j = 0; j < 5; j++) {
           for (int k = 0; k < 5; k++) {
               if (table[j * 5 + k] == plainText[i]) {
                  row1 = j;
                  col1 = k;
               }
               if (table[j * 5 + k] == plainText[i + 1]) {
                  row2 = j;
                  col2 = k;
               }
           }
       }
       if (row1 == row2) {
           cipherText[cipherIndex++] = table[row1 * 5 + (col1 + 1) % 5];
           cipherText[cipherIndex++] = table[row2 * 5 + (col2 + 1) % 5];
       } else if (col1 == col2) {
           cipherText[cipherIndex++] = table[((row1 + 1) % 5) * 5 + col1];
           cipherText[cipherIndex++] = table[((row2 + 1) % 5) * 5 + col2];
       } else {
           cipherText[cipherIndex++] = table[row1 * 5 + col2];
           cipherText[cipherIndex++] = table[row2 * 5 + col1];
       }
   }
   cipherText[cipherIndex] = '\0';
}


void printMatrix(char* table) {
   for (int i = 0; i < 5; i++) {
       for (int j = 0; j < 5; j++) {
           printf("%c ", table[i * 5 + j]);
       }
       printf("\n");
   }
}

int main() {
   char text_Plain[100];
   char key[100];

   printf("Enter the plain text: ");
   scanf(" %s", text_Plain);

   printf("Enter the key: ");
   scanf(" %s", key);

   printf("Key text: %s\n", key);

   char Matrix[100];
   generateKeyTable(key, Matrix);

   char CipherText[100];
   encryptByPlayfairCipher(Matrix, text_Plain, CipherText);

   printf("Updated Plain Text: %s\n", text_Plain);

   printf("Matrix:\n");
   printMatrix(Matrix);

   printf("CipherText: %s\n", CipherText);

   return 0;
}
