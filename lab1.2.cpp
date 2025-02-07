//WAP to implement polyalphabetic cipher

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to encrypt a message using the polyalphabetic cipher
void encrypt(char* plaintext, char* keyword, char* ciphertext) {
    int i = 0, j = 0;
    int pt_length = strlen(plaintext);
    int kw_length = strlen(keyword);

    while (i < pt_length) {
        // Check if the current character is alphabetic
        if (isalpha(plaintext[i])) {
            char pt_char = toupper(plaintext[i]);
            char kw_char = toupper(keyword[j % kw_length]);
            // Shift plaintext character using keyword character
            ciphertext[i] = ((pt_char - 'A' + (kw_char - 'A')) % 26) + 'A';
            j++; // Only increment j for alphabetic characters
        } else {
            // Non-alphabet characters are not changed
            ciphertext[i] = plaintext[i];
        }
        i++;
    }
    ciphertext[i] = '\0'; // Null terminate the ciphertext string
}

// Function to decrypt the message using the polyalphabetic cipher
void decrypt(char* ciphertext, char* keyword, char* plaintext) {
    int i = 0, j = 0;
    int ct_length = strlen(ciphertext);
    int kw_length = strlen(keyword);

    while (i < ct_length) {
        // Check if the current character is alphabetic
        if (isalpha(ciphertext[i])) {
            char ct_char = toupper(ciphertext[i]);
            char kw_char = toupper(keyword[j % kw_length]);
            // Reverse the encryption process to get the plaintext character
            plaintext[i] = ((ct_char - 'A' - (kw_char - 'A') + 26) % 26) + 'A';
            j++; // Only increment j for alphabetic characters
        } else {
            // Non-alphabet characters are not changed
            plaintext[i] = ciphertext[i];
        }
        i++;
    }
    plaintext[i] = '\0'; // Null terminate the plaintext string
}

int main() {
    char plaintext[100], keyword[100], ciphertext[100], decryptedtext[100];

    // Input plaintext and keyword
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; // Remove the newline character at the end

    printf("Enter the keyword: ");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0; // Remove the newline character at the end

    // Encrypt the plaintext
    encrypt(plaintext, keyword, ciphertext);
    printf("Encrypted ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    decrypt(ciphertext, keyword, decryptedtext);
    printf("Decrypted plaintext: %s\n", decryptedtext);

    return 0;
}

