
#include <iostream>
#include <fstream>
#include <cryptopp/integer.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/md5.h>
#include <cryptopp/hex.h>
#include <cryptopp/cryptlib.h>

using namespace CryptoPP;
using namespace std;

void HashMessage(const string& filename, string& hash) {
    MD5 hashFunction;
    FileSource file(filename.c_str(), true /* pump all */, new HashFilter(hashFunction, new HexEncoder(new StringSink(hash))));
}

Integer SignHash(const Integer& hash, const Integer& d, const Integer& n) {
    // Use a_exp_b_mod_c for modular exponentiation
    return a_exp_b_mod_c(hash, d, n);
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Usage: " << argv[0] << " <private key file> <message file> <hash output file> <signature output file>" << endl;
        return 1;
    }

    string privateKeyFile = argv[1];
    string messageFile = argv[2];
    string hashOutputFile = argv[3];
    string signatureOutputFile = argv[4];

    // Load private key (d, n)
    Integer d, n;
    FileSource privFile(privateKeyFile.c_str(), true);
    d.BERDecode(privFile);
    n.BERDecode(privFile);

    // Load message and compute its hash
    string hash;
    HashMessage(messageFile, hash);

    // Convert hash to integer
    Integer messageHash(hash.c_str());

    // Sign the hash
    Integer signature = SignHash(messageHash, d, n);

    // Store the hash in the specified file
    FileSink hashFile(hashOutputFile.c_str(), true);
    messageHash.BEREncode(hashFile);
    hashFile.MessageEnd();
    cout << "Message hash saved in '" << hashOutputFile << "'" << endl;

    // Store the signature in the specified file
    FileSink sigFile(signatureOutputFile.c_str(), true);
    signature.BEREncode(sigFile);
    sigFile.MessageEnd();
    cout << "Signature saved in '" << signatureOutputFile << "'" << endl;

    cout << "Message signed successfully." << endl;

    return 0;
}
