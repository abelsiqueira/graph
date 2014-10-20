#ifndef graph_h
#define graph_h

#include <cstdlib>

enum graph_status { gr_ok = 0, gr_not_init = 1 };

template <typename T>
class Graph {
  public:
    Graph<T>();
    ~Graph<T>() {};
  private:
    int status;
    size_t num_nodes;
    T *info;
};

#endif
