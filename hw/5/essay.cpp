#include <iostream>

#include "essay.h"

Essay::Essay() {
  head_ = NULL;
  tail_ = NULL;
  backup_head_ = NULL;
  backup_tail_ = NULL;
  size_ = 0;
}

// first destroy elements in backup which have been removed.
// then, go through remaining essay and delete all nodes
void Essay::destroy_essay() {
  iterator itr = backup_begin();
  if (backup_head_ != NULL) {
    while (itr.ptr_->backup_next_ != NULL) {
  std::cout << "here" << std::endl;
      iterator tmp = itr;
      ++tmp;
      if (itr.ptr_->removed_ == true) delete itr.ptr_;
      itr = tmp;
    }
    if (backup_tail_->removed_ == true) {
      delete backup_tail_;
    }
  }
  iterator itr2 = begin();
  for (int i = 0; i < size_; ++i) {
    iterator tmp2 = itr2;
    ++tmp2;
    delete itr2.ptr_;
    itr2 = tmp2;
  }

}

// set the size equal to the copied size. 
void Essay::copy(const Essay& e) {
  /*
  this->size_ = e.size_;
  if (e.head_ != NULL) {
    this->head_ = new Node;
    this->tail_ = new Node;
    this->head_->value_ = e.head_->value_;
    this->tail_->value_ = e.tail_->value_;
    Node* tmp = head_;
    for (int i = 0; i < size_; ++i) {
      
    }
  }
  */
}

Essay& Essay::operator=(const Essay &e) {
  destroy_essay();
  copy(e);
  return *this;
}

// create new node, then if head is NULL, make it the head
// otherwise, add it to the back and have tail point to it
// changing the old tail_'s next pointer to the new node
void Essay::push_back(const std::string &word) {
  ++size_;
  Node* new_word = new Node(word);
  new_word->next_ = NULL;
  new_word->added_ = true;
  if (head_ == NULL) {
    head_ = new_word;
    tail_ = new_word;
  } else {
    tail_->next_ = new_word;
    new_word->prev_ = tail_;
    tail_ = new_word;
  }
}

// create a new node. if essay empty, head points to this
// node. if not, set this new node as the head and have the
// old head's prev pointer point to it.
void Essay::push_front(const std::string &word) {
  ++size_;
  Node* new_word = new Node(word);
  new_word->prev_ = NULL;
  new_word->added_ = true;
  if (head_ == NULL) {
    head_ = new_word;
    tail_ = new_word;
  } else {
    head_->prev_ = new_word;
    new_word->next_ = head_;
    head_ = new_word;
  }
}

// if there is no element in the list, push_front
// otherwise, make a new added node, have new node's next pointer
// point to the iterator node, and set the new node's prev equal
// to the prev of the iterator node, the setting the iterator node's
// prev pointer to the new node.
list_iterator Essay::insert(iterator itr, const std::string &word) {
  if (head_ == NULL) {
    push_front(word);
  } else {
    Node *nn = new Node(word);
    nn->added_ = true;
    nn->next_ = itr.ptr_;
    nn->prev_ = itr.ptr_->prev_;
    itr.ptr_->prev_->next_ = nn;
    itr.ptr_->prev_ = nn;
    ++size_;
    return list_iterator(nn, itr.backup_);
  }
}

// first checks if size is 1. if it is, and there is no backup,
// delete the node. if the node has not been backed up, delete 
// the erased node. If the size is more than one, then either
// pop front for the head, pop back for the tail, or rearrange
// pointers so the previous node's next is pointing over the
// erased node, and the next's node's prev is pointing over
// behind the erased node.
list_iterator Essay::erase(iterator itr) {
  if (size_ == 1) {
    itr.ptr_->removed_ = true;
    if (backup_head_ == NULL) delete itr.ptr_;
    else {
      head_ = NULL;
      tail_ = NULL;
    }
    --size_;
  } else if (itr.ptr_ == head_) {
    pop_front();
  } else if (itr.ptr_ == tail_) {
    pop_back();
  } else if (itr.ptr_!= NULL) {
    itr.ptr_->removed_ = true;
    itr.ptr_->prev_->next_ = itr.ptr_->next_;
    itr.ptr_->next_->prev_ = itr.ptr_->prev_;
    iterator itr2 = itr.ptr_->prev_;
    itr.ptr_->next_ = NULL;
    itr.ptr_->prev_ = NULL;
    --size_;
    if (backup_head_ == NULL || itr.ptr_->added_) delete itr.ptr_;
    return itr2.ptr_->next_;
  } else {
    return itr.ptr_;
  }
}

// remove the tail. make a temp node to store tail info,
// then have the tail's prev's next be NULL and change tail
// to old tail's prev. then delete temp to delete the old tail,
// if it hasn't been backed up.
// if the size is one then the same basics apply but tail and head
// are both set to NULL as the node is removed.
void Essay::pop_back() {
  if (tail_ != NULL && size_ > 1) {
    tail_->removed_ = true;
    Node* tmp = tail_;
    tail_->prev_->next_ = NULL;
    tail_ = tail_->prev_;
    --size_;
    if (backup_head_ == NULL) delete tmp;
  } else if ( tail_ != NULL) {
    if (backup_head_ == NULL) delete tail_;
    else {
      tail_->removed_ = true;
    }
    tail_ = NULL;
    head_ = NULL;
    --size_;
  }
}

// same principle as pop front.
// rearrange the pointers so the new head is old head's next,
// then if it hasn't been backed up, delete the old head.
// if the size is 0 set head and tail to NULL
void Essay::pop_front() {
  if (head_ != NULL && size_ > 1) {
    head_->removed_ = true;
    Node* tmp = head_;
    head_->next_->prev_ = NULL;
    head_ = head_->next_;
    if (backup_head_ == NULL) delete tmp;
    --size_;
  } else if (head_ != NULL) {
    if (backup_head_ == NULL) delete head_;
    else {
      head_->removed_ = true;
    }
    head_ = NULL;
    tail_ = NULL;
    --size_;
  }
}

// iterate through the whole list and if the node
// has added=true, then add to a counter.
// then return the counter at the end
int Essay::num_added() {
  iterator itr = begin();
  int added = 0;
  while (itr != end()) {
    if (itr.ptr_->added_) ++added;
    ++itr;
  }
  return added;
}

// iterate through the whole essay and if the node
// has removed= true, then add to a counter.
// then return the counter at the end
int Essay::num_removed() {
  iterator itr = backup_begin();
  int removed = 0;
  while (itr != backup_end()) {
    if (itr.ptr_->removed_) ++removed;
    ++itr;
  }
  return removed;
}

// backup.
// if it has been backed up, then delete all the
// nodes with removed = true from the old backup
// then set the backup head and tail to the current
// head and tail, iterate through essay and copy nodes,
// setting added to false along the way
void Essay::backup() {
  if (backup_head_ != NULL) {
    iterator itr = backup_begin();
    while (itr.ptr_->backup_next_ != NULL) {
      iterator tmp = itr;
      ++tmp;
      if (itr.ptr_->removed_ == true) delete itr.ptr_;
      itr = tmp;
    }
  }
  backup_head_ = head_;
  backup_tail_ = tail_;
  iterator itr = begin();
  for (int i = 0; i < size_; ++i) {
    itr.ptr_->backup_next_ = itr.ptr_->next_;
    itr.ptr_->backup_prev_ = itr.ptr_->prev_;
    itr.ptr_->added_ = false;
    ++itr;
  }
}

// revert.
// if the current list is not empty, iterate through
// and find nodes that were added since last backup,
// deleting them and adjusting size. Then, set head
// and tail to backup head and tail, iterate through
// the backup essay, and set all pointers of current to match that
// of backup, setting removed to false along the way
void Essay::revert() {
  if (head_ != NULL) {
    iterator itr = begin();
    int size = size_;
    for (int i = 0; i < size; ++i) {
      iterator tmp = itr;
      ++tmp;
      if (itr.ptr_->added_) {
        delete itr.ptr_;
        --size_;
      }
      itr = tmp;
    }
  }
  head_ = backup_head_;
  tail_ = backup_tail_;
  iterator itr = backup_begin();
  if (backup_head_ != NULL) {
    while (itr.ptr_->backup_next_ != NULL) {
      itr.ptr_->next_ = itr.ptr_->backup_next_;
      itr.ptr_->prev_ = itr.ptr_->backup_prev_;
      if (itr.ptr_->removed_) ++size_;
      itr.ptr_->removed_ = false;
      ++itr;
    }
    itr.ptr_->next_ = itr.ptr_->backup_next_;
    itr.ptr_->prev_ = itr.ptr_->backup_prev_;
    if (itr.ptr_->removed_) ++size_;
    itr.ptr_->removed_ = false;
  }
}

// splice.
// first, go through the essay and find the indicies of the begin,
// end, and destination iterators. then if the indicies satisfy the 
// rules for splicing, set the node before begin to point to the end
// node, the begin node prev to point to the destination prev, the node
// before destination to point to begin, the destination prev to point 
// to the node before end, the node before end to point to destination,
// and the end node prev to point to what was before begin. This is 
// **easier to draw**. if the rules weren't satisfied, errors are printed.
bool Essay::splice(iterator begin_splice, iterator end_splice, iterator destination) {
  int b_ind = 0; int e_ind = 0; int dest_ind = 0;
  iterator check_itr = begin();
  for (int i = 0; i < size_; ++i) {
    if (check_itr == begin_splice) b_ind = i;
    if (check_itr == end_splice) e_ind = i;
    if (check_itr == destination) dest_ind = i;
    ++check_itr;
  }
  if ( (b_ind < e_ind && e_ind < dest_ind) || (dest_ind < b_ind && b_ind < e_ind) ) {
    Node* tmp = begin_splice.ptr_->prev_;
    begin_splice.ptr_->prev_->next_ = end_splice.ptr_;
    begin_splice.ptr_->prev_ = destination.ptr_->prev_;
    destination.ptr_->prev_->next_ = begin_splice.ptr_;
    destination.ptr_->prev_ = end_splice.ptr_->prev_;
    end_splice.ptr_->prev_->next_ = destination.ptr_;
    end_splice.ptr_->prev_ = tmp;
    return true;
  } else if (b_ind < dest_ind && dest_ind < e_ind) {
    std::cerr << "ERROR (splice): destination cannot be between splice_begin and splice_end\n";
    return false;
  } else if (e_ind <= b_ind) {
    std::cerr << "ERROR (splice): splice_end cannot precede splice_begin\n";
    return false;
  }
  return false;
}

