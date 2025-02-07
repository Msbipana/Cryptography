//WAP to implement play-fair matrix cipher

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Function to create Playfair Matrix
void createMatrix(char *key, char matrix[SIZE][SIZE]) {
    int used[26] = {0};  // Track if a letter has already been used in the matrix
    int row = 0, col = 0;
    
    // Convert key to uppercase and replace 'J' with 'I'
    for (int i = 0; key[i]; i++) {
        key[i] = toupper(key[i]);
        if (key[i] == 'J') key[i] = 'I';  // Treat 'J' as 'I'
    }

    // Add unique characters from the key to the matrix
    for (int i = 0; key[i] != '\0'; i++) {
        if (!used[key[i] - 'A']) {
            used[key[i] - 'A'] = 1;
            matrix[row][col++] = key[i];
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }

    // Add the remaining letters of the alphabet
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch != 'J' && !used[ch - 'A']) {  // Skip 'J' and already used letters
            matrix[row][col++] = ch;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }
}

// Function to find the position of a character in the matrix
void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to format the plaintext by replacing 'J' with 'I' and adding 'X' if necessary
void formatText(char *text, char *formattedText) {
    int length = strlen(text);
    int index = 0;

    // Convert to uppercase and replace 'J' with 'I'
    for (int i = 0; i < length; i++) {
        text[i] = toupper(text[i]);
        if (text[i] == 'J') text[i] = 'I';
    }

    // Process the text to handle duplicate characters
    for (int i = 0; i < length; i++) {
        formattedText[index++] = text[i];
        if (i + 1 < length && text[i] == text[i + 1]) {
            formattedText[index++] = 'X';  // Add 'X' between duplicate letters
        }
    }

    // Add an 'X' at the end if the length is odd
    if (index % 2 != 0) {
        formattedText[index++] = 'X';
    }

    formattedText[index] = '\0';
}

// Function to encrypt a digraph (pair of characters)
void encryptDigraph(char matrix[SIZE][SIZE], char a, char b, char *encA, char *encB) {
    int row1, col1, row2, col2;
    findPosition(matrix, a, &row1, &col1);
    findPosition(matrix, b, &row2, &col2);

    if (row1 == row2) {
        // Same row, shift columns
        *encA = matrix[row1][(col1 + 1) % SIZE];
        *encB = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        // Same column, shift rows
        *encA = matrix[(row1 + 1) % SIZE][col1];
        *encB = matrix[(row2 + 1) % SIZE][col2];
    } else {
        // Rectangle, swap columns
        *encA = matrix[row1][col2];
        *encB = matrix[row2][col1];
    }
}

// Function to encrypt the plaintext
void encrypt(char *plaintext, char *key, char *ciphertext) {
    char matrix[SIZE][SIZE];
    createMatrix(key, matrix);

    char formattedText[100];
    formatText(plaintext, formattedText);

    int length = strlen(formattedText);
    int index = 0;

    // Encrypt the formatted text in pairs
    for (int i = 0; i < length; i += 2) {
        char encA, encB;
        encryptDigraph(matrix, formattedText[i], formattedText[i + 1], &encA, &encB);
        ciphertext[index++] = encA;
        ciphertext[index++] = encB;
    }

    ciphertext[index] = '\0';
}

// Function to decrypt a digraph (pair of characters)
void decryptDigraph(char matrix[SIZE][SIZE], char a, char b, char *decA, char *decB) {
    int row1, col1, row2, col2;
    findPosition(matrix, a, &row1, &col1);
    findPosition(matrix, b, &row2, &col2);

    if (row1 == row2) {
        // Same row, shift columns
        *decA = matrix[row1][(col1 - 1 + SIZE) % SIZE];
        *decB = matrix[row2][(col2 - 1 + SIZE) % SIZE];
    } else if (col1 == col2) {
        // Same column, shift rows
        *decA = matrix[(row1 - 1 + SIZE) % SIZE][col1];
        *decB = matrix[(row2 - 1 + SIZE) % SIZE][col2];
    } else {
        // Rectangle, swap columns
        *decA = matrix[row1][col2];
        *decB = matrix[row2][col1];
    }
}

// Function to decrypt the ciphertext
void decrypt(char *ciphertext, char *key, char *plaintext) {
    char matrix[SIZE][SIZE];
    createMatrix(key, matrix);

    int length = strlen(ciphertext);
    int index = 0;

    // Decrypt the ciphertext in pairs
    for (int i = 0; i < length; i += 2) {
        char decA, decB;
        decryptDigraph(matrix, ciphertext[i], ciphertext[i + 1], &decA, &decB);
        plaintext[index++] = decA;
        plaintext[index++] = decB;
    }

    plaintext[index] = '\0';
}

// Function to print the matrix in matrix form
void printMatrix(char matrix[SIZE][SIZE]) {
    printf("\nPlayfair Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    char key[100], plaintext[100], ciphertext[100], decryptedText[100];
    
    // Ask the user for the key and plaintext
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';  // Remove the newline character
    
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';  // Remove the newline character
    
    // Create the Playfair matrix from the key
    char matrix[SIZE][SIZE];
    createMatrix(key, matrix);
    
    // Print the Playfair matrix
    printMatrix(matrix);

    // Encrypt the plaintext
    encrypt(plaintext, key, ciphertext);
    printf("\nCiphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, key, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}

