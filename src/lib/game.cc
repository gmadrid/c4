#include "game.h"

#include <iostream>

#include "absl/strings/str_cat.h"
#include "absl/strings/substitute.h"

#include "player.h"

namespace c4 {

using std::string;
using std::vector;

string PlayerToColor(Board::Cell cell) {
  switch (cell) {
    case Board::BLANK:
      return "blank";
    case Board::INVALID:
      return "INVALID";
    case Board::RED:
      return "Red";
    case Board::YELLOW:
      return "Yellow";
  }
}

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

bool Game::GameOver() {
  vector<size_t> valid_moves;
  board_->ValidMoves(&valid_moves);
  if (valid_moves.empty()) {
    return true;
  }

  CheckForWin();
  if (winning_player_ != Board::INVALID) {
    std::cout << "WINNER: " << PlayerToColor(winning_player_) << std::endl;
    return true;
  }

  return false;
}

void Game::CheckForWin() {
  CheckForHorizontalWin();
  if (winning_player_ != Board::INVALID) return;

  CheckForVerticalWin();
  if (winning_player_ != Board::INVALID) return;

  CheckForDiagonalWin();
}

template <size_t START_ROW, int DIR>
Board::Cell CheckForDiagonalWinInDirection(Board *board) {
  for (size_t start_delta = 0; start_delta <= 3; ++start_delta) {
    size_t start_row = START_ROW + start_delta;

    for (size_t start_col = 0; start_col < 4; ++start_col) {
      Board::Cell color = board->at(start_row, start_col);
      if (color == Board::BLANK || color == Board::INVALID) {
        continue;
      }

      size_t delta;
      for (delta = 1; delta < 4; ++delta) {
        if (board->at(start_row + delta * DIR, start_col + delta) != color) {
          break;
        }
      }
      if (delta == 4) {
        return color;
      }
    }
  }
  return Board::INVALID;
}

void Game::CheckForDiagonalWin() {
  auto color = CheckForDiagonalWinInDirection<0, 1>(board_.get());
  if (color != Board::INVALID) {
    winning_player_ = color;
    return;
  }

  color = CheckForDiagonalWinInDirection<3, -1>(board_.get());
  if (color != Board::INVALID) {
    winning_player_ = color;
    return;
  }
}

void Game::CheckForVerticalWin() {
  for (size_t start_row = 0; start_row < 3; ++start_row) {
    for (size_t col = 0; col < Board::num_cols; ++col) {
      Board::Cell color = board_->at(start_row, col);
      if (color == Board::BLANK || color == Board::INVALID) {
        continue;
      }

      size_t delta;
      for (delta = 1; delta < 4; ++delta) {
        if (board_->at(start_row + delta, col) != color) {
          break;
        }
      }
      if (delta == 4) {
        winning_player_ = color;
        return;
      }
    }
  }
}

void Game::CheckForHorizontalWin() {
  // Check for horizontal wins.
  for (size_t start_col = 0; start_col < 4; ++start_col) {
    for (size_t row = 0; row < Board::num_rows; ++row) {
      Board::Cell color = board_->at(row, start_col);
      if (color == Board::BLANK || color == Board::INVALID) {
        continue;
      }

      size_t delta;
      for (delta = 1; delta < 4; ++delta) {
        if (board_->at(row, start_col + delta) != color) {
          break;
        }
      }
      if (delta == 4) {
        winning_player_ = color;
        return;
      }
    }
  }
}

}  // namespace c4
