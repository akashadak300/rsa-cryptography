#include <iostream>
#include <fstream>
#include <cryptopp/integer.h>
#include <cryptopp/files.h>
#include <cryptopp/nbtheory.h>

// Function to read a file into a string
std::string ReadFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        exit(1);
    }
    return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}

// Function to decrypt a message using RSA
CryptoPP::Integer Decrypt(const CryptoPP::Integer& cipherText, const CryptoPP::Integer& d, const CryptoPP::Integer& n) {
    return CryptoPP::ModularExponentiation(cipherText, d, n);  // Corrected function
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <cipher text file> <private key file> <plain text file>" << std::endl;
        return 1;
    }

    std::string cipherTextFile = argv[1];
    std::string privateKeyFile = argv[2];
    std::string plainTextFile = argv[3];

    // Read the ciphertext from file
    std::string cipherTextStr = ReadFile(cipherTextFile);
    CryptoPP::Integer cipherText(reinterpret_cast<const CryptoPP::byte*>(cipherTextStr.data()), cipherTextStr.size());

    // Read private key (d, n) from file
    CryptoPP::Integer d, n;
    CryptoPP::FileSource privFile(privateKeyFile.c_str(), true);
    try {
        d.BERDecode(privFile);
        n.BERDecode(privFile);
    } catch (const CryptoPP::BERDecodeErr& err) {
        std::cerr << "BER decode error: " << err.what() << std::endl;
        return 1;
    }

    // Decrypt the message
    CryptoPP::Integer plainText = Decrypt(cipherText, d, n);

    // Convert the decrypted integer back to string
    std::string decryptedMessage;
    decryptedMessage.resize(plainText.MinEncodedSize());
    plainText.Encode(reinterpret_cast<CryptoPP::byte*>(&decryptedMessage[0]), decryptedMessage.size());

    // Save the plaintext to file
    std::ofstream plainTextFileStream(plainTextFile, std::ios::binary);
    if (!plainTextFileStream) {
        std::cerr << "Unable to open file: " << plainTextFile << std::endl;
        return 1;
    }
    plainTextFileStream.write(decryptedMessage.data(), decryptedMessage.size());
    plainTextFileStream.close();

    std::cout << "Plaintext saved in '" << plainTextFile << "'" << std::endl;

    return 0;
}
// g++ -o rsa_decryption_phase rsa_decryption_phase.cpp -lcryptopp
// ./rsa_decryption_phase cipher_text.bin private_key.bin plain_text.txt
