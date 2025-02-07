//LAB2 TRANSPOSITION TECHNIQUE

//IMPLEMENT ROW-TRANSPOSE CIPHER

#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char* text, int key, char* ciphertext) {
    int len = strlen(text);
    int rows = (len / key) + (len % key != 0);
    char grid[rows][key];
    
    // Fill the grid with the plaintext
    int i = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < key; col++) {
            if (i < len) {
                grid[row][col] = text[i++];
            } else {
                grid[row][col] = 'X'; // Padding character
            }
        }
    }

    // Display the grid
    printf("\nGrid (rows and columns):\n");
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < key; col++) {
            printf("%c ", grid[row][col]);
        }
        printf("\n");
    }

    // Read column by column to create ciphertext
    int idx = 0;
    for (int col = 0; col < key; col++) {
        for (int row = 0; row < rows; row++) {
            ciphertext[idx++] = grid[row][col];
        }
    }
    ciphertext[idx] = '\0'; // Null-terminate the ciphertext
}

void decrypt(char* ciphertext, int key, char* decryptedText) {
    int len = strlen(ciphertext);
    int rows = (len / key) + (len % key != 0);
    char grid[rows][key];
    
    // Fill the grid column by column with the ciphertext
    int idx = 0;
    for (int col = 0; col < key; col++) {
        for (int row = 0; row < rows; row++) {
            if (idx < len) {
                grid[row][col] = ciphertext[idx++];
            } else {
                grid[row][col] = 'X'; // Padding character (should not be needed)
            }
        }
    }

    // Read row by row to reconstruct the decrypted text
    idx = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < key; col++) {
            decryptedText[idx++] = grid[row][col];
        }
    }
    decryptedText[idx] = '\0'; // Null-terminate the decrypted text

    // Remove padding 'X' characters from the end of the decrypted text
    for (int i = strlen(decryptedText) - 1; i >= 0; i--) {
        if (decryptedText[i] == 'X') {
            decryptedText[i] = '\0';
        } else {
            break;
        }
    }
}

int main() {
    char text[100], ciphertext[100], decryptedText[100];
    int key;

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);

    // Remove the newline character if present
    text[strcspn(text, "\n")] = '\0';

    printf("Enter the key (number of columns): ");
    scanf("%d", &key);

    // Encrypt the text using Row-Transpose Cipher
    encrypt(text, key, ciphertext);
    printf("\nCiphertext: %s\n", ciphertext);

    // Decrypt the ciphertext using Row-Transpose Cipher
    decrypt(ciphertext, key, decryptedText);
    printf("\nDecrypted Text: %s\n", decryptedText);

    return 0;
}

