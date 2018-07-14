#ifndef C4_LIB_BOARD_H
#define C4_LIB_BOARD_H

#include <array>
#include <vector>

#include <absl/strings/string_view.h>

#include "index.h"

namespace c4 {

namespace private_tags {
constexpr size_t num_rows = 6;
constexpr size_t num_cols = 7;

class RowTag {};
class ColTag {};
}  // namespace private_tags

using RowIndex = Index<private_tags::RowTag, private_tags::num_rows>;
using ColIndex = Index<private_tags::ColTag, private_tags::num_cols>;

class Board {
 public:
  Board();

  // Board rep is X = Red, O = Yellow, . = Blank.
  // Anything else is ignored.
  // There MUST be num_rows * num_cols total 'X', 'O' and '.'.
  // First character is (5, 0), last character is (0, 6), so the ASCII rep
  // will look like the board it represents (if it has LF at the end of each
  // line).
  Board(char const *str, size_t len);
  //  Board(absl::string_view board_rep);
  std::string to_string() const;

  Board(const Board &) = default;
  Board(Board &&) = default;
  Board &operator=(const Board &) = default;
  Board &operator=(Board &&) = default;

  enum Cell {
    INVALID = -1,
    BLANK = 0,
    RED = 1,
    YELLOW = 2,
  };

  // Returned value is only valid until first Board mutation.
  using MoveList = std::vector<ColIndex>;
  void ValidMoves(MoveList *) const;
  Cell at(RowIndex row, ColIndex col) const {
    return cells_[row.to_size_t() * num_cols + col.to_size_t()];
  }

  void Reset();
  bool Move(ColIndex col, Cell color);
  void Unmove(ColIndex col);

 private:
  constexpr static auto num_rows = RowIndex::size();
  constexpr static auto num_cols = ColIndex::size();
  constexpr static auto total_cells = num_rows * num_cols;

  void ReverseTopToBottom();
  Cell &mutable_at(RowIndex row, ColIndex col) {
    return cells_[row.to_size_t() * num_cols + col.to_size_t()];
  }

  // row-major list of Cells.
  // 0, 0 is bottom-left.
  std::array<Cell, total_cells> cells_;
};

}  // namespace c4

inline c4::Board operator""_board(char const *str, size_t sz) {
  return c4::Board(str, sz);
}

#endif  // C4_LIB_BOARD_H
