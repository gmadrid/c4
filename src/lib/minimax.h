#ifndef C4_LIB_MINIMAX_H
#define C4_LIB_MINIMAX_H

#include "board.h"
#include "player.h"

namespace c4 {

constexpr size_t DEFAULT_DEPTH = 8;
class MinimaxChooser {
 public:
  MinimaxChooser(size_t depth = DEFAULT_DEPTH) : depth_(depth) {}

  size_t operator()(Board *board, Board::Cell color) {
    size_t move;
    auto result = minimax(board, depth_, color, &move);
    return move;
  }

 private:
  double minimax(Board *board, size_t max_depth, Board::Cell current_color,
                 size_t *chosen_move);
  size_t depth_;
};

using MinimaxPlayer = BasicPlayer<MinimaxChooser>;

}  // namespace c4

#endif  // C4_LIB_MINIMAX_H
