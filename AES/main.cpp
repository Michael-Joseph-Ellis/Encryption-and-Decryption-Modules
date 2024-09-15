#include "aes.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

#define ENCRYPTED_FILE "encrypted_output.bin"
#define DECRYPTED_FILE "decrypted_output.txt"
#define INPUT_FILE "input.txt"

/**
 * @brief Helper function to print data in hexadecimal format.
 * 
 * @param data A pointer to the data to be printed.
 * @param len The length of the data in bytes.
 */
void print_hex(const unsigned char *data, int len) {
    for (int i = 0; i < len; i++) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)data[i];
    }
    std::cout << std::dec << std::endl; // Reset to decimal formatting
}

/**
 * @brief Helper function to check if a file exists.
 * 
 * @param filename The name of the file to check.
 * @return true If the file exists.
 * @return false If the file does not exist.
 */
bool file_exists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

/**
 * @brief Helper function to create a file with some sample text.
 * 
 * @param filename The name of the file to create.
 * @param content The content to write to the file.
 */
void create_file_with_text(const std::string& filename, const std::string& content) {
    std::ofstream outfile(filename);
    outfile << content;
    outfile.close();
}

int main() {
    std::string plaintext_content = "This is a secret message. It will be encrypted and decrypted.";

    // Step 1: Check if the input file exists; if not, create it.
    if (!file_exists(INPUT_FILE)) {
        std::cout << "File not found, creating new file: " << INPUT_FILE << std::endl;
        create_file_with_text(INPUT_FILE, plaintext_content);
    }

    // Step 2: Read plaintext from file
    std::ifstream infile(INPUT_FILE);
    std::string plaintext((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());
    infile.close();
    
    std::cout << "Read from file: " << plaintext << std::endl;

    // Generate a random AES key and IV
    unsigned char key[AES_KEYLEN];
    unsigned char iv[MY_AES_BLOCK_SIZE];
    generate_aes_key(key);  // Generate random AES key
    generate_aes_iv(iv);    // Generate random AES IV

    // Encrypt the plaintext from the file
    unsigned char ciphertext[256];  // Buffer to store ciphertext
    int ciphertext_len = aes_encrypt(reinterpret_cast<const unsigned char*>(plaintext.c_str()), plaintext.size(), key, iv, ciphertext);

    // Write encrypted data to encrypted_output.bin file
    std::ofstream encrypted_file(ENCRYPTED_FILE, std::ios::binary);
    encrypted_file.write(reinterpret_cast<const char*>(ciphertext), ciphertext_len);
    encrypted_file.close();
    
    std::cout << "Encrypted data written to " << ENCRYPTED_FILE << std::endl;

    // Decrypt the ciphertext
    unsigned char decryptedtext[256];  // Buffer to store decrypted text
    int decryptedtext_len = aes_decrypt(ciphertext, ciphertext_len, key, iv, decryptedtext);

    // Add null terminator to the decrypted text for safe printing
    decryptedtext[decryptedtext_len] = '\0';

    // Write decrypted text to decrypted_output.txt file
    std::ofstream decrypted_file(DECRYPTED_FILE);
    decrypted_file.write(reinterpret_cast<const char*>(decryptedtext), decryptedtext_len);
    decrypted_file.close();

    std::cout << "Decrypted data written to " << DECRYPTED_FILE << std::endl;

    return 0;
}

// NOTE:
// This code demonstrates a simple encryption and decryption process using AES-256-CBC mode.
// This is only a basic implementation and should not be used for production-level security. 
// To properly use this, you need to have OpenSSL installed on your system.
// You can compile this code using the following command:
// g++ main.cpp aes.cpp -o aes_example -lssl -lcrypto
// This will generate an executable named aes_example that you can run to see the encryption and decryption process.
// You can also modify the input.txt file to test with different plaintext messages.
// You can alternatively modify the main function to read plaintext from user input or any other source, or to directly encrypt/decrypt strings without file I/O. 