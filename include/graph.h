#ifndef graph_h
#define graph_h

#include <cstdlib>
#include <fstream>

enum graph_status { gr_ok = 0, gr_not_init = 1 };

template <typename NodeType, typename ArcType>
class Graph {
  private:
    class ArcPointer {
      public:
        ArcPointer (ArcType _info = 0, ArcPointer *n = 0, size_t en = 0,
            size_t sn = 0) : info(_info), next(n), endNode(en),
            startNode(sn) { };
        ~ArcPointer () { };
        ArcType info;
        ArcPointer *next;
        size_t endNode;
        size_t startNode;

        //Methods
        ArcPointer *getLast () {
          if (next == 0) return this; else return next->getLast(); };
    };
  public:
    Graph<NodeType, ArcType> () : status(gr_not_init), num_nodes(0),
        num_arcs(0), nodes(0), arcs(0) { };
    ~Graph<NodeType, ArcType> () {};

    void readGraph (const char *);
    void prettyPrint () const;
  private:
    int status;
    size_t num_nodes, num_arcs;
    NodeType *nodes;
    ArcPointer **arcs;
};

/* file example:
 * num_nodes num_arcs
 * node1_value
 * node2_value
 * ...
 * i j arcij_value
 */
template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::readGraph (const char *filename) {
  std::ifstream file(filename);
  file >> num_nodes >> num_arcs;
  nodes = new NodeType[num_nodes];
  arcs = new ArcPointer*[num_nodes];
  for (size_t i = 0; i < num_nodes; i++) {
    file >> nodes[i];
    arcs[i] = 0;
  }
  size_t from, to;
  ArcType info;
  for (size_t k = 0; k < num_arcs; k++) {
    file >> from >> to >> info;
    if (arcs[from] == 0)
      arcs[from] = new ArcPointer(info, 0, to, from);
    else
      arcs[from]->getLast()->next = new ArcPointer(info, 0, to, from);
  }
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::prettyPrint () const {
  std::cout << "Graph with " << num_nodes << " nodes and "
    << num_arcs << " arcs." << std::endl;
  for (size_t i = 0; i < num_nodes; i++) {
    std::cout << "Node " << i << ": " << nodes[i] << std::endl;
    ArcPointer* p = arcs[i];
    while (p != 0) {
      std::cout << i << "->" << p->endNode << ": " << p->info << std::endl;
      p = p->next;
    }
  }
}

#endif
