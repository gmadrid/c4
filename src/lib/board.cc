#include "board.h"

namespace c4 {

using std::string;
using std::vector;

Board::Board() { Reset(); }

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

}  // namespace c4
