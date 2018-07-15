#ifndef C4_LIB_MINIMAX_H
#define C4_LIB_MINIMAX_H

#include <deque>
#include <limits>

#include "absl/types/optional.h"

#include "board.h"
#include "player.h"

namespace c4 {

constexpr size_t DEFAULT_DEPTH = 8;
class MinimaxChooser {
 public:
  MinimaxChooser(size_t depth = DEFAULT_DEPTH) : depth_(depth) {}

  ColIndex operator()(Board *board, Board::Cell color) {
    auto result = minimax(board, depth_, std::numeric_limits<double>::lowest(),
                          std::numeric_limits<double>::max(), color);
    return result.first.front();
  }

 private:
  using MoveList = std::deque<ColIndex>;
  using MinimaxResult = std::pair<MoveList,  // Moves arriving at score.
                                  double>;   // It's eval score.

  MinimaxResult minimax(Board *board, size_t max_depth, double alpha,
                        double beta, Board::Cell current_color);
  size_t depth_;
};

using MinimaxPlayer = BasicPlayer<MinimaxChooser>;

}  // namespace c4

#endif  // C4_LIB_MINIMAX_H
