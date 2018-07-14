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
  EXPECT_EQ(ColIndex(3), ymove);
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
  EXPECT_EQ(ColIndex(3), rmove);
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
  EXPECT_EQ(ColIndex(3), ymove);

  auto rmove = chooser(&board, Board::RED);
  EXPECT_EQ(ColIndex(6), rmove);
}

TEST(Minimax, Bug1) {
  // Why doesn't this choose Col 4?
  auto board =
      "O......"
      "X......"
      "O......"
      "X......"
      "XXOO.O."
      "XXOXOO."_board;
  // If depth is 7, this test passes. It breaks at 8, though.
  // However, given any search depth, any move for X but C4 will lose.
  MinimaxChooser chooser(8);
  auto rmove = chooser(&board, Board::YELLOW);
  EXPECT_EQ(ColIndex(4), rmove);
  std::cout << rmove.to_size_t() << std::endl;
}

}  // namespace tests
}  // namespace c4
