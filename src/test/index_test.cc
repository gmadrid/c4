#include "../lib/index.h"

#include "gtest/gtest.h"

namespace c4 {
namespace tests {

class TestTag {};
using TIndex = Index<TestTag, 22>;
using TIndexRange = IndexRange<TestTag, 22>;

TEST(Index, IndexCtor) {
  TIndex index(6);
  ASSERT_EQ(6, index.to_size_t());
}

TEST(Index, IndexTooBig) { ASSERT_DEATH(TIndex(22), ""); }

TEST(Index, Size) {
  EXPECT_EQ(3, (Index<TestTag, 3>::size()));
  EXPECT_EQ(8, (Index<TestTag, 8>::size()));
}

TEST(Index, ToSize) {
  TIndex i13(13);
  TIndex i0(0);
  TIndex i21(21);

  EXPECT_EQ(13, i13.to_size_t());
  EXPECT_EQ(0, i0.to_size_t());
  EXPECT_EQ(21, i21.to_size_t());
}

TEST(Index, Equality) {
  TIndex i2(2);
  TIndex i2_2(2);
  TIndex i3(3);

  EXPECT_TRUE(i2 == i2);
  EXPECT_FALSE(i2 != i2);

  EXPECT_TRUE(i2 == i2_2);
  EXPECT_FALSE(i2 != i2_2);

  EXPECT_TRUE(i2 != i3);
  EXPECT_FALSE(i2 == i3);
}

TEST(Index, Add) {
  EXPECT_EQ(13, (TIndex(4) + TIndex(9)).to_size_t());
  EXPECT_EQ(18, (TIndex(7) + 11).to_size_t());
  EXPECT_EQ(4, (4 + TIndex(0)).to_size_t());

  // overflow
  EXPECT_DEATH(TIndex(20) + 4, "");
}

TEST(IndexRange, Create) { TIndexRange(5); }

TEST(IndexRange, Begin) { EXPECT_EQ(TIndex(5), *TIndexRange(5).begin()); }

TEST(IndexRange, RangeLoop) {
  int count = 0;
  TIndexRange ir(count);
  for (auto i : ir) {
    ASSERT_EQ(count, i.to_size_t());
    count++;
  }
  ASSERT_EQ(TIndex::size(), count);

  count = 5;
  TIndexRange ir5(count);
  for (auto i : ir5) {
    ASSERT_EQ(count, i.to_size_t());
    count++;
  }
  ASSERT_EQ(TIndex::size(), count);
}

TEST(IndexRange, RangeTo) {
  int count = 17;
  TIndexRange ir(TIndex(17), TIndex(18));
  for (auto i : ir) {
    ASSERT_EQ(count, i.to_size_t());
    count++;
  }
  ASSERT_EQ(18, count);
}

}  // namespace tests
}  // namespace c4
