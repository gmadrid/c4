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

  virtual size_t ChooseMove(Board *board) const = 0;

  Board::Cell Color() const { return color_; };
  void SetColor(Board::Cell color) {
    assert(color_ == Board::INVALID);
    assert(color == Board::YELLOW || color == Board::RED);
    color_ = color;
  }

 protected:
  //  std::string name_;
  Board::Cell color_ = Board::INVALID;
};

class FirstChoicePlayer : public Player {
 public:
  FirstChoicePlayer(absl::string_view name) : Player(name) {}
  size_t ChooseMove(Board *board) const override;
};

class LastChoicePlayer : public Player {
 public:
  LastChoicePlayer(absl::string_view name) : Player(name) {}
  size_t ChooseMove(Board *board) const override;
};

class RandomChoicePlayer : public Player {
 public:
  RandomChoicePlayer(absl::string_view name,
                     std::shared_ptr<std::default_random_engine> rnd)
      : Player(name), rnd_(rnd) {}
  size_t ChooseMove(Board *board) const override;

 private:
  std::shared_ptr<std::default_random_engine> rnd_;
};

}  // namespace c4

#endif  // C4_LIB_PLAYER_H
