#include <iostream>
#include <cstdint> // Include this for uint8_t and uint16_t
#include <bitset>

template <typename T>
std::string printBits(T num) {
    std::bitset<sizeof(T) * 8> binary(num);
    return binary.to_string();
}

template <typename T>
T cutter(T data) {
    T buff = data;
    return buff >>= (sizeof(T) * 4); // Right shift by half of the size in bits
}

// Function to encode data using Hamming (8,4) code
uint16_t hamming_encode_(uint8_t data) {
    uint8_t D1 = (data >> 3) & 1;
    uint8_t D2 = (data >> 2) & 1;
    uint8_t D3 = (data >> 1) & 1;
    uint8_t D4 = data & 1;

    uint8_t P1 = 1 ^ D1 ^ D3 ^ D4;
    uint8_t P2 = 1 ^ D1 ^ D2 ^ D4;
    uint8_t P3 = 1 ^ D1 ^ D2 ^ D3;
    uint8_t P4 = 1 ^ P1 ^ D1 ^ P2 ^ D2 ^ P3 ^ D3 ^ D4;

    return (P1 << 7) | (D1 << 6) | (P2 << 5) | (D2 << 4) | (P3 << 3) | (D3 << 2) | (P4 << 1) | D4;
}

uint16_t hamming_encode(uint8_t data) {
    uint16_t fst_part = hamming_encode_(data);
    uint16_t snd_part = hamming_encode_(cutter(data));

    return fst_part | (snd_part << 8);
}


// Function to decode data using Hamming (8,4) code
uint8_t hamming_decode_(uint16_t encoded_data) {
    uint8_t P1 = (encoded_data >> 7) & 1;
    uint8_t D1 = (encoded_data >> 6) & 1;
    uint8_t P2 = (encoded_data >> 5) & 1;
    uint8_t D2 = (encoded_data >> 4) & 1;
    uint8_t P3 = (encoded_data >> 3) & 1;
    uint8_t D3 = (encoded_data >> 2) & 1;
    uint8_t P4 = (encoded_data >> 1) & 1;
    uint8_t D4 = encoded_data & 1;

    uint8_t A = 1 ^ P1 ^ D1 ^ P3 ^ D3;
    uint8_t B = 1 ^ P1 ^ D1 ^ P2 ^ D2;
    uint8_t C = 1 ^ P2 ^ D2 ^ P3 ^ D3;
    uint8_t D = 1 ^ P1 ^ D1 ^ P2 ^ D2 ^ P3 ^ D3 ^ P4 ^ D4;

    // If the XOR of A, B, C is true and D is true
    if ((A ^ B ^ C) && D) {
        // Return the bitwise shift and OR operation result
        return (D1 << 3) | (D2 << 2) | (D3 << 1) | D4;
    } 
    // If the XOR of A, B, C is true and D is false
    else if ((A ^ B ^ C) && !D) {
        std::cout << "Error detected in P4." << std::endl;
        return (D1 << 3) | (D2 << 2) | (D3 << 1) | D4;
    } 
    // If the XOR of A, B, C is false and D is true
    else if (!(A ^ B ^ C) && D) {
        std::cout << "Double error detected in received data." << std::endl;
        return 0;
    } 
    // If none of the above conditions are met
    else {
        // Check the values of A, B, C and update D1, D2, D3, D4 accordingly
        if (A == 0 && B == 0 && C == 0) {
            D1 ^= 1;
        } 
        if (A == 1 && B == 0 && C == 0) {
            D2 ^= 1;
        } 
        if (A == 0 && B == 1 && C == 0) {
            D3 ^= 1;
        } 
        if (A == 0 && B == 0 && C == 1) {
            D4 ^= 1;
        }
        std::cout << "Single error detected in received data. Corrected it." << std::endl;

        return (D1 << 3) | (D2 << 2) | (D3 << 1) | D4;
    }

}

uint8_t hamming_decode(uint16_t encoded_data) {
    uint8_t fst_part = hamming_decode_(encoded_data);
    uint8_t snd_part = hamming_decode_(cutter(encoded_data));

    return fst_part | (snd_part << 4);
}


int main() {
    // Replace with your data
    uint8_t data = 150; // 10010110 in binary
    // Encode the data
    uint16_t encoded_data = hamming_encode(data);
    // Decode the data
    uint8_t decoded_data = hamming_decode(encoded_data);

    std::cout << "Input data: " << printBits(data) << std::endl;
    std::cout << "Encoded data: " << printBits(encoded_data) << std::endl;
    std::cout << "Decoded data: " << printBits(decoded_data) << std::endl;
    return 0;
}
