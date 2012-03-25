#include "gtest/gtest.h"
#include "file.h"
#include "simplifier.h"

using namespace analisys;

class FileTest : public testing::Test 
{
public:
	FileTest() :
		file_1(File::build(TEST_DIR "teste1", nop)),
		file_2(File::build(TEST_DIR "teste2", nop))
	{}
protected:
	static const Simplifier nop;

	File::Ptr file_1;
	File::Ptr file_2;
	File::Ptr file_3;
};

const Simplifier FileTest::nop{};

TEST_F(FileTest, Constructor)
{
	EXPECT_TRUE(static_cast<bool>(file_1));
	EXPECT_TRUE(static_cast<bool>(file_2));
	EXPECT_FALSE(static_cast<bool>(file_3));
}

TEST_F(FileTest, Size)
{
	EXPECT_EQ(file_1->size(), 58);
	EXPECT_EQ(file_2->size(), 32);
}

TEST_F(FileTest, Index)
{
	EXPECT_EQ((*file_1)[0], (*file_2)[0]);
	EXPECT_EQ((*file_1)[0], (*file_1)[0]);
	EXPECT_NE((*file_1)[0], (*file_1)[1]);
}

TEST_F(FileTest, Equal)
{
	EXPECT_NE(*file_1, *file_2);

	File::Ptr file_1_other = File::build(file_1->filename(), nop);
	EXPECT_EQ(*file_1_other, *file_1);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
