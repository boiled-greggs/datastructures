#include <vector>

// ====================================================================================
// A Point is just a 2D coordinate.

class Point {
public:
  Point(int x_, int y_); // accessors 
  int get_x() const { return x; }
  int get_y() const { return y; }
  int x;
  int y;
private:
  // representation
};

// helper function for printing Points
std::ostream& operator<<(std::ostream &ostr, const Point &p);

// ====================================================================================
// An Edge is a vertical or horizontal line segment connecting 2 points.

class Edge {
public:
  // constructor
  Edge(const Point &a_, const Point &b_);
  // accessors
  const Point& get_a() const { return a; }
  const Point& get_b() const { return b; }
private:
  // representation
  Point a;
  Point b;
};

// helper function for printing Edges
std::ostream& operator<<(std::ostream &ostr, const Edge &e);

// ====================================================================================
// A Node is a Point with a count of the number of Edges that should touch it.

class Node {
public:
  Node(const Point &p, int n);
  // accessors
  const Point& get_pt() const { return pt; }
  int get_num_paths() const { return num_paths; }
  
  friend class Graph;
  Point pt;
  // public pointer nodes to make this easier
  Node* up;
  Node* down;
  Node* left;
  Node* right;
  int up_ind, down_ind, left_ind, right_ind;
private:
  int num_paths;
  int num_left;
};

// ====================================================================================
// A Graph is a collection of Nodes and Edges that can be printed.

class Graph {
public:
  // constructor
  Graph();
  // modifiers
  void addNode(const Point &p, int n);
  void addEdge(const Point &a, const Point &b);
  void addNeighbors();
  void print_nay();
  bool solve(std::vector<Graph> &solutions, Node n, int i, Graph scratch);
  void solve(std::vector<Graph> &solutions);

  // print helper functions
  void printSolution() const;
  void printGraph() const;
private:
  // representation
  int max_x;
  int max_y;
  std::vector<Node> nodes;
  std::vector<Edge> edges;
  int edges_left;
  int total_edges;
};

// ====================================================================================
