// Updated RSA key generation code
#include <iostream>
#include <fstream>
#include <cryptopp/integer.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/nbtheory.h>

using namespace CryptoPP;
using namespace std;

Integer GeneratePrime(int bits, AutoSeededRandomPool& rng) {
    Integer prime;
    do {
        prime.Randomize(rng, bits);
    } while (!IsPrime(prime));
    return prime;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <size of p and q in bits>" << endl;
        return 1;
    }

    int bits = atoi(argv[1]);

    AutoSeededRandomPool rng;
    Integer p = GeneratePrime(bits, rng);
    Integer q = GeneratePrime(bits, rng);

    while (p == q) {
        q = GeneratePrime(bits, rng);
    }

    Integer n = p * q;
    Integer phi_n = (p - 1) * (q - 1);

    Integer d;
    do {
        d.Randomize(rng, bits);
    } while (Integer::Gcd(d, phi_n) != Integer::One());

    Integer e = d.InverseMod(phi_n);

    // Store public key (e, n) in 'grp_1_publickey.bin'
    FileSink pubFile("grp_1_publickey.bin", true);
    e.BEREncode(pubFile);
    n.BEREncode(pubFile);
    pubFile.MessageEnd();
    cout << "Public key saved in 'grp_1_publickey.bin'" << endl;

    // Store private key (d, n) in 'grp_1_privatekey.bin'
    FileSink privFile("grp_1_privatekey.bin", true);
    d.BEREncode(privFile);
    n.BEREncode(privFile);
    privFile.MessageEnd();
    cout << "Private key saved in 'grp_1_privatekey.bin'" << endl;

    cout << "RSA keys have been generated by group 1." << endl;

    return 0;
}



//  g++ -o rsa_setup_phase rsa_setup_phase.cpp -lcryptopp

//  ./rsa_setup_phase 1024