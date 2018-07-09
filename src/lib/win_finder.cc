#include "win_finder.h"

namespace c4 {

static Board::Cell FindHorizontalWin(Board *board) {
  // Check for horizontal wins.
  for (size_t start_col = 0; start_col < 4; ++start_col) {
    for (size_t row = 0; row < Board::num_rows; ++row) {
      Board::Cell color = board->at(row, start_col);
      if (color == Board::BLANK || color == Board::INVALID) {
        continue;
      }

      size_t delta;
      for (delta = 1; delta < 4; ++delta) {
        if (board->at(row, start_col + delta) != color) {
          break;
        }
      }
      if (delta == 4) {
        return color;
      }
    }
  }
  return Board::INVALID;
}

static Board::Cell FindVerticalWin(Board *board) {
  for (size_t start_row = 0; start_row < 3; ++start_row) {
    for (size_t col = 0; col < Board::num_cols; ++col) {
      Board::Cell color = board->at(start_row, col);
      if (color == Board::BLANK || color == Board::INVALID) {
        continue;
      }

      size_t delta;
      for (delta = 1; delta < 4; ++delta) {
        if (board->at(start_row + delta, col) != color) {
          break;
        }
      }
      if (delta == 4) {
        return color;
      }
    }
  }
  return Board::INVALID;
}

template <size_t START_ROW, int DIR>
static Board::Cell FindDiagonalWinInDirection(Board *board) {
  for (size_t start_delta = 0; start_delta <= 3; ++start_delta) {
    size_t start_row = START_ROW + start_delta;

    for (size_t start_col = 0; start_col < 4; ++start_col) {
      Board::Cell color = board->at(start_row, start_col);
      if (color == Board::BLANK || color == Board::INVALID) {
        continue;
      }

      size_t delta;
      for (delta = 1; delta < 4; ++delta) {
        if (board->at(start_row + delta * DIR, start_col + delta) != color) {
          break;
        }
      }
      if (delta == 4) {
        return color;
      }
    }
  }
  return Board::INVALID;
}

static Board::Cell FindDiagonalWin(Board *board) {
  auto color = FindDiagonalWinInDirection<0, 1>(board);
  if (color != Board::INVALID) {
    return color;
  }

  color = FindDiagonalWinInDirection<3, -1>(board);
  if (color != Board::INVALID) {
    return color;
  }
  return Board::INVALID;
}

Board::Cell FindWinOnBoard(Board *board) {
  Board::Cell winner = FindHorizontalWin(board);
  if (winner != Board::INVALID) return winner;

  winner = FindVerticalWin(board);
  if (winner != Board::INVALID) return winner;

  return FindDiagonalWin(board);
}

}  // namespace c4
