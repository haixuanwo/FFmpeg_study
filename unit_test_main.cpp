/**
 * @author Clark
 * @email haixuanwoTxh@gmail.com
 * @date 2021-10-24
 */

#include <gtest/gtest.h>

TEST(testName, subName)
{
	EXPECT_FALSE(false);
	EXPECT_TRUE(true);
}

int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}
