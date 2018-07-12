#ifndef C4_LIB_BOARD_H
#define C4_LIB_BOARD_H

#include <array>
#include <vector>

#include <absl/strings/string_view.h>

namespace c4 {

class Board {
 public:
  Board();

  // Board rep is X = Red, O = Yellow, . = Blank.
  // Anything else is ignored.
  // There MUST be num_rows * num_cols total 'X', 'O' and '.'.
  // First character is (5, 0), last character is (0, 6), so the ASCII rep
  // will look like the board it represents (if it has LF at the end of each
  // line).
  Board(char const *str, size_t sz);
  //  Board(absl::string_view board_rep);
  std::string to_string() const;

  Board(const Board &) = default;
  Board(Board &&) = default;
  Board &operator=(const Board &) = default;
  Board &operator=(Board &&) = default;

  constexpr static size_t num_rows = 6;
  constexpr static size_t num_cols = 7;

  enum Cell {
    INVALID = -1,
    BLANK = 0,
    RED = 1,
    YELLOW = 2,
  };

  // Returned value is only valid until first Board mutation.
  using MoveList = std::vector<size_t>;
  void ValidMoves(MoveList *) const;
  Cell at(size_t row, size_t col) const;

  void Reset();
  bool Move(size_t col, Cell color);
  void Unmove(size_t col);

 private:
  // row-major list of Cells.
  // 0, 0 is bottom-left.
  std::array<Cell, num_rows * num_cols> cells_;
};

}  // namespace c4

inline c4::Board operator""_board(char const *str, size_t sz) {
  return c4::Board(str, sz);
}

#endif  // C4_LIB_BOARD_H
