#include "graph.h"

template <typename T>
Graph<T>::Graph() {
  status = gr_not_init;
  num_nodes = 0;
  info = 0;
}
