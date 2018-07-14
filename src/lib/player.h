#ifndef C4_LIB_PLAYER_H
#define C4_LIB_PLAYER_H

#include <chrono>
#include <random>
#include <string>

#include "absl/strings/string_view.h"

#include "board.h"

namespace c4 {

class Player {
 public:
  Player(absl::string_view name) /*: name_(name)*/ {};

  virtual ColIndex ChooseMove(Board *board) = 0;

  Board::Cell Color() const { return color_; };
  void SetColor(Board::Cell color) {
    // Ensure that the color is set properly and never gets set again.
    assert(color_ == Board::INVALID);
    assert(color == Board::YELLOW || color == Board::RED);
    color_ = color;
  }

 protected:
  //  std::string name_;
  Board::Cell color_ = Board::INVALID;
};

template <typename C, typename... CARGS>
class BasicPlayer : public Player {
 public:
  BasicPlayer(absl::string_view name, CARGS... chooser_args)
      : Player(name), chooser_(chooser_args...) {}
  ColIndex ChooseMove(Board *board) override { return chooser_(board, color_); }

 protected:
  C chooser_;
};

class FirstChoiceChooser {
 public:
  ColIndex operator()(Board *board, Board::Cell color) {
    Board::MoveList valid_moves;
    board->ValidMoves(&valid_moves);
    return valid_moves.front();
  }
};

class LastChoiceChooser {
 public:
  ColIndex operator()(Board *board, Board::Cell color) {
    Board::MoveList valid_moves;
    board->ValidMoves(&valid_moves);
    return valid_moves.back();
  }
};

class RandomChoiceChooser {
 public:
  RandomChoiceChooser(std::shared_ptr<std::default_random_engine> rnd)
      : rnd_(rnd) {}
  ColIndex operator()(Board *board, Board::Cell color) {
    Board::MoveList valid_moves;
    board->ValidMoves(&valid_moves);
    return valid_moves.at((*rnd_)() % valid_moves.size());
  }

 private:
  std::shared_ptr<std::default_random_engine> rnd_;
};

using FirstChoicePlayer = BasicPlayer<FirstChoiceChooser>;
using LastChoicePlayer = BasicPlayer<LastChoiceChooser>;
using RandomChoicePlayer =
    BasicPlayer<RandomChoiceChooser,
                std::shared_ptr<std::default_random_engine>>;

}  // namespace c4

#endif  // C4_LIB_PLAYER_H
