#include <gtest/gtest.h>
#include "keyserver.c"

TEST(KeyServerTest, Init) { 
    int public_key = 0;
    KEY_SERVER* server = keyserver_init(public_key);
    ASSERT_TRUE(server);
    ASSERT_EQ(server->public_key, public_key);
    free(server);
}

TEST(KeyServerTest, GetStoredId) { 
    KEY_SERVER* server = keyserver_init(0);
    keyserver_set_id(server,0,2);

    ASSERT_EQ(2, keyserver_get_id(server, 0));
    free(server);
}

TEST(KeyServerTest, TryLoginWithBadId) {
    KEY_SERVER* server = keyserver_init(0);

    keyserver_set_id(server, 0,2);
    keyserver_set_id(server, 1,4);
    ASSERT_EQ(1, keyserver_try_login(server,0));
    
    free(server);
}
TEST(KeyServerTest, TryLoginWithGoodId) {
    KEY_SERVER* server = keyserver_init(0);

    keyserver_set_id(server, 0,2);
    keyserver_set_id(server, 1,4);
    ASSERT_EQ(2, keyserver_try_login(server,0));
    
    free(server);
}
