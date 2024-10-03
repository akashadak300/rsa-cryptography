#include <iostream>
#include <fstream>
#include <cryptopp/integer.h>
#include <cryptopp/files.h>
#include <cryptopp/nbtheory.h>
#include <cryptopp/osrng.h>

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <plain text file> <public key file> <cipher text file>" << std::endl;
        return 1;
    }

    // File names from command-line arguments
    std::string plainTextFile = argv[1];
    std::string publicKeyFile = argv[2];
    std::string cipherTextFile = argv[3];

    // Function to read content from a file
    auto ReadFile = [](const std::string& filename) -> std::string {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Unable to open file: " << filename << std::endl;
            exit(1);
        }
        return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    };

    // Read plaintext from the input file
    std::string plainText = ReadFile(plainTextFile);
    CryptoPP::Integer message(reinterpret_cast<const CryptoPP::byte*>(plainText.data()), plainText.size());

    // Variables for public key components
    CryptoPP::Integer e, n;

    // Read public key from file
    CryptoPP::FileSource pubFile(publicKeyFile.c_str(), true);
    try {
        e.BERDecode(pubFile);
        n.BERDecode(pubFile);
    } catch (const CryptoPP::BERDecodeErr& err) {
        std::cerr << "BER decode error: " << err.what() << std::endl;
        return 1;
    }

    // Encrypt the message using RSA (m^e mod n)
    auto Encrypt = [](const CryptoPP::Integer& message, const CryptoPP::Integer& e, const CryptoPP::Integer& n) -> CryptoPP::Integer {
        return CryptoPP::ModularExponentiation(message, e, n);
    };

    CryptoPP::Integer cipherText = Encrypt(message, e, n);

    // Save encrypted ciphertext to file
    CryptoPP::FileSink cipherFile(cipherTextFile.c_str(), true);
    cipherText.Encode(cipherFile, cipherText.MinEncodedSize());
    cipherFile.MessageEnd();

    // Success message
    std::cout << "Ciphertext saved in '" << cipherTextFile << "'" << std::endl;

    return 0;
}
// g++ -o rsa_encryption_phase rsa_encryption_phase.cpp -lcryptopp
// ./rsa_encryption_phase plain_text.txt public_key.bin cipher_text.bin
