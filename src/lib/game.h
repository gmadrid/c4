#ifndef C4_LIB_GAME_H
#define C4_LIB_GAME_H

#include <memory>
#include <string>

#include "board.h"

namespace c4 {

  class Game {
  public:
    Game(std::unique_ptr<Board>&& board, bool print_boards = false)
      : board_(std::move(board)), print_boards_(print_boards) {};

    bool Move();
    bool GameOver() const;

    std::string to_string() const;
    
  private:
    Board::Cell current_player_ = Board::YELLOW;
    std::unique_ptr<Board> board_;
    bool print_boards_;
  };

}  // namespace c4

#endif  // C4_LIB_GAME_H
