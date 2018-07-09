#ifndef C4_LIB_MINIMAX_H
#define C4_LIB_MINIMAX_H

#include "board.h"
#include "player.h"

namespace c4 {

class MinimaxChooser {
 public:
  size_t operator()(Board *board) {
    std::vector<size_t> valid_moves;
    board->ValidMoves(&valid_moves);
    return valid_moves.at(valid_moves.size() / 2);
  }
};

using MinimaxPlayer = BasicPlayer<MinimaxChooser>;

}  // namespace c4

#endif  // C4_LIB_MINIMAX_H
