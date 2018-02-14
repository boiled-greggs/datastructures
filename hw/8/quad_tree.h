// ===================================================================
//
// We provide the Point class and the implementation of several
// QuadTree member functions for printing.  
//
// IMPORTANT: You should modify this file to add all of the necessary
// functionality for the QuadTree class and its helper classes: Node,
// DepthIterator, and BreadthIterator.
//
// ===================================================================

#ifndef quad_tree_h_
#define quad_tree_h_

#include <iostream>
#include <vector>
#include <cassert>


// ==============================================================
// ==============================================================
// A tiny templated class to store 2D coordinates.  This class works
// with number_type = int, float, double, unsigned char (a 1 byte=8
// bit integer), short (a 2 byte=16 bit integer).

template <class number_type>
class Point {
public:
  Point(const number_type& x_, const number_type& y_) : x(x_),y(y_) {}
  // REPRESENTATION
  number_type x;
  number_type y;
};

// a helper function to print Points to STL output stream
template <class number_type>
inline std::ostream& operator<<(std::ostream &ostr, const Point<number_type> &pt) {
  ostr << "(" << pt.x << "," << pt.y << ")";
  return ostr;
}

template <class number_type, class label_type>
class Node {
  public:
    Node(const label_type &lab, const Point<number_type> &pt_) : children(), label(lab), pt(pt_) {}

    // representation
    Node<number_type, label_type>* children[4];
    label_type label;
    Point<number_type> pt;
    Node<number_type, label_type>* parent;
};

template <class number_type, class label_type>
class DepthIterator {
public:
  DepthIterator(Node<number_type, label_type>* n = NULL) : ptr(n) {}

  // operators
  bool operator==(const DepthIterator &itr) {
    return ptr == itr.ptr; 
  }
  bool operator!=(const DepthIterator &itr) {
    return ptr != itr.ptr;
  }

  // checks first if any of the children are null, and goes to each of them
  // in order. if that doesn't work, we're at the bottom, so we have to find
  // which child we are, then go to the next child over if possible. if not,
  // it's time to go even higher in the tree until we can finally go to the
  // next child over again. if none of this is ever possible, then we're at
  // the end of the tree.
  DepthIterator operator++() {
    if (ptr->children[0] != NULL) {
      ptr = ptr->children[0];
      return *this;
    } else if (ptr->children[1] != NULL) {
      ptr = ptr->children[1];
      return *this;
    } else if (ptr->children[2] != NULL) {
      ptr = ptr->children[2];
      return *this;
    } else if (ptr->children[3] != NULL) {
      ptr = ptr->children[3];
      return *this;
    }
    int child_num = -1;
    for (int i = 0; i < 4; i++) {
      if (ptr->parent->children[i] == ptr) {
        child_num = i;
        break;
      }
    }
    for (int i = child_num+1; i != -1 && i < 4; i++) {
      if ( ptr->parent->children[i] != NULL ) {
        ptr = ptr->parent->children[i];
        return *this;
      }
    }
    Node<number_type, label_type>* temp = ptr->parent;
    while( temp != NULL) {
      child_num = -1;
      for (int i = 0; i < 4; i++) {
        if (temp->parent != NULL) {
          if (temp->parent->children[i] == temp) {
            child_num = i;
            break;
          }
        }
      }
      if ( child_num != 3 && child_num != -1) {
        for(int i=child_num+1; i!=-1 && i<4; i++) {
          if(temp->parent->children[i] != NULL) {
            ptr = temp->parent->children[i];
            return *this;
          }
        }
      }
      temp = temp->parent;
      if (temp == NULL) break;
    }
    ptr = NULL;
    return *this;
  }
  DepthIterator operator++(int) { DepthIterator temp(*this); ++(*this); return temp; }
  const Point<number_type>& operator*() const { return ptr->pt; }
  
  // more info
  const label_type getLabel() const { return ptr->label; }
  const int getDepth() const {
    int depth = -1;
    Node<number_type, label_type>* tmp = ptr;
    while (tmp != NULL) {
      tmp = tmp->parent;
      ++depth;
    }
    return depth;
  }
private:
  Node<number_type, label_type>* ptr;
  
};

template <class number_type, class label_type>
class BreadthIterator {
public:
  BreadthIterator(Node<number_type, label_type>* n = NULL, int height = 0) : ptr(n), level(height+1), in_row_count(0), count(0)  { prev.push_back(ptr); }
  
  // operators
  bool operator==(const BreadthIterator &itr) {
    return ptr == itr.ptr; 
  }
  bool operator!=(const BreadthIterator &itr) {
    return ptr != itr.ptr;
  }
  
  // much more complicated than depth. makes a vector of the elements
  // in the row, then draws from that iteratively until there are no
  // more. makes a new vector for the next row down. once this is not
  // possible it returns the end pointer.
  BreadthIterator operator++() {
    bool flag = false;
    if (count != 0) {
      ptr = prev[in_row_count];
      ++in_row_count;
      flag = true;
    } else if (count > level) {
      level = 0; count = 0; in_row_count = 0;
      ptr = NULL;
      std::vector<Node<number_type, label_type>* > v;
      v.push_back(ptr);
      prev = v;
      return *this;
    }
    std::vector< Node<number_type, label_type>* > check_vec;
    if (in_row_count == prev.size() || count == 0) {
      std::vector< Node<number_type, label_type>* > temp(prev);
      check_vec = temp;
      prev.clear();
      in_row_count = 0;
      count += 1;
      for (unsigned int i = 0; i < temp.size(); i++) {
        for (int j = 0; j < 4; j++) {
          if (temp[i]->children[j] != NULL)
            prev.push_back(temp[i]->children[j]);
        }
      }
    }
    if (!flag) {
      ptr = prev[in_row_count];
      in_row_count++;
    }
    if (prev.size() != 0) 
      return *this;
    else if (prev.size() == 0) { 
      Node<number_type, label_type>* tmp = ptr->parent;
      int child_num = -1;
      bool last_node = true;
      while (tmp->parent != NULL) {
        bool more_children = false;
        for (int i = 0; i < 4; ++i) {
          if (tmp->children[i] == ptr) {
            child_num = i;
          }
          if (child_num > -1 && i < 3) {
            if (tmp->children[i+1] != NULL) {
              more_children = true;
            }
          }
        }
        if (child_num != 3 && more_children == true) {
          last_node = false;
          break;
        } else if (more_children == false && count == level) { 
          count++;
          return *this;
          break;
        } else {
          tmp = tmp->parent;
        }
      }
      if (last_node) return *this;
      else {
        level = 0; count = 0; in_row_count = 0;
        ptr = NULL;
        std::vector<Node<number_type, label_type>* > v;
        v.push_back(ptr);
        prev = v;
        return *this;
      }
    }
    return *this;
  }
  BreadthIterator operator++(int) { BreadthIterator temp(*this); ++(*this); return temp; }
  const Point<number_type>& operator*() const { return ptr->pt; }
  
  const label_type getLabel() const { return ptr->label; }
  // travel to the top of the tree and count how many nodes you pass
  const int getDepth() const {
    int depth = -1;
    Node<number_type, label_type>* tmp = ptr;
    while (tmp != NULL) {
      tmp = tmp->parent;
      ++depth;
    }
    return depth;
  }
  Node<number_type, label_type>* ptr;
  int level;
  int in_row_count;
  int count;
  std::vector< Node<number_type, label_type>* > prev;
private:
  
};

template <class number_type, class label_type>
class QuadTree {
public:
  // constructor & destructor
  QuadTree() : size_(0), height_(-1), root_(NULL)  {}
  QuadTree( const QuadTree &qtree ) : size_(qtree.size_), height_(qtree.height_) { root_ = this->copy(qtree.root_, NULL); }
  QuadTree& operator= ( const QuadTree &qtree ) { destroy_tree(root_); size_ = qtree.size_; height_ = qtree.height_; root_ = this->copy(qtree.root_, NULL); return *this; }
  ~QuadTree() { destroy_tree(root_); root_ = NULL; }
  
  // typedef and friend iterators so they can access the private members
  typedef DepthIterator<number_type, label_type> iterator;
  typedef BreadthIterator<number_type, label_type> bf_iterator;
  friend class DepthIterator<number_type, label_type>;
  friend class BreadthIterator<number_type, label_type>;
  
  int size() const { return size_; }
  int height() const { return height_; }

  std::pair<iterator, bool> insert( const Point<number_type> &pt, const label_type &label ) {
    return insert( pt, label, root_, root_, 0 ); }
  iterator find(number_type x,  number_type y) { return find(x, y, root_); }
  
  iterator begin() { return iterator(root_); }
  iterator end() { return iterator(); }

  bf_iterator bf_begin() { return bf_iterator(root_, height_); }
  bf_iterator bf_end() { return bf_iterator(NULL); }
  

private:
  int size_;
  int height_;
  Node<number_type, label_type>* root_;

  void destroy_tree(Node<number_type, label_type>* n) {
    if (n == NULL)
      return;
    for (int i = 0; i < 4; i ++)
      destroy_tree(n->children[i]);
    delete n;
  }
  
  Node<number_type, label_type>* copy(Node<number_type, label_type>* old_root, Node<number_type, label_type>* parent) {
    if (old_root == NULL)
      return NULL;
    Node<number_type, label_type>* ans = new Node<number_type, label_type>(old_root->label, old_root->pt);
    ans->pt = old_root->pt;
    ans->label = old_root->label;
    ans->children[0] = copy(old_root->children[0], ans);
    ans->children[1] = copy(old_root->children[1], ans);
    ans->children[2] = copy(old_root->children[2], ans);
    ans->children[3] = copy(old_root->children[3], ans);
    ans->parent = parent;
    return ans;
  }


  // insert returns iterator and a bool in a pair
  std::pair<iterator, bool> insert(const Point<number_type> &pt, const label_type &label, 
      Node<number_type, label_type>* &current, Node<number_type, label_type>* &parent, int height) {
    // get to a NULL pointer means it's the right place to insert
    if (current == NULL) {
      current = new Node<number_type, label_type> (label, pt);
      if (height >= 1) current->parent = parent;
      else current->parent = NULL;
      ++size_;
      if (height > height_) height_ = height;
      return std::make_pair(iterator(current), true);
    }
    if (pt.x == current->pt.x && pt.y == current->pt.y) {
      return std::make_pair(iterator(current), false);
    }
    
    // find the right child to pass to the recursive insert call
    int quadrant = -1;
    if (pt.x < current->pt.x && pt.y < current->pt.y)
      quadrant = 0;
    else if (pt.x > current->pt.x && pt.y < current->pt.y)
      quadrant = 1;
    else if (pt.x < current->pt.x && pt.y > current->pt.y)
      quadrant = 2;
    else if (pt.x > current->pt.x && pt.y > current->pt.y)
      quadrant = 3;
    
    return insert(pt, label, current->children[quadrant], current, height+1);

  }

  // find returns iterator pointing to node of tree with that point
  iterator find(number_type x, number_type y, Node<number_type, label_type>* n) {
    if (n == NULL) {
      return iterator(NULL);
    }
    if (n->pt.x == x && n->pt.y == y) {
      return iterator(n);
    }
    int quadrant = -1;
    if (x < n->pt.x && y < n->pt.y)
      quadrant = 0;
    else if (x > n->pt.x && y < n->pt.y)
      quadrant = 1;
    else if (x < n->pt.x && y > n->pt.y)
      quadrant = 2;
    else if (x > n->pt.x && y > n->pt.y)
      quadrant = 3;

    return find(x, y, n->children[quadrant]);
  }

public:
// ==============================================================
// PROVIDED CODE : QUAD TREE MEMBER FUNCTIONS FOR PRINTING
// ==============================================================

// NOTE: this function only works for quad trees with non negative
// integer coordinates and char labels

// NOTE2: this function assumes that no two points have the same x
// coordinate or the same y coordinate.

// plot driver function
// takes in the maximum x and y coordinates for these data points
// the optional argument draw_lines defaults to true
void plot(int max_x, int max_y, bool draw_lines=true) const {
  // allocate blank space for the center of the board
  std::vector<std::string> board(max_y+1,std::string(max_x+1,' '));
  // edit the board to add the point labels and draw vertical and
  // horizontal subdivisions
  plot(root_,board,0,max_x,0,max_y,draw_lines);
  // print the top border of the plot
  std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
  for (int i = 0; i <= max_y; i++) {
    // print each row of the board between vertical border bars
    std::cout << "|" << board[i] << "|" << std::endl;
  }
  // print the top border of the plot
  std::cout << "+" << std::string(max_x+1,'-') << "+" << std::endl;
}

// actual recursive function for plotting
void plot(Node<number_type,label_type> *p, std::vector<std::string> &board,
          int x_min, int x_max, int y_min, int y_max, bool draw_lines) const {
  // base case, draw nothing if this node is NULL
  if (p == NULL) return;
  // check that the dimensions range of this node make sense
  assert (x_min >= 0 && x_min <= x_max);
  assert (y_min >= 0 && y_min <= y_max);
  assert (board.size() >= y_max);
  assert (board[0].size() >= x_max);
  // verify that the point stored at this node fits on the board
  assert (p->pt.y >= 0 && p->pt.y < board.size());
  assert (p->pt.x >= 0 && p->pt.x < board[0].size());
  // draw the vertical and horizontal bars extending across the
  // range of this node
  if (draw_lines) {
    for (int x = x_min; x <= x_max; x++) {
      board[p->pt.y][x] = '-';
    }
    for (int y = y_min; y <= y_max; y++) {
      board[y][p->pt.x] = '|';
    }
  }
  // draw this label
  board[p->pt.y][p->pt.x] = p->label;
  // recurse on the 4 children
  plot(p->children[0],board,x_min ,p->pt.x-1,y_min ,p->pt.y-1,draw_lines);
  plot(p->children[1],board,p->pt.x+1,x_max ,y_min ,p->pt.y-1,draw_lines);
  plot(p->children[2],board,x_min ,p->pt.x-1,p->pt.y+1,y_max ,draw_lines);
  plot(p->children[3],board,p->pt.x+1,x_max ,p->pt.y+1,y_max ,draw_lines);
}


// ==============================================================

// prints all of the tree data with a pre-order (node first, then
// children) traversal of the tree structure

// driver function
void print_sideways() const { print_sideways(root_,""); }

// actual recursive function
void print_sideways(Node<number_type,label_type>* p, const std::string &indent) const {
  // base case
  if (p == NULL) return;
  // print out this node
  std::cout << indent << p->label << " (" << p->pt.x << "," << p->pt.y << ")" << std::endl;
  // recurse on each of the children trees
  // increasing the indentation
  print_sideways(p->children[0],indent+"  ");
  print_sideways(p->children[1],indent+"  ");
  print_sideways(p->children[2],indent+"  ");
  print_sideways(p->children[3],indent+"  ");
}

// ==============================================================
// ==============================================================
};

#endif
