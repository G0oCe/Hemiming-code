#include "main.cpp"
#include <gtest/gtest.h>


TEST(Encoding_Test, normal_case) {
    ASSERT_EQ(59624, hamming_encode(136));
}


TEST(Decoding_Test, AllCorret) {
    ASSERT_EQ(136, hamming_decode(59624));
}

TEST(Decoding_Test, errorInP4) {
    EXPECT_EQ(232, hamming_decode(24298));
} 

TEST(Decoding_Test, doubleError) {
    EXPECT_EQ(-1, int8_t(hamming_decode(58596))); // hamming decode return uint and -1 is signed, thats why i used it here
} 

TEST(Decoding_Test, singleError) {
    
    // A is false
    EXPECT_EQ(238, hamming_decode(59110));

    // B is false
    EXPECT_EQ(238, hamming_decode(62194));

    // C is false
    EXPECT_EQ(153, hamming_decode(57568));

    // C and B is false
    EXPECT_EQ(136, hamming_decode(63736));
    
    // A and C is false
    EXPECT_EQ(136, hamming_decode(60652));

    // A and B is false
    EXPECT_EQ(136, hamming_decode(59881));
    
    // All is false
    EXPECT_EQ(136, hamming_decode(43176));
} 



int main() {
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}
