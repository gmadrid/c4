#include "../lib/win_finder.h"

#include "gtest/gtest.h"

namespace c4 {
namespace tests {

//    class WinFinder{};
using c4::Board;

bool CheckWinnerEq(Board &&board, Board::Cell winner) {
  return winner == FindWinOnBoard(&board);
}

TEST(WinFinder, Horizontal) {
  CheckWinnerEq(
      "XXXX..."
      "......."
      "......."
      "......."
      "......."
      "......."_board,
      Board::RED);

  CheckWinnerEq(
      "......."
      "......."
      "..OOOO."
      "......."
      "......."
      "......."_board,
      Board::YELLOW);

  CheckWinnerEq(
      "......."
      "......."
      "......."
      "......."
      "...XXXX"
      "......."_board,
      Board::RED);

  CheckWinnerEq(
      "......."
      "......."
      "......."
      "......."
      "......."
      ".OOOO.."_board,
      Board::YELLOW);

  CheckWinnerEq(
      "......."
      "......."
      "......."
      "......."
      "......."
      ".OOOX.."_board,
      Board::INVALID);
}

TEST(WinFinder, Vertical) {
  CheckWinnerEq(
      "O......"
      "O......"
      "O......"
      "O......"
      "......."
      "......."_board,
      Board::YELLOW);

  CheckWinnerEq(
      "......."
      ".O....."
      ".O....."
      ".O....."
      ".O....."
      "......."_board,
      Board::YELLOW);

  CheckWinnerEq(
      "......."
      "......."
      "....X.."
      "....X.."
      "....X.."
      "....X.."_board,
      Board::RED);

  CheckWinnerEq(
      "......."
      "O.....X"
      "O.....X"
      "O.....X"
      "......X"
      "......."_board,
      Board::RED);

  CheckWinnerEq(
      "....X.."
      "O...X.."
      "O......"
      "O...X.."
      "....X.."
      "....X.."_board,
      Board::INVALID);
}

TEST(WinFinder, CheckDiagonal) {
  CheckWinnerEq(
      "X......"
      ".X....."
      "..X...."
      "...X..."
      "......."
      "......."_board,
      Board::RED);
  CheckWinnerEq(
      "......."
      ".X....."
      "..X...."
      "...X..."
      "....X.."
      "......."_board,
      Board::RED);
  CheckWinnerEq(
      "......."
      "......."
      "X......"
      ".X....."
      "..X...."
      "...X..."_board,
      Board::RED);
  CheckWinnerEq(
      "......."
      "......."
      "...O..."
      "....O.."
      ".....O."
      "......O"_board,
      Board::YELLOW);

  CheckWinnerEq(
      "X....O."
      ".X..O.."
      "..XO..."
      "..O.X.."
      ".....X."
      "......X"_board,
      Board::YELLOW);

  CheckWinnerEq(
      "X....O."
      ".X..O.."
      "..XO..."
      "....X.."
      ".O...X."
      "......X"_board,
      Board::INVALID);
}

}  // namespace tests
}  // namespace c4
