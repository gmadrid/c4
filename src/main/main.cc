#include <iostream>
#include <memory>

#include "absl/memory/memory.h"

#include "../lib/board.h"
#include "../lib/game.h"
#include "../lib/minimax.h"
#include "../lib/player.h"

using std::cout;
using std::endl;

using c4::Board;
using c4::Game;

int main(int argc, char *argv[]) {
  // TODO: check on size of ColIndex. It should be 4.

  auto rnd = std::make_shared<std::default_random_engine>(
      std::chrono::system_clock::now().time_since_epoch().count());
  auto board = absl::make_unique<Board>();

  auto yellow = absl::make_unique<c4::RandomChoicePlayer>("Yellow", rnd);
  // auto yellow = absl::make_unique<c4::MinimaxPlayer>("Yellow");
  auto red = absl::make_unique<c4::MinimaxPlayer>("Red");

  Game game(std::move(board), std::move(yellow), std::move(red), true);

  while (!game.GameOver()) {
    game.Move();
  }

  return 0;
}
