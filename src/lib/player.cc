#include "player.h"

namespace c4 {

using std::vector;

size_t FirstChoicePlayer::ChooseMove(Board *board) const {
  vector<size_t> valid_moves;
  board->ValidMoves(&valid_moves);
  return valid_moves.front();
}

size_t LastChoicePlayer::ChooseMove(Board *board) const {
  vector<size_t> valid_moves;
  board->ValidMoves(&valid_moves);
  return valid_moves.back();
}

size_t RandomChoicePlayer::ChooseMove(Board *board) const {
  vector<size_t> valid_moves;
  board->ValidMoves(&valid_moves);
  return valid_moves.at(rnd_() % valid_moves.size());
}

}  // namespace c4
