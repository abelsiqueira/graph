#include <iostream>
#include "graph.h"

int main () {
  Graph<int, int> G;
  size_t n = 5;
  int x[n];

  for (size_t i = 0; i < n; i++)
    x[i] = 1;
  G.create(n, x);
  for (size_t i = 0; i < n; i++)
    for (size_t j = i+1; j < n; j++)
      if (i != j)
        G.addArc(i, j, i+j*n);

  for (size_t i = 0; i < n; i++) {
    for (size_t j = 0; j <= i; j++) {
      if (G.getArcPointer(i,j) != 0)
        return 1;
    }
    for (size_t j = i+1; j < n; j++) {
      if (G.getArcPointer(i,j)->info != i+j*n)
        return 1;
    }
  }

  return 0;
}
