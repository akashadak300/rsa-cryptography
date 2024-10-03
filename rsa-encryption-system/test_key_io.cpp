#include <iostream>
#include <cryptopp/integer.h>
#include <cryptopp/files.h>

using namespace CryptoPP;
using namespace std;

int main() {
    Integer e("1234567890123456789012345678901234567890");  // Example public exponent
    Integer n("9876543210987654321098765432109876543210");  // Example modulus

    // Save public key (e, n) to file
    FileSink file("test_publickey.bin", true);
    e.BEREncode(file);
    n.BEREncode(file);
    file.MessageEnd();
    cout << "Public key saved to 'test_publickey.bin'" << endl;

    // Read public key (e, n) from file
    Integer eRead, nRead;
    FileSource fileIn("test_publickey.bin", true);
    eRead.BERDecode(fileIn);
    nRead.BERDecode(fileIn);

    // Print read values
    cout << "Read e: " << eRead << endl;
    cout << "Read n: " << nRead << endl;

    return 0;
}
