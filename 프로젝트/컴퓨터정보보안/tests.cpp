#include "test_client.cpp"
#include "test_keyserver.cpp"
#include "test_server.cpp"
#include "test_c_hash.cpp"
#include <gtest/gtest.h>
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}