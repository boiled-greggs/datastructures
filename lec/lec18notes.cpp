// --------------------------------------------------------------
// target output
// level 0:  4
// level 1:  2 6
// level 2:  1 3 5 7

void breadth_first_print( TreeNode<T>* root ) {
  if (root == NULL) return;
  int which_level = 0;                                             
  std::list<TreeNode<T>*> current_level;
  std::list<TreeNode<T>*> next_level;
  current_level.push_back(root);
  do {
    next_level.clear();
    cout << "level " << which_level << " :"
      while (!current_level.empty()) {
        TreeNode<T>* tmp = current_level.front();
        current_level.pop_front();
        std::cout << tmp->value << " ";
        if (tmp->left != NULL) {
          next_level.push_back(tmp->left);
        }
        if (tmp->right != NULL) {
          next_level.push_back(tmp->right);
        }
      }
    current_level = next_level;
    which_level++;
    std::cout << std::endl;
  } while (!next_level.empty());
}

// --------------------------------------------------------------

iterator & operator++() {
  /* discussed & implemented in Lecture 18 */
  if ( ptr_->right != NULL ) {
    // there is stuff in the right subtree
    // go right first
    ptr_ = ptr_->right;
    while (ptr_->left != NULL) {
      // go left as much as you can
      ptr_ = ptr_->left;
    }
  } else {
    // go upwards along right branches...  stop before the first left
    while (ptr_->parent != NULL && ptr_->parent->right == ptr_) { 
      ptr_ = ptr_->parent; 
    }
    // go up one more time
    // NOTE: this might end in NULL -- then we're at end()
    ptr_ = ptr_->parent;
  }     
  return *this;
}

// --------------------------------------------------------------
