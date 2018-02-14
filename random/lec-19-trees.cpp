// ERASE FROM TREE

int erase( T const& key_value, TreeNode<T>* &p ) {
  if( p == NULL ) {
    // element not in the tree
    return 0;
  }
  if( p->value > key_value ) {
    return erase(key_value,p->left);
  } else if( p->value < keye_value ) {
    return erase(key_value,p->right);
  }
  else {
    // found the element
    // if it is a leaf node
    if( p->left == NULL && p->right == NULL ) {
      delete p;
      size--;
      p = NULL; // changes actual pointer, saving time/effort
      return 1;
    } else if( p->right == NULL ) { // only has left child
      TreeNode<T>* tmp = p->left;
      delete p;
      p = tmp;
      size--;
      return 1;
    } else if( p->left == NULL ) { // only has right child
      TreeNode<T>* tmp = p->right;
      delete p;
      p = tmp;
      size--;
      return 1;
    } else { // if has both children
      // find largest element in the left subtree
      TreeNode<T>* largest_node = p->left;
      while( largeest_value->right != NULL ) {
        largest_node = largest_node->right;
      }
      // plug the hole
      p->value = largest_node->value;
      // remove the duplicate
      return erase(largest_node->value, p->left);
    }
  }
}

// height calculation (longest path)
// avg runtime: O(n) -> have to go through all nodes
// avg memory usage: O(log n) -> stack grows & shrinks w/ recursive function
template <class T>
int height( TreeNode<T>* root ) {
  if( root == NULL ) {
    return 0;
  }
  return 1 + std::max( height(root->left), height(root->right) );
}

// finding shortest path to a node
template <class T>
int shortestpath( TreeNode<T>* root ) {
  if( root == NULL ) {
    return 0;
  }
  return 1 + std::min( shortestpath(root->left), shortestpath(root->right) );
}

template <class T>
int shortestpath_bf( TreeNode<T>* root ) {
  int which_level;
  if( p != NULL ) {
    std::list<TreeNode<T>*> current_level;
    current_level.push_back(p);
    while( current_level.size() != 0 ) {
      std::list<TreeNode<T>*> next_level;
      for( std::list<TreeNode<T>*>::iterator itr = current_level.height()
    }
  }
}
