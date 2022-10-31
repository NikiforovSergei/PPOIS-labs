

#ifndef __KITA_EDGE__
#define __KITA_EDGE__

#include <stdexcept>

template<typename T>
class Edge {
public:
  T a;
  T b;

  Edge() = default;
  Edge(T new_a, T new_b) : a(new_a), b(new_b) {}
  
  T& smaller_element() {
    return b < a ? b : a;
  }
  const T& smaller_element() const {
    return b < a ? b : a;
  }

  T& bigger_element() {
    return b < a ? a : b;
  }
  const T& bigger_element() const {
    return b < a ? a : b;
  }

  inline bool operator==(const Edge& ce) const {
    return ((a == ce.a && b == ce.b) || (a == ce.b && b == ce.a));
  }
  inline bool operator!=(const Edge& ce) const {
    return !(*this == ce);
  }
  inline bool operator<(const Edge& ce) const {
    auto e_smaller = smaller_element(), e_bigger = bigger_element();
    auto ce_smaller = ce.smaller_element(), ce_bigger = ce.bigger_element();

    if (e_smaller < ce_smaller) {
      return true;
    }
    if (ce_smaller < e_smaller) {
      return false;
    }
    if (e_bigger < ce_bigger) {
      return true;
    }

    return false;
  }
  inline bool operator>(const Edge& ce) const {
    return ce < *this;
  }
  inline bool operator<=(const Edge& ce) const {
    return !(*this > ce);
  }
  inline bool operator>=(const Edge& ce) const {
    return !(*this < ce);
  }
};

namespace std {
  template<typename T>
  struct hash<Edge<T>> {
    inline std::size_t operator()(const Edge<T>& e) const {
      return std::hash<T>()(e.smaller_element()) ^ (std::hash<T>()(e.bigger_element()) << 1);
    }
  };
}

#endif
