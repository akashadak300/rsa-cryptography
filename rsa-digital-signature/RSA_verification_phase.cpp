#include <iostream>
#include <fstream>
#include <cryptopp/integer.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/hex.h>

using namespace CryptoPP;
using namespace std;

// Function to decrypt the signature using public key (e, n)
Integer Decrypt(const Integer& signature, const Integer& e, const Integer& n) {
    return a_exp_b_mod_c(signature, e, n);
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cerr << "Usage: " << argv[0] << " <public_key_file> <signature_file> <msgHash1_file> <msg_file>" << endl;
        return 1;
    }

    // Input files
    const char* publicKeyFile = argv[1];
    const char* signatureFile = argv[2];
    const char* msgHash1File = argv[3];
    const char* messageFile = argv[4];

    // Variables for public key (e, n), signature (S), and original hash (D)
    Integer e, n, S, D, D_prime;

    // Load public key (e, n) from the file
    FileSource pubFile(publicKeyFile, true /* pump all */);
    e.BERDecode(pubFile);
    n.BERDecode(pubFile);

    // Load the signature (S) from the file
    FileSource sigFile(signatureFile, true /* pump all */);
    S.BERDecode(sigFile);

    // Load the original message hash (D) from the file 'msgHash1.bin'
    FileSource msgHashFile(msgHash1File, true /* pump all */);
    D.BERDecode(msgHashFile);

    // Decrypt the signature to get D' using the public key (e, n)
    D_prime = Decrypt(S, e, n);

    // Store D' in 'grp_1_msgHash2.bin'
    FileSink msgHash2File("grp_1_msgHash2.bin", true);
    D_prime.BEREncode(msgHash2File);
    msgHash2File.MessageEnd();
    cout << "D' saved in 'grp_1_msgHash2.bin'" << endl;

    // Compare D and D'
    if (D == D_prime) {
        cout << "Signature is valid: D = D'" << endl;
    } else {
        cout << "Signature is invalid: D != D'" << endl;
    }

    return 0;
}
