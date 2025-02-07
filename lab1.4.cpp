//WAP to implement Hill Cipher

#include <stdio.h>
#include <string.h>
#include <ctype.h>
// Function to compute the determinant of a 2x2 matrix
int determinant(int key[2][2]) {

    return (key[0][0] * key[1][1] - key[0][1] * key[1][0]);

}
// Function to calculate modular inverse
int modInverse(int a, int m) {

    a = a % m;

    for (int x = 1; x < m; x++) {

        if ((a * x) % m == 1)

            return x;

    }

    return -1; // Modular inverse does not exist

}
// Function to prepare the plaintext
void prepareText(char text[]) {

    int len = strlen(text);

    if (len % 2 != 0) {

        text[len] = 'x'; // Append 'x' if length is odd

        text[len + 1] = '\0';

    }

}
// Function to encrypt plaintext using Hill cipher
void encrypt(char plaintext[], int key[2][2], char ciphertext[]) {

    int len = strlen(plaintext);

    for (int i = 0; i < len; i += 2) {

        int p1 = plaintext[i] - 'a';
        int p2 = plaintext[i + 1] - 'a';
        // Apply the key matrix
        ciphertext[i] = ((key[0][0] * p1 + key[0][1] * p2) % 26) + 'a';
        ciphertext[i + 1] = ((key[1][0] * p1 + key[1][1] * p2) % 26) + 'a';

    }

    ciphertext[len] = '\0'; // Null-terminate the ciphertext

}
// Function to decrypt ciphertext using Hill cipher
void decrypt(char ciphertext[], int key[2][2], char plaintext[]) {

    int det = determinant(key);

    int detMod = (det % 26 + 26) % 26; // Determinant mod 26

    int invDet = modInverse(detMod, 26);
    if (invDet == -1) {

        printf("Matrix is not invertible under mod 26.\n");

        return;

    }
    // Compute the inverse key matrix
    int invKey[2][2];

    invKey[0][0] = (key[1][1] * invDet) % 26;

    invKey[0][1] = (-key[0][1] * invDet + 26) % 26;

    invKey[1][0] = (-key[1][0] * invDet + 26) % 26;

    invKey[1][1] = (key[0][0] * invDet) % 26;

 

    int len = strlen(ciphertext);

    for (int i = 0; i < len; i += 2) {

        int c1 = ciphertext[i] - 'a';

        int c2 = ciphertext[i + 1] - 'a';

 

        // Apply the inverse key matrix

        plaintext[i] = ((invKey[0][0] * c1 + invKey[0][1] * c2) % 26) + 'a';

        plaintext[i + 1] = ((invKey[1][0] * c1 + invKey[1][1] * c2) % 26) + 'a';

    }

    plaintext[len] = '\0'; // Null-terminate the plaintext

}
int main() {

    int key[2][2];

    char plaintext[100], ciphertext[100];

    int choice;

 

    printf("Enter 2x2 key matrix (integers):\n");

    for (int i = 0; i < 2; i++) {

        for (int j = 0; j < 2; j++) {

            scanf("%d", &key[i][j]);

        }

    }
    printf("Enter the text: ");

    scanf("%s", plaintext);
    // Convert text to lowercase and remove non-alphabet characters
	for (int i = 0; plaintext[i]; i++) {

        plaintext[i] = tolower(plaintext[i]);

    }
    prepareText(plaintext);
    printf("Choose an option:\n1. Encrypt\n2. Decrypt\nYour choice: ");
    scanf("%d", &choice);
    if (choice == 1) {

        encrypt(plaintext, key, ciphertext);

        printf("Encrypted text: %s\n", ciphertext);

    } else if (choice == 2) {

        decrypt(plaintext, key, ciphertext);

        printf("Decrypted text: %s\n", ciphertext);

    } else {

        printf("Invalid choice.\n");

    }
    return 0;
}


