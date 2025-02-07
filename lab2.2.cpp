//LAB2

//IMPLEMENT RAIL-FENCE CIPHER
#include <stdio.h>
#include <string.h>

// Function to encrypt the message using Rail Fence Cipher
void encryptMsg(char msg[], int key) {
    int msgLen = strlen(msg);
    int i, j, k = -1, row = 0, col = 0;
    char railMatrix[key][msgLen];

    // Initialize the rail matrix with newline characters
    for (i = 0; i < key; ++i)
        for (j = 0; j < msgLen; ++j)
            railMatrix[i][j] = '\n';

    // Fill the rail matrix
    for (i = 0; i < msgLen; ++i) {
        railMatrix[row][col++] = msg[i];
        if (row == 0 || row == key - 1)
            k = k * (-1); // Reverse direction
        row += k;
    }

    // Print the encrypted message
    printf("\nEncrypted Message: ");
    for (i = 0; i < key; ++i)
        for (j = 0; j < msgLen; ++j)
            if (railMatrix[i][j] != '\n')
                printf("%c", railMatrix[i][j]);
}

// Function to decrypt the message using Rail Fence Cipher
void decryptMsg(char enMsg[], int key) {
    int msgLen = strlen(enMsg);
    int i, j, k = -1, row = 0, col = 0, m = 0;
    char railMatrix[key][msgLen];

    // Initialize the rail matrix with newline characters
    for (i = 0; i < key; ++i)
        for (j = 0; j < msgLen; ++j)
            railMatrix[i][j] = '\n';

    // Mark positions in the rail matrix
    for (i = 0; i < msgLen; ++i) {
        railMatrix[row][col++] = '*';
        if (row == 0 || row == key - 1)
            k = k * (-1); // Reverse direction
        row += k;
    }

    // Fill the marked positions with the encrypted message
    for (i = 0; i < key; ++i)
        for (j = 0; j < msgLen; ++j)
            if (railMatrix[i][j] == '*')
                railMatrix[i][j] = enMsg[m++];

    // Print the decrypted message
    row = col = 0;
    k = -1;
    printf("\nDecrypted Message: ");
    for (i = 0; i < msgLen; ++i) {
        printf("%c", railMatrix[row][col++]);
        if (row == 0 || row == key - 1)
            k = k * (-1); // Reverse direction
        row += k;
    }
}

int main() {
    char msg[100];
    int key;

    // Get input from user
    printf("Enter a message to encrypt: ");
    fgets(msg, sizeof(msg), stdin);
    
    // Remove newline character from input if present
    size_t len = strlen(msg);
    if (len > 0 && msg[len - 1] == '\n') {
        msg[len - 1] = '\0';
    }

    printf("Enter number of rails: ");
    scanf("%d", &key);

    printf("Original Message: %s", msg);
    
    encryptMsg(msg, key);
    
    // Decrypting back to show that it works correctly
    char enMsg[100];
    
    // Constructing encrypted message from output of encryption function
    printf("\nEnter the encrypted message to decrypt: ");
    
    scanf(" %[^\n]", enMsg); // Read until newline

    decryptMsg(enMsg, key);

    return 0;
}

