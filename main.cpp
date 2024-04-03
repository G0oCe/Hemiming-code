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


int main() {
    uint8_t data = 13;
    uint16_t encoded_data = hamming_encode(data);
    
    return 0;
}