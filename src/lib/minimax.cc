#include "minimax.h"

#include <algorithm>
#include <iostream>

#include "absl/strings/str_join.h"
#include "absl/strings/substitute.h"
#include "win_finder.h"

template <typename... T>
void D(const std::string &format, T... args) {
  std::cout << absl::Substitute(format, args...) << std::endl;
}

namespace c4 {

using std::make_pair;
using std::max_element;
using std::pair;
using std::vector;

double evaluate(Board *board) { return 0.0; }

double MinimaxChooser::minimax(Board *board, size_t max_depth,
                               Board::Cell current_color, size_t *chosen_move) {
  // Red is always the maximizing color.
  bool maximizing = current_color == Board::RED;

  Board::Cell winner = FindWinOnBoard(board);
  if (winner != Board::INVALID) {
    if (chosen_move != nullptr) *chosen_move = -1;
    if (winner == Board::RED) {
      return std::numeric_limits<double>::max();
    } else {
      return std::numeric_limits<double>::lowest();
    }
  }

  vector<size_t> valid_moves;
  vector<pair<size_t, double>> candidates;
  board->ValidMoves(&valid_moves);

  if (valid_moves.empty()) {
    // It's a tie. There are no moves and no winner.
    return 0;
  }

  if (max_depth == 0) {
    return evaluate(board);
  }

  if (maximizing) {
    for (auto move : valid_moves) {
      board->Move(move, current_color);
      candidates.emplace_back(
          move,
          minimax(board, max_depth - 1,
                  current_color == Board::RED ? Board::YELLOW : Board::RED,
                  nullptr));
      auto p = candidates.back();
      board->Unmove(move);
    }
    // auto s = absl::StrJoin(candidates, "|", absl::PairFormatter(":"));
    //    D("red candidates($1): $0", s, max_depth);
    auto p = max_element(
        candidates.begin(), candidates.end(),
        [](const pair<size_t, double> &p1, const pair<size_t, double> &p2) {
          return p1.second < p2.second;
        });
    if (chosen_move != nullptr) *chosen_move = p->first;
    return p->second;
  } else {
    for (auto move : valid_moves) {
      board->Move(move, current_color);
      candidates.emplace_back(
          move,
          minimax(board, max_depth - 1,
                  current_color == Board::RED ? Board::YELLOW : Board::RED,
                  nullptr));
      auto p = candidates.back();
      board->Unmove(move);
    }
    // auto s = absl::StrJoin(candidates, "|", absl::PairFormatter(":"));
    //    D("yellow candidates($1): $0", s, max_depth);
    auto p = min_element(
        candidates.begin(), candidates.end(),
        [](const pair<size_t, double> &p1, const pair<size_t, double> &p2) {
          return p1.second < p2.second;
        });
    if (chosen_move != nullptr) *chosen_move = p->first;
    return p->second;
  }
}

}  // namespace c4
