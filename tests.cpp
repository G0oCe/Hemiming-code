#include "main.cpp"
#include <gtest/gtest.h>


TEST(Encoding_Test, normal_case) {
    ASSERT_EQ(16448, hamming_encode(136));
}


TEST(Decoding_Test, AllCorret) {
    ASSERT_EQ(136, hamming_decode(16448));
}

TEST(Decoding_Test, errorInP4) {
    EXPECT_EQ(170, hamming_decode(52428));
} 

TEST(Decoding_Test, doubleError) {
    EXPECT_EQ(-1, int8_t(hamming_decode(51400))); // hamming decode return uint and -1 is signed, thats why i used it here
} 

TEST(Decoding_Test, singleError) {
    // All is false
    EXPECT_EQ(238, hamming_decode(46260));

    // C and B is false
    EXPECT_EQ(238, hamming_decode(58596));

    // A and C is false
    EXPECT_EQ(238, hamming_decode(61680));

    // A and B is false
    EXPECT_EQ(238, hamming_decode(62965));
    
} 



int main() {
    testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}


/*
исправь тесты, там не те значения
прочекай условия ошибок если одна ошибка
*/
