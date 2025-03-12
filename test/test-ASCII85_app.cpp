#include <gtest/gtest.h>
#include <sstream>
#include <string>


using namespace std;

extern void encode(const char* input, size_t len, ostream& out);
extern bool decode(istream& in, ostream& out);

TEST(EncoderTest, FourZeroBytes) {
    string input(4, '\0');
    ostringstream output;
    encode(input.data(), 4, output);
    EXPECT_EQ(output.str(), "z");
}

TEST(DecoderTest, DecodeZ) {
    istringstream input("z");
    ostringstream output;
    bool success = decode(input, output);
    EXPECT_TRUE(success);
    EXPECT_EQ(output.str(), string(4, '\0'));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}