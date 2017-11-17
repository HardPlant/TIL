#include <gtest/gtest.h>
#include "client.c"

TEST(ClientTest, Init) { 
    ASSERT_EQ(1, client_init());
}