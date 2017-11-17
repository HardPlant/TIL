#include <gtest/gtest.h>
#include "keyserver.c"

TEST(KeyServerTest, Init) { 
    ASSERT_EQ(1, keyserver_init());
}

TEST(KeyServerTest, GetStoredId) { 
    ASSERT_EQ(2, keyserver_get_id(0));
}
