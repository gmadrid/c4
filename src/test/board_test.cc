#include "../lib/board.h"

#include "gtest/gtest.h"

namespace c4 {
namespace tests {

TEST(Board, BasicCtor) {
  Board board;
  Board::MoveList valid_moves;
  board.ValidMoves(&valid_moves);

  ASSERT_EQ(7, valid_moves.size());
}

TEST(Board, StrLiteral) {
  auto board =
      R"XXX(
O......
X......
O......
X......
O......
X......)XXX"_board;
  Board::MoveList valid_moves;
  board.ValidMoves(&valid_moves);

  ASSERT_EQ(6, valid_moves.size());

  auto board2 =
      "O.....X"
      "X...O.O"
      "O..OX.X"
      "X.OXO.O"
      "OOXOX.X"
      "XXOXO.O"_board;
  board2.ValidMoves(&valid_moves);

  ASSERT_EQ(5, valid_moves.size());
  ASSERT_EQ(
      "O.....X\n"
      "X...O.O\n"
      "O..OX.X\n"
      "X.OXO.O\n"
      "OOXOX.X\n"
      "XXOXO.O\n",
      board2.to_string());
}

}  // namespace tests
}  // namespace c4
