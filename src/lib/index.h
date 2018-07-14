#ifndef C4_LIB_INDEX_H
#define C4_LIB_INDEX_H

#include <cassert>
#include <cstddef>

namespace c4 {

template <typename TAG, size_t SZ>
class IndexRange;

template <typename TAG, size_t SZ>
class Index {
 public:
  constexpr static size_t size() { return SZ; }

  Index() : Index(0) {}
  explicit Index(size_t val) : index_(val) { assert(index_ < SZ); }
  size_t to_size_t() const { return index_; }

  bool operator==(Index rhs) const { return index_ == rhs.index_; }
  bool operator!=(Index rhs) const { return !(*this == rhs); }

  Index operator+(size_t sz) const { return Index(index_ + sz); }
  Index operator+(Index rhs) const { return operator+(rhs.to_size_t()); }
  friend Index operator+(size_t lhs, Index rhs) { return rhs + lhs; }

  IndexRange<TAG, SZ> range() { return IndexRange<TAG, SZ>(*this); }
  IndexRange<TAG, SZ> range_to(Index e) {
    return IndexRange<TAG, SZ>(*this, e);
  }

 private:
  size_t index_;
};

template <typename TAG, size_t SZ>
class IndexRange {
 public:
  using Idx = Index<TAG, SZ>;

  IndexRange(size_t size) : start_(size), end_(SZ) {}
  IndexRange(Idx b) : start_(b.to_size_t()), end_(SZ) {
    assert(start_ < SZ);
    assert(end_ <= SZ);
  };
  IndexRange(Idx b, Idx e) : start_(b.to_size_t()), end_(e.to_size_t()) {}

  IndexRange begin() const { return *this; }
  IndexRange end() const { return IndexRange(end_); }

  bool operator==(IndexRange rhs) const { return start_ == rhs.start_; }
  bool operator!=(IndexRange rhs) const { return !(*this == rhs); }
  Idx operator*() const { return Idx(start_); }
  IndexRange &operator++() {
    start_++;
    return *this;
  }

 private:
  size_t start_;
  size_t end_;
};

}  // namespace c4

#endif  // C4_LIB_INDEX_H
