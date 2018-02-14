#include <string>
#include <iostream>
#include <cassert>
#include <cmath>
#include "graph.h"


// ====================================================================================

Point::Point(int x_, int y_) : x(x_),y(y_) {
  // Points must have positive coordinates
  assert (x_ >= 0);
  assert (y_ >= 0);
}

// helper function for printing Points
std::ostream& operator<<(std::ostream &ostr, const Point &p) {
  ostr << "(" << p.get_x() << "," << p.get_y() << ")";
  return ostr;
}

// ====================================================================================

Edge::Edge(const Point &a_, const Point &b_) : a(a_),b(b_) {
  // Edges must be horizontal or vertical
  assert ((a_.get_x() == b_.get_x() && a_.get_y() != b_.get_y()) ||
          (a_.get_x() != b_.get_x() && a_.get_y() == b_.get_y()));
}

// ====================================================================================

Node::Node(const Point &p, int n) : pt(p),num_paths(n),num_left(n) {
  up = down = left = right = NULL;
  // Nodes/islands must have at least one Edge/bridge.  At most 2
  // Edges/bridges can connect a pair of Nodes/islands.  Edges/bridges
  // may only run horizontal or vertical and cannot cross other
  // Edges/bridges.  This a Node/island can support at most 8 bridges.
  assert (n >= 1 && n <= 8);
}

// ====================================================================================

// helper function for printing Edges
std::ostream& operator<<(std::ostream &ostr, const Edge &e) {
  ostr << e.get_a() << "," << e.get_b();
  return ostr;
}

// ====================================================================================

Graph::Graph() {
  // We track the maximum dimensions of the graph.
  max_x = 0;
  max_y = 0;
}


void Graph::addNode(const Point &p, int n) {
  // Incrementally track the maximum dimensions of the graph.
  max_x = std::max(p.get_x(),max_x);
  max_y = std::max(p.get_y(),max_y);
  total_edges += n;
  nodes.push_back(Node(p,n));
}


void Graph::addEdge(const Point &a, const Point &b) {
  assert (a.get_x() <= max_x);
  assert (a.get_y() <= max_y);
  assert (b.get_x() <= max_x);
  assert (b.get_y() <= max_y);
  edges.push_back(Edge(a,b));
}

// find the neighbors of each node in the graph. this is a little
// on the ~computatationally expensive~ side of things but at least
// you don't have to do it over and over again later now
void Graph::addNeighbors() {
  edges_left = 0;
  int total_left = 0;
  for (int i = 0; i < nodes.size(); ++i) {
    total_left += nodes[i].num_left;
    int x = nodes[i].pt.x; int y = nodes[i].pt.y;
    int up_dist, down_dist, left_dist, right_dist;
    up_dist = down_dist = max_y;
    left_dist = right_dist = max_x;
    for (int j = 0; j < nodes.size(); ++j) {
      // horizontal neighbors
      if ( nodes[j].pt.y == y ) {
        if ( nodes[j].pt.x < x && abs(x-nodes[j].pt.x) <= left_dist ) {
          nodes[i].left = &nodes[j];
          nodes[i].left_ind = j;
          left_dist = abs(x - nodes[j].pt.x);
        } else if ( nodes[j].pt.x > x && abs(x-nodes[j].pt.x) <= right_dist ) {
          nodes[i].right = &nodes[j];
          nodes[i].right_ind = j;
          right_dist = abs(x-nodes[j].pt.x);
        }
      } 
      // vertical neighbors
      else if ( nodes[j].pt.x == x ) {
        if ( nodes[j].pt.y < y && abs(y-nodes[j].pt.y) <= down_dist ) {
          nodes[i].down = &nodes[j];
          nodes[i].down_ind = j;
          down_dist = abs(y-nodes[j].pt.y);
        } else if ( nodes[j].pt.y > y && abs(y-nodes[j].pt.y) <= up_dist ) {
          nodes[i].up = &nodes[j];
          nodes[i].up_ind = j;
          up_dist = abs(y-nodes[j].pt.y);
        }
      }
    }
  }
  // need to keep track of this for each new copy
  edges_left = total_left/2;
}


// solve
// recursively go through nodes of the Graph, checking if bridges are possible
// in each direction, and then adding edges, changing values, and calling again
// until there are no edges left. when there are no bridges left to add, 
// the current copy is a solution and thus is added to solutions.
bool Graph::solve(std::vector<Graph> &solutions, Node n, int i, Graph scratch) {
  // base case for no edges left to add
  if (scratch.edges_left == 0) {
    solutions.push_back(scratch);
    return true;
  } else if (n.num_left > 0) {
    if (n.up != NULL) {
      if (n.up->num_left > 0) {
        scratch.addNeighbors();
        scratch.addEdge(scratch.nodes[i].pt, scratch.nodes[i].up->pt);
        scratch.nodes[i].num_left--; scratch.nodes[i].up->num_left--;
        scratch.edges_left--;
        int k = scratch.nodes[i].up_ind;
        if ( solve(solutions, scratch.nodes[k], k, scratch) ) return true;
      }
    }
    if (n.down != NULL) {
      if (n.down->num_left > 0) {
        scratch.addNeighbors();
        scratch.addEdge(scratch.nodes[i].pt, scratch.nodes[i].down->pt);
        scratch.nodes[i].num_left--; scratch.nodes[i].down->num_left--;
        scratch.edges_left--;
        int k = scratch.nodes[i].down_ind;
        if ( solve(solutions, scratch.nodes[k], k, scratch) ) return true;
      }
    }
    if (n.left != NULL) {
      if (n.left->num_left > 0) {
        scratch.addNeighbors();
        scratch.addEdge(scratch.nodes[i].pt, scratch.nodes[i].left->pt);
        scratch.nodes[i].num_left--; scratch.nodes[i].left->num_left--;
        scratch.edges_left--;
        int k = scratch.nodes[i].left_ind;
        if ( solve(solutions, scratch.nodes[k], k, scratch) ) return true;
      }
    }
    if (n.right != NULL) {
      if (n.right->num_left > 0) {
        scratch.addNeighbors();
        scratch.addEdge(scratch.nodes[i].pt, scratch.nodes[i].right->pt);
        scratch.nodes[i].num_left--; scratch.nodes[i].right->num_left--;
        scratch.edges_left--;
        int k = scratch.nodes[i].right_ind;
        if ( solve(solutions, scratch.nodes[k], k, scratch) ) return true;
      }
    }
  } else {
    bool found = false;
    int k = -1;
    while (!found) {
      ++k;
      if (scratch.nodes[k].num_left > 0) found = true;
    }
    if ( solve(solutions, scratch.nodes[k], k, scratch) ) return true;
    else return (solve(solutions, scratch.nodes[k+1], k+1, scratch));
  }
  return false;
}

// driver
void Graph::solve(std::vector<Graph> &solutions) {
  for (int i = 0; i < nodes.size(); ++i) {
    Graph scratch(*this);
    solve(solutions, scratch.nodes[i], i, scratch);
  }
}

void Graph::printSolution() const {
  std::cout << "Solution:" << std::endl;
  for (int i = 0; i < edges.size(); i++) {
    std::cout << edges[i] << std::endl;
  }
}


void Graph::printGraph() const {
  // a graph should have at least one node/island
  assert (nodes.size() > 1);
  // the dimensions of the board should be positive
  assert (max_x >= 0);
  assert (max_y >= 0);

  // allocate an empty/blank board, twice as big in each dimension so
  // we can draw lines between the nodes/islands.
  std::vector<std::string> board(2*max_y+1,std::string(2*max_x+1,' '));
  // mark all of the islands with their bridge count
  for (int i = 0; i < nodes.size(); i++) {
    const Point &pt = nodes[i].get_pt(); 
    std::string value = std::to_string(nodes[i].get_num_paths());
    board[2*pt.get_y()][2*pt.get_x()] = value[0];
  }

  // loop over all of the edges/bridges
  for (int i = 0; i < edges.size(); i++) {
    Point a = edges[i].get_a();
    Point b = edges[i].get_b();
    // determine the edge/edge direction
    int diff_x = b.get_x()-a.get_x();
    int diff_y = b.get_y()-a.get_y();
    if (diff_x > 0) diff_x = 1;
    if (diff_x < 0) diff_x = -1;
    if (diff_y > 0) diff_y = 1;
    if (diff_y < 0) diff_y = -1;

    // walk between the islands to draw the bridge
    int x = a.get_x()*2+diff_x;
    int y = a.get_y()*2+diff_y;
    while (x != b.get_x()*2 || y != b.get_y()*2) {
      if (diff_x == 0) {
        // vertical bridge
        assert (diff_y != 0);
        if (board[y][x] == '|') {
          // if we already have a bridge, draw a double vertical bridge
          board[y][x] = '#';
        } else {
          assert (board[y][x] == ' ');
          // otherwise draw a single vertical bridge
          board[y][x] = '|';        
        }
      } else {
        assert (diff_y == 0);
        // horizontal bridge
        if (board[y][x] == '-') {
          // if we already have a brige, draw a double horizontal bridge
          board[y][x] = '=';        
        } else {
          assert (board[y][x] == ' ');
          // otherwise draw a single horizontal bridge
          board[y][x] = '-';        
        }
      }
      x+=diff_x;
      y+=diff_y;
    }
  }

  // surround the board with a border of spaces
  char border = ' ';
  std::cout << std::string(board[0].size()+2,border) << std::endl;
  for (int i = board.size()-1; i >= 0; i--) {
    std::cout << border << board[i] << border << std::endl;
  }
  std::cout << std::string(board[0].size()+2,border) << std::endl;
}

// ====================================================================================
