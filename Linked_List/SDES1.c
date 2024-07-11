#include <stdio.h>
#include <string.h>

// Initial and final permutations (IP and IP^-1)
int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};
int IP_inv[] = {4, 1, 3, 5, 7, 2, 8, 6};

// Expansion permutation (E)
int E[] = {4, 1, 2, 3, 2, 3, 4, 1};

// Permutation P
int P[] = {2, 4, 3, 1};

// S-boxes (S0 and S1)
int S0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

int S1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

// Function prototypes
void generateSubkeys(char[], char[], char[], char[]);
void initialPermutation(char[]);
void inverseInitialPermutation(char[]);
void expansion(char[], char[]);
void permutationP(char[]);
void swap(char[], char[]);
void SDES(char[], char[], int);
void f_function(char[], char[], char[]);

// Key permutation 10 -> 8
int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
int P8[] = {6, 3, 7, 4, 8, 5, 10, 9};

char K1[9];  // Subkey K1
char K2[9];  // Subkey K2

// Circular left shifts
void shift_left(char[], int);

// Main function
int main() {
    char plaintext[9] = "10100101"; // 8-bit plaintext
    char key[11] = "0010010111";   // 10-bit key

    char ciphertext[9];

    generateSubkeys(key, K1, K2, P10);

    SDES(plaintext, ciphertext, 1);
    printf("Encrypted: %s\n", ciphertext);

    SDES(ciphertext, plaintext, -1);
    printf("Decrypted: %s\n", plaintext);

    return 0;
}

// Generate subkeys K1 and K2
void generateSubkeys(char key[], char K1[], char K2[], char P10[]) {
    char temp_key[11];
    for (int i = 0; i < 10; i++) {
        temp_key[i] = key[P10[i] - 1];
    }
    temp_key[10] = '\0';

    shift_left(temp_key, 1);
    for (int i = 0; i < 8; i++) {
        K1[i] = temp_key[P8[i] - 1];
    }
    K1[8] = '\0';

    shift_left(temp_key, 2);
    for (int i = 0; i < 8; i++) {
        K2[i] = temp_key[P8[i] - 1];
    }
    K2[8] = '\0';
}

// Circular left shift operation
void shift_left(char key[], int shifts) {
    char temp[2];
    for (int i = 0; i < shifts; i++) {
        temp[0] = key[0];
        temp[1] = key[5];

        for (int j = 0; j < 9; j++) {
            key[j] = key[j + 1];
        }

        key[4] = temp[0];
        key[9] = temp[1];
    }
}

// Initial permutation (IP)
void initialPermutation(char plaintext[]) {
    char temp[9];
    for (int i = 0; i < 8; i++) {
        temp[i] = plaintext[IP[i] - 1];
    }
    temp[8] = '\0';
    strcpy(plaintext, temp);
}

// Inverse initial permutation (IP^-1)
void inverseInitialPermutation(char ciphertext[]) {
    char temp[9];
    for (int i = 0; i < 8; i++) {
        temp[i] = ciphertext[IP_inv[i] - 1];
    }
    temp[8] = '\0';
    strcpy(ciphertext, temp);
}

// Expansion permutation (E)
void expansion(char right_half[], char expanded[]) {
    char temp[9];
    for (int i = 0; i < 8; i++) {
        temp[i] = right_half[E[i] - 1];
    }
    temp[8] = '\0';
    strcpy(expanded, temp);
}

// Permutation P
void permutationP(char input[]) {
    char temp[5];
    for (int i = 0; i < 4; i++) {
        temp[i] = input[P[i] - 1];
    }
    temp[4] = '\0';
    strcpy(input, temp);
}

// Swap function
void swap(char L[], char R[]) {
    char temp[9];
    strcpy(temp, L);
    strcpy(L, R);
    strcpy(R, temp);
}

// SDES encryption/decryption
void SDES(char plaintext[], char ciphertext[], int encrypt) {
    char L[5], R[5], temp[9], expanded[9];

    initialPermutation(plaintext);

    // Split into L0 and R0
    for (int i = 0; i < 4; i++) {
        L[i] = plaintext[i];
        R[i] = plaintext[i + 4];
    }
    L[4] = R[4] = '\0';

    // Select subkeys based on encryption or decryption
    char *subkey1, *subkey2;
    if (encrypt == 1) {
        subkey1 = K1;
        subkey2 = K2;
    } else {
        subkey1 = K2;
        subkey2 = K1;
    }

    // Round 1
    expansion(R, expanded);
    f_function(expanded, subkey1, temp);
    for (int i = 0; i < 4; i++) {
        temp[i] = temp[i] == plaintext[i] ? '0' : '1';
    }
    permutationP(temp);
    for (int i = 0; i < 4; i++) {
        temp[i] = temp[i] == plaintext[i] ? '0' : '1';
    }
    swap(L, temp);
    inverseInitialPermutation(plaintext);

    // Round 2
    expansion(L, expanded);
    f_function(expanded, subkey2, temp);
    for (int i = 0; i < 4; i++) {
        temp[i] = temp[i] == plaintext[i] ? '0' : '1';
    }
    permutationP(temp);
    for (int i = 0; i < 4; i++) {
        temp[i] = temp[i] == plaintext[i] ? '0' : '1';
    }
    swap(L, temp);
    inverseInitialPermutation(plaintext);

    // Combine L16R16
    strcpy(ciphertext, L);
    strcat(ciphertext, R);
}

// F function
void f_function(char expanded[], char key[], char result[]) {
    char L[3], R[3], temp[5];

    for (int i = 0; i < 4; i++) {
        L[i] = expanded[i];
        R[i] = expanded[i + 4];
    }
    L[4] = R[4] = '\0';

    // Convert L and R to decimal
    int row1 = (L[0] - '0') * 2 + (L[3] - '0');
    int col1 = (L[1] - '0') * 2 + (L[2] - '0');
    int row2 = (R[0] - '0') * 2 + (R[3] - '0');
    int col2 = (R[1] - '0') * 2 + (R[2] - '0');

    // Apply S-boxes
    int val1 = S0[row1][col1];
    int val2 = S1[row2][col2];

    // Convert values to binary
    sprintf(temp, "%02d", val1);
    result[0] = temp[0];
    result[1] = temp[1];

    sprintf(temp, "%02d", val2);
    result[2] = temp[0];
    result[3] = temp[1];
    result[4] = '\0';

    // Permute using P4
    permutationP(result);
}
