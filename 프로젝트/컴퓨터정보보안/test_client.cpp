#include <gtest/gtest.h>
#include "client.h"

TEST(ClientTest, Init) { 
    ASSERT_EQ(1, client_init());
}
