#ifndef C4_LIB_MINIMAX_H
#define C4_LIB_MINIMAX_H

#include "board.h"
#include "player.h"

namespace c4 {

class MinimaxChooser {
 public:
  size_t operator()(Board *board, Board::Cell color) {
    auto result = minimax(board, 5, true, color); // THIS IS WRONG!
    return result.first;
    //    std::vector<size_t> valid_moves;
    //    board->ValidMoves(&valid_moves);
    //    return valid_moves.at(valid_moves.size() / 2);
  }

 private:
  std::pair<size_t, double> minimax(Board *board, size_t max_depth,
                                    bool maximize,
                                    Board::Cell maximizing_color);
};

using MinimaxPlayer = BasicPlayer<MinimaxChooser>;

}  // namespace c4

#endif  // C4_LIB_MINIMAX_H
