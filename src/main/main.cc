#include <iostream>
#include <memory>

#include "absl/memory/memory.h"

#include "../lib/board.h"
#include "../lib/game.h"

using c4::Board;
using c4::Game;

int main(int argc, char *argv[]) {
  auto board = absl::make_unique<Board>();
  Game game(std::move(board), true);

  while (!game.GameOver()) {
    game.Move();
  }
  std::cout << game.to_string() << std::endl;

  return 0;
}
