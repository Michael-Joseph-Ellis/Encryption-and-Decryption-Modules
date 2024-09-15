#include "aes.h"
#include <openssl/rand.h>

// Function to generate a random AES-256 key (32 bytes)
void generate_aes_key(unsigned char *key) {
    RAND_bytes(key, AES_KEYLEN);  // Generate 256 bits of random data for the key
}

// Function to generate a random Initialization Vector (16 bytes)
void generate_aes_iv(unsigned char *iv) {
    RAND_bytes(iv, MY_AES_BLOCK_SIZE);  // Generate 128 bits of random data for the IV
}

// Function to encrypt plaintext using AES-256-CBC
int aes_encrypt(const unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len;
    int ciphertext_len;

    // Initialize encryption operation
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    // Perform encryption
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len);
    ciphertext_len = len;

    // Finalize encryption (padding is handled here)
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

// Function to decrypt ciphertext using AES-256-CBC
int aes_decrypt(const unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int len;
    int plaintext_len;

    // Initialize decryption operation
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv);

    // Perform decryption
    EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len);
    plaintext_len = len;

    // Finalize decryption (handling padding here)
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    plaintext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}
