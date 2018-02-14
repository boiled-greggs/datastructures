#ifndef _essay_h_
#define _essay_h_

class Node {
  public:
    Node() : next_(NULL), prev_(NULL), backup_next_(NULL), backup_prev_(NULL), 
      added_(false), removed_(false) {}
    Node(const std::string &str) : value_(str), next_(NULL), prev_(NULL), 
      backup_next_(NULL), backup_prev_(NULL), added_(false), removed_(false) {}
    void debug() const;

    std::string value_;
    Node* next_;
    Node* prev_;
    Node* backup_next_;
    Node* backup_prev_;
    bool added_;
    bool removed_;
};

class Essay;

class list_iterator {
  public:
    list_iterator(Node* p=NULL, bool backup=false) : ptr_(p), backup_(backup) {}
    
    std::string& operator*() { return ptr_->value_; }

    list_iterator &operator++() {
      if( backup_ == false ) ptr_ = ptr_->next_;
      else if (backup_ == true) ptr_ = ptr_->backup_next_;
      return *this;
    }
    list_iterator operator++(int) {
      list_iterator temp(*this);
      if ( backup_ == false ) ptr_ = ptr_->next_;
      else if (backup_ == true ) ptr_ = ptr_->backup_next_;
      return temp;
    }
    list_iterator& operator--() { // pre-decrement, e.g., --iter
      if ( backup_ == false ) ptr_ = ptr_->prev_;
      else if (backup_ == true ) ptr_ = ptr_->backup_prev_;
      return *this;
    }
    list_iterator operator--(int) { // post-decrement, e.g., iter--
      list_iterator temp(*this);
      if ( backup_ == false ) ptr_ = ptr_->prev_;
      else if ( backup_ == true ) ptr_ = ptr_->backup_prev_;
      return temp;
    }

    friend class Essay;

    bool operator==(const list_iterator& r) const {
      return ptr_ == r.ptr_; }
    bool operator!=(const list_iterator& r) const {
      return ptr_ != r.ptr_; }
  
    // debug
    void debug() const;

  private:
    Node* ptr_;
    bool backup_; 

};

class Essay {
  public:
    typedef list_iterator iterator; //SOMETHING;

    // constructors etc
    Essay();
    Essay(const Essay& e) { copy(e); }
    Essay& operator=(const Essay &e);
    ~Essay() { destroy_essay(); }
    
    // accessors etc
    int size() const { return size_; }
    bool empty() const { return head_ == NULL; }
    int num_added();
    int num_removed();
    void clear() { destroy_essay(); }
    
    // read/write access
    const std::string &front() const { return head_->value_; }
    std::string &front() { return head_->value_; }
    const std::string &back() const { return tail_->value_; }
    std::string &back() { return tail_->value_; }

    // modifiers
    void push_back(const std::string &word);
    void push_front(const std::string &word);
    void pop_front();
    void pop_back();
    
    // whole point of it
    void backup();
    void revert();
    bool splice(iterator begin_splice, iterator end_splice, iterator destination);

    // iterating
    iterator erase(iterator itr);
    iterator insert(iterator itr, const std::string &word);
    iterator begin() { return iterator(head_, false); }
    iterator end() { return iterator(NULL, false); }
    iterator backup_begin() { return iterator(backup_head_, true); }
    iterator backup_end() { return iterator(NULL, true); }
    
    // debug
    void debug() const;

  private:
    void copy(const Essay &old);
    void destroy_essay();

    Node *head_;
    Node *tail_;
    Node *backup_head_;
    Node *backup_tail_;
    int size_;
};








#endif
