#include "game.h"

#include <iostream>

#include "absl/strings/str_cat.h"
#include "absl/strings/substitute.h"

#include "player.h"

namespace c4 {

using std::string;
using std::vector;

string Game::to_string() const {
  return absl::StrCat(
      absl::Substitute("$0's turn\n",
                       current_player_ == Board::YELLOW ? "Yellow" : "Red"),
      board_->to_string());
}

Player *Game::CurrentPlayer() const {
  return current_player_ == Board::YELLOW ? yellow_player_.get()
                                          : red_player_.get();
}

bool Game::Move() {
  auto move = CurrentPlayer()->ChooseMove(board_.get());
  board_->Move(move, current_player_);

  if (print_boards_) {
    std::cout << to_string() << std::endl;
  }

  current_player_ =
      current_player_ == Board::YELLOW ? Board::RED : Board::YELLOW;

  return true;
}

bool Game::GameOver() const {
  vector<size_t> valid_moves;
  board_->ValidMoves(&valid_moves);
  return valid_moves.empty();
}

}  // namespace c4
