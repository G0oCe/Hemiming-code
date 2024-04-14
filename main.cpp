#include <iostream>
#include <cstdint> // Include this for uint8_t and uint16_t

// Function to encode data using Hamming (8,4) code
uint16_t hamming_encode(uint8_t data) {
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

// Function to decode data using Hamming (8,4) code
uint8_t hamming_decode(uint16_t encoded_data) {
    uint8_t P1 = (encoded_data >> 7) & 1;
    uint8_t D1 = (encoded_data >> 6) & 1;
    uint8_t P2 = (encoded_data >> 5) & 1;
    uint8_t D2 = (encoded_data >> 4) & 1;
    uint8_t P3 = (encoded_data >> 3) & 1;
    uint8_t D3 = (encoded_data >> 2) & 1;
    uint8_t P4 = (encoded_data >> 1) & 1;
    uint8_t D4 = encoded_data & 1;

    uint8_t P1_calc = D1 ^ D3 ^ D4;
    uint8_t P2_calc = D1 ^ D2 ^ D4;
    uint8_t P3_calc = D1 ^ D2 ^ D3;
    uint8_t P4_calc = P1_calc ^ D1 ^ D2 ^ D3 ^ D4;

    // If the calculated parity bits match the received parity bits, return the data bits
    if (P1 == P1_calc && P2 == P2_calc && P3 == P3_calc && P4 == P4_calc) {
        return (D1 << 3) | (D2 << 2) | (D3 << 1) | D4;
    } else {
        // If the parity bits do not match, print an error message and return 0
        std::cout << "Error detected in received data." << std::endl;
        return 0;
    }
}

int main() {
    // Replace with your data
    uint8_t data = 13; // 1101 in binary
    // Encode the data
    uint16_t encoded_data = hamming_encode(data);
    // Decode the data
    uint8_t decoded_data = hamming_decode(encoded_data);
    return 0;
}
