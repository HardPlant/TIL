#include <gtest/gtest.h>
#include "keyserver.c"

TEST(KeyServerTest, Init) { 
    ASSERT_EQ(1, keyserver_init());
}