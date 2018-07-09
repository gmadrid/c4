#include <iostream>
#include <memory>

#include "absl/memory/memory.h"

#include "../lib/board.h"
#include "../lib/game.h"

using c4::Board;
using c4::Game;

int main(int argc, char *argv[]) {
  auto board = absl::make_unique<Board>();
  auto yellow = absl::make_unique<c4::RandomChoicePlayer>("Yellow");
  auto red = absl::make_unique<c4::RandomChoicePlayer>("Red");

  Game game(std::move(board), std::move(yellow), std::move(red), true);

  while (!game.GameOver()) {
    game.Move();
  }

  return 0;
}
