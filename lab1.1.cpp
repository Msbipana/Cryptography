//WAP to implement Caeser Cipher

#include <stdio.h>
#include <string.h>

void encrypt(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        
        if (c >= 'A' && c <= 'Z') {
            text[i] = ((c - 'A' + shift) % 26) + 'A'; // Encrypt uppercase letters
        }
        else if (c >= 'a' && c <= 'z') {
            text[i] = ((c - 'a' + shift) % 26) + 'a'; // Encrypt lowercase letters
        }
    }
}

void decrypt(char *text, int shift) {
    for (int i = 0; text[i] != '\0'; i++) {
        char c = text[i];
        
        if (c >= 'A' && c <= 'Z') {
            text[i] = ((c - 'A' - shift + 26) % 26) + 'A'; // Decrypt uppercase letters
        }
        else if (c >= 'a' && c <= 'z') {
            text[i] = ((c - 'a' - shift + 26) % 26) + 'a'; // Decrypt lowercase letters
        }
    }
}

int main() {
    char text[100];
    int shift;
    
    printf("Enter the text to be encrypted: ");
    fgets(text, sizeof(text), stdin);
    
    // Remove the newline character if fgets() adds one
    text[strcspn(text, "\n")] = 0;

    printf("Enter the shift value: ");
    scanf("%d", &shift);
    
    // Encrypt the text
    encrypt(text, shift);
    printf("Encrypted text: %s\n", text);
    
    // Decrypt the text
    decrypt(text, shift);
    printf("Decrypted text: %s\n", text);
    
    return 0;
}

