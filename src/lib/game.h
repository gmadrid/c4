#ifndef C4_LIB_GAME_H
#define C4_LIB_GAME_H

#include <chrono>
#include <memory>
#include <string>

#include "board.h"
#include "player.h"

namespace c4 {

class Game {
 public:
  Game(std::unique_ptr<Board>&& board, std::unique_ptr<Player>&& yellow_player,
       std::unique_ptr<Player>&& red_player, bool print_boards = false)
      : board_(std::move(board)),
        yellow_player_(std::move(yellow_player)),
        red_player_(std::move(red_player)),
        print_boards_(print_boards) {
    yellow_player_->SetColor(Board::YELLOW);
    red_player_->SetColor(Board::RED);
  };

  bool Move();
  bool GameOver();

  std::string to_string() const;

 private:
  Player* CurrentPlayer() const;
  void CheckForWin();

  Board::Cell current_player_ = Board::YELLOW;
  std::unique_ptr<Board> board_;
  std::unique_ptr<Player> yellow_player_;
  std::unique_ptr<Player> red_player_;
  bool print_boards_;
  Board::Cell winning_player_ = Board::INVALID;
};

}  // namespace c4

#endif  // C4_LIB_GAME_H
