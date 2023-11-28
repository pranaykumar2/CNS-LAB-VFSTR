#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void encryption()
{
      	int i;
      	char cipher_text[100], plain_text[100];
        int key;

      	printf("Enter the plain text you want to encrypt (only uppercase alphabets): ");
      	fgets(plain_text, sizeof(plain_text), stdin);
      	plain_text[strcspn(plain_text, "\n")] = '\0';

      	printf("\nEnter the key for encryption : ");
        scanf("%d", &key);

        for (int i = 0; plain_text[i]; i++)
        {
             cipher_text[i] = (plain_text[i] - 'A' + key) % 26 + 'A';
        }
      	cipher_text[i] = '\0';

      	printf("\nThe encrypted version of your text is: %s", cipher_text);
}

void decryption()
{
      	int i;
      	char cipher_text[100], plain_text[100];
        int key;

      	printf("Enter the text you want to decrypt (only uppercase alphabets): ");
      	fgets(cipher_text, sizeof(cipher_text), stdin);
      	cipher_text[strcspn(cipher_text, "\n")] = '\0';

        printf("\nEnter the key for encryption : ");
        scanf("%d", &key);

      	for(i = 0; cipher_text[i]; i++)
      	{
      		  plain_text[i] = (cipher_text[i] - 'A' - key + 26) % 26 + 'A';
      	}
      	plain_text[i] = '\0';
      	printf("\nThe decrypted version of your text is: %s", plain_text);
}

int main()
{
    	while(1)
    	{
        		int option;

        		printf("\n----------------------------\nImplementing Ceaser Cipher\n----------------------------");

        		printf("\nChoose an option:\n1. Encrypt a text\n2. Decrypt a text\n3. Exit\n==> ");
        		scanf("%d", &option);
        		getchar();

        		switch(option)
        		{
          			case 1: encryption(); break;
          			case 2: decryption(); break;
          			case 3: printf("\nExiting Program!! Thank you\n"); exit(0);
          			default: printf("\nInvalid option selected, Please choose again!!\n"); break;
    		    }
    	}
}
