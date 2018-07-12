#include "../lib/minimax.h"

#include "gtest/gtest.h"

#include "../lib/board.h"

namespace c4 {
namespace tests {

TEST(Minimax, BasicWin) {
  auto board =
      "......."
      "......."
      "......."
      "......."
      "......."
      "OOO...."_board;

  MinimaxChooser chooser(2);
  auto ymove = chooser(&board, Board::YELLOW);
  EXPECT_EQ(3, ymove);
}

TEST(Minimax, BasicDefense) {
  auto board =
      "......."
      "......."
      "......."
      "......."
      "......."
      "OOO...."_board;

  MinimaxChooser chooser(2);
  auto rmove = chooser(&board, Board::RED);
  EXPECT_EQ(3, rmove);
}

TEST(Minimax, OffenceBeforeDefense) {
  auto board =
      "......."
      "......."
      "......."
      "......X"
      "......X"
      "OOO...X"_board;

  MinimaxChooser chooser(3);
  auto ymove = chooser(&board, Board::YELLOW);
  EXPECT_EQ(3, ymove);

  auto rmove = chooser(&board, Board::RED);
  EXPECT_EQ(6, rmove);
}

}  // namespace tests
}  // namespace c4

// Why doesn't X block O's win on col 6?
// X......
// O......
// X......
// X......
// O.XOOO.
// X.XOOOX
