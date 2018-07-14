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
        assert(pos < total_cells);
        cells_[pos++] = Board::BLANK;
        break;
      case 'X':
        assert(pos < total_cells);
        cells_[pos++] = Board::RED;
        break;
      case 'O':
        assert(pos < total_cells);
        cells_[pos++] = Board::YELLOW;
        break;
    }
  }
  assert(pos == total_cells);

  ReverseTopToBottom();
}

void Board::ReverseTopToBottom() {
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

  Board other(*this);
  other.ReverseTopToBottom();

  for (auto row : RowIndex(0).range()) {
    for (auto col : ColIndex(0).range()) {
      Cell cell = other.at(row, col);
      char ch = '.';
      if (cell == YELLOW)
        ch = 'O';
      else if (cell == RED)
        ch = 'X';
      val.push_back(ch);
    }
    val.push_back('\n');
  }
  return val;
}

void Board::Reset() {
  for (auto& cell : cells_) {
    cell = BLANK;
  }
}

void Board::ValidMoves(MoveList* valid_moves) const {
  assert(valid_moves != nullptr);
  valid_moves->clear();
  RowIndex top_row(num_rows - 1);
  for (auto col : ColIndex(0).range()) {
    if (at(top_row, col) == BLANK) {
      valid_moves->push_back(col);
    }
  }
}

bool Board::Move(ColIndex col, Cell color) {
  assert(color == RED || color == YELLOW);
  if (at(RowIndex(num_rows - 1), col) != BLANK) return false;

  for (auto row : RowIndex(0).range()) {
    if (at(row, col) == BLANK) {
      mutable_at(row, col) = color;
      return true;
    }
  }
  assert(false);
  return false;
}

void Board::Unmove(ColIndex col) {
  for (int i = num_rows - 1; i >= 0; --i) {
    RowIndex row(i);
    auto val = at(row, col);
    if (val == Board::RED || val == Board::YELLOW) {
      mutable_at(row, col) = Board::BLANK;
      return;
    }
  }
}

}  // namespace c4
