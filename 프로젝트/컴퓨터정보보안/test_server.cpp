#include <gtest/gtest.h>
#include "server.c"

TEST(ServerTest, Init) { 
    ASSERT_EQ(1, server_init());
}