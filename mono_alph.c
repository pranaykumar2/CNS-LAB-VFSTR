#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void monoalphabeticEncryption()
{
    char plain_text[100], cipher_text[100];
    char mapping[26] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    int i;

    printf("Enter the plain text you want to encrypt (only uppercase alphabets): ");
    fgets(plain_text, sizeof(plain_text), stdin);
    plain_text[strcspn(plain_text, "\n")] = '\0';


    for (i = 0; plain_text[i]; i++) {
        if (isalpha(plain_text[i])) {
            int index = toupper(plain_text[i]) - 'A';
            cipher_text[i] = mapping[index];
        } else {
            cipher_text[i] = plain_text[i];
        }
    }
    cipher_text[i] = '\0';

    printf("The encrypted version of your text is: %s\n", cipher_text);
}

int main()
{
    while (1)
    {
        int option;

        printf("\n----------------------------\nImplementing Monoalphabetic Cipher\n----------------------------");

        printf("\nChoose an option:\n1. Encrypt a text using Monoalphabetic Cipher\n2. Exit\n==> ");
        scanf("%d", &option);
        getchar();

        switch (option) {
            case 1:
                monoalphabeticEncryption();
                break;
            case 2:
                printf("\nExiting Program!! Thank you\n");
                exit(0);
            default:
                printf("\nInvalid option selected, Please choose again!!\n");
                break;
        }
    }

    return 0;
}
