#include <gtest/gtest.h>
#include "keyserver.c"

TEST(KeyServerTest, Init) { 
    SERVER* server = keyserver_init();
    ASSERT_TRUE(server);
}

TEST(KeyServerTest, GetStoredId) { 
    ASSERT_EQ(2, keyserver_get_id(0));
}

TEST(KeyServerTest, TryLoginWithBadId) {
    keyserver_set_id(0,2);
    keyserver_set_id(1,4);
    ASSERT_EQ(1, keyserver_try_login(0));
}
TEST(KeyServerTest, TryLoginWithGoodId) {
    keyserver_set_id(0,2);
    keyserver_set_id(1,4);
    ASSERT_EQ(2, keyserver_try_login(0));
}
