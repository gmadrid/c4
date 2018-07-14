#include "win_finder.h"

#include "board.h"

namespace c4 {

static Board::Cell FindHorizontalWin(Board *board) {
  // Check for horizontal wins.
  for (auto start_col : ColIndex(0).range_to(ColIndex(4))) {
    for (auto row : RowIndex(0).range()) {
      // for (size_t row = 0; row < private_tags::num_rows; ++row) {
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
  for (auto start_row : RowIndex(0).range_to(RowIndex(3))) {
    //  for (size_t start_row = 0; start_row < 3; ++start_row) {
    for (auto col : ColIndex(0).range()) {
      //    for (size_t col = 0; col < private_tags::num_cols; ++col) {
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

// template <RowIndex START_ROW, int DIR>
static Board::Cell FindDiagonalWinInDirection(Board *board, RowIndex first_row,
                                              int direction) {
  for (size_t start_delta = 0; start_delta < 3; ++start_delta) {
    RowIndex start_row = first_row + start_delta;

    for (auto start_col : ColIndex(0).range_to(ColIndex(4))) {
      Board::Cell color = board->at(start_row, start_col);
      if (color == Board::BLANK || color == Board::INVALID) {
        continue;
      }

      size_t delta;
      for (delta = 1; delta < 4; ++delta) {
        if (board->at(start_row + delta * direction, start_col + delta) !=
            color) {
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
  auto color = FindDiagonalWinInDirection(board, RowIndex(0), 1);
  if (color != Board::INVALID) {
    return color;
  }

  color = FindDiagonalWinInDirection(board, RowIndex(3), -1);
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
