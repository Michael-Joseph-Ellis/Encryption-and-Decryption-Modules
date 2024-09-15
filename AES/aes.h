#ifndef AES_H
#define AES_H

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <cstring>

// Constants for AES
const int AES_KEYLEN = 32;          // 256-bit key length
const int MY_AES_BLOCK_SIZE = 16;   // Custom block size for AES (avoiding conflict with OpenSSL)

/**
 * @brief Generates a random AES-256 key.
 *
 * This function generates a 256-bit random key suitable for AES-256 encryption.
 *
 * @param key A pointer to a buffer where the generated key will be stored.
 *
 * @pre `key` must point to a valid buffer that can hold 32 bytes (256 bits).
 * 
 * @post The `key` buffer will contain 32 random bytes.
 *
 * @example
 * unsigned char key[AES_KEYLEN];
 * generate_aes_key(key);
 */
void generate_aes_key(unsigned char *key);

/**
 * @brief Generates a random Initialization Vector (IV) for AES.
 *
 * This function generates a random 16-byte Initialization Vector (IV) used in AES encryption.
 *
 * @param iv A pointer to a buffer where the generated IV will be stored.
 *
 * @pre `iv` must point to a valid buffer that can hold 16 bytes (AES block size).
 * 
 * @post The `iv` buffer will contain 16 random bytes.
 *
 * @example
 * unsigned char iv[MY_AES_BLOCK_SIZE];
 * generate_aes_iv(iv);
 */
void generate_aes_iv(unsigned char *iv);

/**
 * @brief Encrypts plaintext using AES-256-CBC encryption.
 * 
 * This function encrypts the provided plaintext using AES-256-CBC encryption with the
 * provided key and Initialization Vector (IV).
 * 
 * @param plaintext A pointer to the plaintext data to be encrypted.
 * @param plaintext_len The length of the plaintext data in bytes.
 * @param key A pointer to the AES key to be used for encryption. Must be 32 bytes long (AES-256).
 * @param iv A pointer to the Initialization Vector (IV) to be used. Must be 16 bytes long (AES block size).
 * @param ciphertext A pointer to a buffer where the ciphertext will be stored.
 *
 * @pre 
 * - `plaintext` must point to valid data that needs encryption.
 * - `key` must point to a valid 32-byte AES key.
 * - `iv` must point to a valid 16-byte IV buffer.
 * - `ciphertext` must point to a valid buffer that can store at least `plaintext_len + AES_BLOCK_SIZE` bytes.
 * 
 * @post 
 * - The `ciphertext` buffer will contain the encrypted data.
 *
 * @return int The length of the ciphertext in bytes.
 *
 * @example
 * unsigned char key[AES_KEYLEN];
 * unsigned char iv[MY_AES_BLOCK_SIZE];
 * unsigned char ciphertext[128];
 * 
 * generate_aes_key(key);
 * generate_aes_iv(iv);
 * 
 * const char* plaintext = "This is a secret message";
 * int ciphertext_len = aes_encrypt(reinterpret_cast<const unsigned char*>(plaintext), strlen(plaintext), key, iv, ciphertext);
 */
int aes_encrypt(const unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext);

/**
 * @brief Decrypts ciphertext using AES-256-CBC encryption.
 *
 * This function decrypts the provided ciphertext using AES-256-CBC encryption with the
 * provided key and Initialization Vector (IV).
 *
 * @param ciphertext A pointer to the ciphertext data to be decrypted.
 * @param ciphertext_len The length of the ciphertext data in bytes.
 * @param key A pointer to the AES key to be used for decryption. Must be 32 bytes long (AES-256).
 * @param iv A pointer to the Initialization Vector (IV) to be used. Must be 16 bytes long (AES block size).
 * @param plaintext A pointer to a buffer where the decrypted plaintext will be stored.
 *
 * @pre 
 * - `ciphertext` must point to valid data that needs decryption.
 * - `key` must point to a valid 32-byte AES key.
 * - `iv` must point to a valid 16-byte IV buffer.
 * - `plaintext` must point to a valid buffer that can store at least `ciphertext_len` bytes.
 * 
 * @post 
 * - The `plaintext` buffer will contain the decrypted data.
 *
 * @return int The length of the decrypted plaintext in bytes.
 *
 * @example
 * unsigned char key[AES_KEYLEN];
 * unsigned char iv[MY_AES_BLOCK_SIZE];
 * unsigned char decryptedtext[128];
 * 
 * int decryptedtext_len = aes_decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);
 */
int aes_decrypt(const unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext);

#endif // AES_H
