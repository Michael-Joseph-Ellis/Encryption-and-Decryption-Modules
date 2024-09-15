# AES Encryption/Decryption Module
This project provides an AES (Advanced Encryption Standard) encryption and decryption module implemented in C++ using OpenSSL. The module includes two files: `aes.cpp` and `aes.h`, which encapsulate the AES-256-CBC encryption and decryption functionalities. You can integrate these files into larger projects that require AES encryption/decryption capabilities.

## Features 
- **AES Encryption/Decryption**: Supports AES-256 in CBC mode for secure data encryption and decryption.
- **Customizable**: Allows for the generation of secure AES keys and Initialization Vectors (IVs).
- **Modular Design**: aes.cpp and aes.h are designed to be used in larger C++ projects with minimal changes.
- **Flexible Usage**: Can be easily extended or adapted to handle other encryption modes or integrated into security-based projects.

## Using the Module in Other Projects

### Integration
To use this AES module in other projects: 

1. Ensure to `#include "aes.h` in your C++ files where this module's encryption and decryption methods are required.
2. **(Important)** Compile with OpenSSL: Ensure you link against OpenSSL by compiling your project with -lssl and -lcrypto flags. 

### Function Overview 
- `void generate_aes_key(unsigned char *key)`: Generates a random 256-bit AES key.
- `void generate_aes_iv(unsigned char *iv)`: Generates a random 128-bit Initialization Vector (IV).
- `int aes_encrypt(const unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext)`: Encrypts the plaintext using AES-256-CBC.
- `int aes_decrypt(const unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *iv, unsigned char *plaintext)`: Decrypts the ciphertext using AES-256-CBC.

## Example of Usage (main.cpp)

The provided `main.cpp` file is a demonstration of how to use the `aes.cpp` and `aes.h` modules for encrypting and decrypting plaintext file. It reads plaintext from a file, encrypts it using AES-256-CBC, writes the ecrypted data to a binary file, and then decrypts it back into readable format. The example also showcases key generation, IV generation, and working with OpenSSL's EVP API. 

## Steps to Compile and Run the Example 

```bash
g++ main.cpp aes.cpp -o aes_example -lssl -lcrypto
```

This will compile the `main.cpp`, `aes.cpp`, and `aes.h` into an executable named `aes_example`. When executed, the program will:
1. Read plaintext from a file (or generate one if it doesn't exist).
2. Encrypt the plaintext using AES-256-CBC.
3. Write the encrypted data to `encrypted_output.bin`.
4. Decrypt the encrypted data and save it to `decrypted_output.text`.

## Modular Usage 

Working on a larger project, you omit the `main.cpp` file and directly incorperate `aes.cpp` and `aes.h` into your codebase.
- Call `aes_encrypt` and `aes_decrypt` in your project wherever encryption and decryption are requried. 
- Generate keys and IVs using the provided utility functions or customize them for your security model. 

## License 

This project is licensed under the MIT license. 