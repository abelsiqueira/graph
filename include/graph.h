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
        ArcPointer (ArcType _info = 0, ArcPointer *n = 0, size_t sn = 0,
            size_t en = 0) : info(_info), next(n), start_node(sn),
            end_node(en) { };
        ~ArcPointer () { destroy(); };
        ArcType info;
        ArcPointer *next;
        size_t start_node;
        size_t end_node;

        //Methods
        ArcPointer *getLast () {
          if (next == 0) return this; else return next->getLast(); };
        void destroy () {
          if (next != 0)
            next->destroy();
        }
    };
  public:
    Graph<NodeType, ArcType> () : status(gr_not_init), num_nodes(0),
        num_arcs(0), nodes(0), arcs(0) { };
    ~Graph<NodeType, ArcType> () { destroy(); };

    void readGraph (const char *);
    void prettyPrint () const;
  private:
    int status;
    size_t num_nodes, num_arcs;
    NodeType *nodes;
    ArcPointer **arcs;
  private:
    void init (size_t nn) {
      if (nodes != 0 || arcs != 0)
        throw("ERROR: Graph already initialized");
      nodes = new NodeType[nn];
      arcs = new ArcPointer*[nn];
      for (size_t i = 0; i < nn; i++) {
        ArcType info = ArcType();
        arcs[i] = new ArcPointer(info, 0, i, nn);
      }
    }
    void destroy () {
      if (nodes != 0)
        delete []nodes;
      for (size_t i = 0; i < num_nodes; i++) {
        arcs[i]->destroy();
      }
      if (arcs != 0)
        delete []arcs;
    }
    void addArc (ArcType info, size_t from, size_t to) {
      ArcPointer *arc = new ArcPointer(info, 0, from, to);
      ArcPointer *p = arcs[from], *q = arcs[from];
      while (p->end_node < to) {
        q = p;
        p = p->next;
      }
      if (p == arcs[from])
        arcs[from] = arc;
      else
        q->next = arc;
      arc->next = p;
    }
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
  init(num_nodes);
  for (size_t i = 0; i < num_nodes; i++)
    file >> nodes[i];
  size_t from, to;
  ArcType info;
  for (size_t k = 0; k < num_arcs; k++) {
    file >> from >> to >> info;
    this->addArc(info, from, to);
  }
}

template <typename NodeType, typename ArcType>
void Graph<NodeType, ArcType>::prettyPrint () const {
  std::cout << "Graph with " << num_nodes << " nodes and "
    << num_arcs << " arcs." << std::endl;
  for (size_t i = 0; i < num_nodes; i++) {
    std::cout << "Node " << i << ": " << nodes[i] << std::endl;
    ArcPointer* p = arcs[i];
    while (p->next != 0) {
      std::cout << i << "->" << p->end_node << ": " << p->info << std::endl;
      p = p->next;
    }
  }
}

#endif
