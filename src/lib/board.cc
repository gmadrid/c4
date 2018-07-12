#include "board.h"

#include <algorithm>

namespace c4 {

using std::string;
using std::vector;

Board::Board() { Reset(); }

Board::Board(char const* str, size_t sz) {
  size_t pos = 0;
  for (size_t i = 0; i < sz; ++i) {
    switch (str[i]) {
      case '.':
        assert(pos < num_rows * num_cols);
        cells_[pos++] = Board::BLANK;
        break;
      case 'X':
        assert(pos < num_rows * num_cols);
        cells_[pos++] = Board::RED;
        break;
      case 'O':
        assert(pos < num_rows * num_cols);
        cells_[pos++] = Board::YELLOW;
        break;
    }
  }
  assert(pos == num_rows * num_cols);

  // Now swap rows 0 & 5, 1 & 4, 2 & 3.
  auto cbegin = cells_.begin();
  std::swap_ranges(cbegin + 0, cbegin + 0 + num_cols, cbegin + 5 * num_cols);
  std::swap_ranges(cbegin + 1 * num_cols, cbegin + 2 * num_cols,
                   cbegin + 4 * num_cols);
  std::swap_ranges(cbegin + 2 * num_cols, cbegin + 3 * num_cols,
                   cbegin + 3 * num_cols);
}

string Board::to_string() const {
  string val;
  val.reserve((num_rows + 1) * num_cols);

  size_t row = num_rows;
  do {
    row--;
    for (size_t col = 0; col < num_cols; ++col) {
      Cell cell = at(row, col);
      char ch = '.';
      if (cell == YELLOW)
        ch = 'O';
      else if (cell == RED)
        ch = 'X';
      val.push_back(ch);
    }
    val.push_back('\n');
  } while (row > 0);
  return val;
}

void Board::Reset() {
  for (auto& cell : cells_) {
    cell = BLANK;
  }
}

Board::Cell Board::at(size_t row, size_t col) const {
  if (row >= num_rows || col >= num_cols) return INVALID;

  return cells_[row * num_cols + col];
}

void Board::ValidMoves(std::vector<size_t>* valid_moves) const {
  assert(valid_moves != nullptr);
  valid_moves->clear();
  for (size_t col = 0; col < num_cols; ++col) {
    if (at(num_rows - 1, col) == BLANK) {
      valid_moves->push_back(col);
    }
  }
}

bool Board::Move(size_t col, Cell color) {
  assert(color == RED || color == YELLOW);
  assert(col < num_cols);
  if (at(num_rows - 1, col) != BLANK) return false;

  for (size_t row = 0; row < num_rows; ++row) {
    if (at(row, col) == BLANK) {
      cells_[row * num_cols + col] = color;
      return true;
    }
  }
  assert(false);
  return false;
}

void Board::Unmove(size_t col) {
  for (int i = num_rows - 1; i >= 0; --i) {
    auto val = at(i, col);
    if (val == Board::RED || val == Board::YELLOW) {
      cells_[i * num_cols + col] = Board::BLANK;
      return;
    }
  }
}

}  // namespace c4
