#include <iostream>
#include "graph.h"

int main () {
  Graph<double, double> G;

  G.readGraph("ex01.gr");
  G.prettyPrint();

  return 0;
}
