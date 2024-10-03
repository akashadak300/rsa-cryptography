# RSA Cryptography System - Encryption & Digital Signature

This repository contains two projects as part of **Cyber Security Lab Assignment 7**:
1. **RSA Encryption System** 
2. **RSA Digital Signature System** 

## 1. RSA Encryption System 

### Objective
Implement the **RSA encryption system** to securely encrypt and decrypt messages between two parties.

### Phases of Implementation
#### 1. Setup Phase
- **Generate two large prime numbers `p` and `q`**, where `p ≠ q`.
- Compute:
  - `n = p * q`
  - `Φ(n) = (p - 1) * (q - 1)`
- Generate the keys:
  - **Private key (`d`)** as a random integer `d ∈ Z*Φ(n)` and coprime with `Φ(n)`.
  - **Public key (`e`)** such that `e ≡ d⁻¹ mod Φ(n)`
- Store:
  - Public key `(e, n)` in the binary file `publickey.bin`.
  - Private key `(d, n)` in `privatekey.bin`.
  
**Note**: Discard the values of `p`, `q`, and `Φ(n)` after key generation.

#### 2. Encryption Phase
- **Objective**: Encrypt the plaintext using the public key `(e, n)`.
- Steps:
  1. Input the plaintext file path.
  2. Compute the ciphertext `C ≡ M^e mod n`.
  3. Save the ciphertext in `ciphertext.bin`.

#### 3. Decryption Phase
- **Objective**: Decrypt the ciphertext using the private key `(d, n)` to retrieve the original message.
- Steps:
  1. Input the ciphertext from `ciphertext.bin`.
  2. Compute the plaintext `M ≡ C^d mod n`.
  3. Save the decrypted plaintext in a file.

### Workflow Summary:
1. **Setup**: Generate keys and save them.
2. **Encryption**: Encrypt the message using the public key.
3. **Decryption**: Decrypt the ciphertext using the private key.

---

## 2. RSA Digital Signature System 

### Objective
Implement the **RSA Digital Signature System** to verify the authenticity and integrity of a message.

### Phases of Implementation
#### 1. Setup Phase
- **Generate two large prime numbers `p` and `q`**, where `p ≠ q`.
- Compute:
  - `n = p * q`
  - `Φ(n) = (p - 1) * (q - 1)`
- Generate the keys:
  - **Private key (`d`)** as a random integer `d ∈ Z*Φ(n)` and coprime with `Φ(n)`.
  - **Public key (`e`)** such that `e ≡ d⁻¹ mod Φ(n)`
- Store:
  - Public key `(e, n)` in `publickey.bin`.
  - Private key `(d, n)` in `privatekey.bin`.
  
**Note**: Discard the values of `p`, `q`, and `Φ(n)` after key generation.

#### 2. Signature Phase
- **Objective**: Sign a hashed version of the plaintext.
- Steps:
  1. Compute the **hash of the message** using `md5sum` and store it in `msgHash1.bin`.
  2. Sign the hashed message `H(m)` using the private key:
     - `S ≡ (H(m))^d mod n`
  3. Store the digital signature `S` in `signature.bin`.

#### 3. Verification Phase
- **Objective**: Verify the digital signature using the public key.
- Steps:
  1. Verify the signature by computing:
     - `D' ≡ (S)^e mod n`
  2. Compare the computed hash `D'` with the original hash stored in `msgHash1.bin`. If `D = D'`, the signature is valid.
  3. Store the computed hash `D'` in `msgHash2.bin`.

### Workflow Summary:
1. **Setup**: Generate keys and save them.
2. **Signature**: Generate a digital signature for the hashed message.
3. **Verification**: Verify the signature using the public key.

---

## Tools & Technologies Used

- **Crypto++**: Using `Integer`, `PrimeAndGenerator`, and `AutoSeededRandomPool` classes for key generation and cryptographic computations.
- **Programming Language**: C++
- **Algorithms**:
  - RSA for encryption/decryption.
  - RSA for digital signatures.
  - `md5sum` for hashing during the signature phase.

## Files Structure
- `publickey.bin`: Stores the public key `(e, n)`.
- `privatekey.bin`: Stores the private key `(d, n)`.
- `ciphertext.bin`: Stores the encrypted message (ciphertext).
- `msgHash1.bin`: Stores the hash of the plaintext.
- `msgHash2.bin`: Stores the hash used during signature verification.
- `signature.bin`: Stores the generated digital signature.

## How to Run

### For RSA Encryption System:
1. **Setup Phase**: Generate keys:
   ```bash
   ./rsa_setup
   ```
2. **Encryption Phase**: Encrypt a plaintext message:
   ```bash
   ./rsa_encrypt plaintext.txt
   ```
3. **Decryption Phase**: Decrypt the ciphertext:
   ```bash
   ./rsa_decrypt ciphertext.bin
   ```

### For RSA Digital Signature System:
1. **Setup Phase**: Generate keys:
   ```bash
   ./rsa_setup
   ```
2. **Signature Phase**: Sign a message:
   ```bash
   ./rsa_sign message.txt
   ```
3. **Verification Phase**: Verify the digital signature:
   ```bash
   ./rsa_verify signature.bin
   ```

## License
This project is developed for educational purposes as part of the Cyber Security Lab assignments.

