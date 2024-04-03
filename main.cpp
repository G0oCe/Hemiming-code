#include <iostream>
#include <cstdint>

uint16_t hamming_encode(uint8_t data) {
    uint8_t D1 = (data >> 3) & 1;
    uint8_t D2 = (data >> 2) & 1;
    uint8_t D3 = (data >> 1) & 1;
    uint8_t D4 = data & 1;

    uint8_t P1 = D1 ^ D3 ^ D4;
    uint8_t P2 = D1 ^ D2 ^ D4;
    uint8_t P3 = D1 ^ D2 ^ D3;
    uint8_t P4 = P1 ^ D1 ^ D2 ^ D3 ^ D4;

    return (P1 << 7) | (D1 << 6) | (P2 << 5) | (D2 << 4) | (P3 << 3) | (D3 << 2) | (P4 << 1) | D4;
}

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

    if (P1 == P1_calc && P2 == P2_calc && P3 == P3_calc && P4 == P4_calc) {
        return (D1 << 3) | (D2 << 2) | (D3 << 1) | D4;
    } else {
        std::cout << "Error detected in received data." << std::endl;
        return 0;
    }
}

int main() {
    uint8_t data = 13;
    uint16_t encoded_data = hamming_encode(data);
    uint8_t decoded_data = hamming_decode(encoded_data);
    
    return 0;
}