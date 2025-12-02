#ifndef PQC_HANDLER_H
#define PQC_HANDLER_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <oqs/oqs.h>

class PQCHandler {
public:
    static void Initialize() {
        OQS_init();
    }

    static void Cleanup() {
        OQS_destroy();
    }

    // Step 1: Master generates Key Pair (Public/Private)
    static bool GenerateKyberKeyPair(std::vector<uint8_t>& publicKey, std::vector<uint8_t>& privateKey) {
        OQS_KEM* kem = OQS_KEM_new(OQS_KEM_alg_kyber_768);
        if (kem == NULL) return false;

        publicKey.resize(kem->length_public_key);
        privateKey.resize(kem->length_secret_key);

        OQS_STATUS status = OQS_KEM_keypair(kem, publicKey.data(), privateKey.data());
        
        OQS_KEM_free(kem);
        return status == OQS_SUCCESS;
    }

    // Step 2: Outstation Encapsulates (Generates Shared Secret + Ciphertext)
    static bool EncapsulateSecret(const std::vector<uint8_t>& publicKey, std::vector<uint8_t>& ciphertext, std::vector<uint8_t>& sharedSecret) {
        OQS_KEM* kem = OQS_KEM_new(OQS_KEM_alg_kyber_768);
        if (kem == NULL) return false;

        ciphertext.resize(kem->length_ciphertext);
        sharedSecret.resize(kem->length_shared_secret);

        OQS_STATUS status = OQS_KEM_encaps(kem, ciphertext.data(), sharedSecret.data(), publicKey.data());

        OQS_KEM_free(kem);
        return status == OQS_SUCCESS;
    }

    // Step 3: Master Decapsulates (Recovers Shared Secret using Private Key)
    static bool DecapsulateSecret(const std::vector<uint8_t>& ciphertext, const std::vector<uint8_t>& privateKey, std::vector<uint8_t>& sharedSecret) {
        OQS_KEM* kem = OQS_KEM_new(OQS_KEM_alg_kyber_768);
        if (kem == NULL) return false;

        sharedSecret.resize(kem->length_shared_secret);

        OQS_STATUS status = OQS_KEM_decaps(kem, sharedSecret.data(), ciphertext.data(), privateKey.data());

        OQS_KEM_free(kem);
        return status == OQS_SUCCESS;
    }

    static void PrintHex(const std::string& label, const std::vector<uint8_t>& data) {
        std::cout << "[PQC] " << label << " (" << data.size() << " bytes): ";
        for (size_t i = 0; i < 16 && i < data.size(); ++i) { // Print first 16 bytes only
            std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)data[i];
        }
        std::cout << "..." << std::dec << std::endl;
    }
};

#endif