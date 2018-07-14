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

using absl::optional;

double evaluate(Board *board) { return 0.0; }

MinimaxChooser::MinimaxResult MinimaxChooser::minimax(
    Board *board, size_t max_depth, double alpha, double beta,
    Board::Cell current_color) {
  // Red is always the maximizing color.
  bool maximizing = current_color == Board::RED;

  Board::Cell winner = FindWinOnBoard(board);
  if (winner != Board::INVALID) {
    //    if (chosen_move != nullptr) *chosen_move = -1;
    if (winner == Board::RED) {
      return make_pair(optional<ColIndex>{},
                       std::numeric_limits<double>::max());
    } else {
      return make_pair(optional<ColIndex>{},
                       std::numeric_limits<double>::lowest());
    }
  }

  Board::MoveList valid_moves;
  vector<MinimaxResult> candidates;
  board->ValidMoves(&valid_moves);

  if (valid_moves.empty()) {
    // It's a tie. There are no moves and no winner.
    return make_pair(optional<ColIndex>{}, 0);
  }

  if (max_depth == 0) {
    return make_pair(optional<ColIndex>{}, evaluate(board));
  }

  if (maximizing) {
    auto v = std::numeric_limits<double>::lowest();
    for (auto move : valid_moves) {
      board->Move(move, current_color);
      candidates.emplace_back(
          optional<ColIndex>(move),
          minimax(board, max_depth - 1, alpha, beta,
                  current_color == Board::RED ? Board::YELLOW : Board::RED)
              .second);
      auto p = candidates.back();
      board->Unmove(move);
      v = std::max(v, p.second);
      alpha = std::max(alpha, v);
      if (alpha >= beta) {
        break;
      }
    }
    //    auto s = absl::StrJoin(candidates, "|", [](std::string* out, auto pr)
    //    {
    //					    });
    //    D("red candidates($1): $0", s, max_depth);
    auto p = max_element(candidates.begin(), candidates.end(),
                         [](MinimaxResult const &p1, MinimaxResult const &p2) {
                           return p1.second < p2.second;
                         });
    return *p;
  } else {
    auto v = std::numeric_limits<double>::max();
    for (auto move : valid_moves) {
      board->Move(move, current_color);
      candidates.emplace_back(
          optional<ColIndex>(move),
          minimax(board, max_depth - 1, alpha, beta,
                  current_color == Board::RED ? Board::YELLOW : Board::RED)
              .second);
      auto p = candidates.back();
      board->Unmove(move);
      v = std::min(beta, p.second);
      beta = std::min(beta, v);
      if (alpha >= beta) {
        break;
      }
    }
    //    auto s = absl::StrJoin(candidates, "|", [](std::string* out, auto pr)
    //    {} ); D("yellow candidates($1): $0", s, max_depth);
    auto p = min_element(candidates.begin(), candidates.end(),
                         [](MinimaxResult const &p1, MinimaxResult const &p2) {
                           return p1.second < p2.second;
                         });
    return *p;
  }
}

}  // namespace c4
