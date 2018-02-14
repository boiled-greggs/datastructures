#ifndef _ds_hashset_h_
#define _ds_hashset_h_

#include <iostream>
#include <list>
#include <string>
#include <vector>

template <class KeyType, class HashFunc>
class ds_hashset {
private:
  typedef typename std::list<KeyType>::iterator hash_list_itr;

public:
  // iterator class
  class iterator {
  public:
    friend class ds_hashset;
  private:
    // rep
    ds_hashset* m_hs;
    int m_index;
    hash_list_itr m_list_itr;

    // private constructors
    iterator(ds_hashset* hs) : m_hs(hs), m_index(-1) {}
    iterator(ds_hashset* hs, int index, hash_list_itr loc) :
      m_hs(hs), m_index(index), m_list_itr(loc) {}

  public:
    // constructors
    iterator() : m_hs(0), m_index(-1) {}
    iterator(iterator const &itr) :
      m_hs(itr.m_hs), m_index(itr.m_index), m_list_itr(itr.m_list_itr) {}
    iterator& operator=(const iterator& old) {
      m_hs = old.m_hs;
      m_index = old.m_index;
      m_list_itr = old.m_list_itr;
      return *this;
    }

    // dereference -> current list iterator only
    const KeyType& operator*() const { return *m_list_itr; }

    // comparison -> accounts for list iterators being unassigned at end
    friend bool operator== (const iterator& lft, const iterator& rgt) {
      return lft.m_hs == rgt.m_hs && lft.m_index == rgt.m_index &&
        (lft.m_index == -1 || lft.m_list_itr == rgt.m_list_itr);
    }
    friend bool operator!= (const iterator& lft, const iterator& rgt) {
      return lft.m_hs != rgt.m_hs || lft.m_index != rgt.m_index ||
        (lft.m_index != -1 && lft.m_list_itr != rgt.m_list_itr);
    }

    // increment & decrement
    iterator& operator++() {
      this->next();
      return *this;
    }
    iterator operator++(int) {
      iterator temp(*this);
      this->next();
      return temp;
    }
    iterator& operator--() {
      this->prev();
      return *this;
    }
    iterator operator--(int) {
      iterator temp(*this);
      this->next();
      return temp;
    }

  private:
    // find next entry
    void next() {
      ++m_list_itr; // next in list
      // if at the end of the list
      if (m_list_itr == m_hs->m_table[m_index].end()) {
        for (++m_index; m_index < int(m_hs->m_table.size()) &&
            m_hs->m_table[m_index].empty(); ++m_index) {}
        
        // if one is found, assign m_list_itr to start
        if (m_index != int(m_hs->m_table.size()))
          m_list_itr = m_hs->m_table[m_index].begin();

        // otherwise, this is the end
        else
          m_index = -1;
      }
    }

    // find previous entry
    void prev() {
      // if not at start of current list, just decrement list iterator
      if (m_list_itr != m_hs->m_table[m_index].begin())
        m_list_itr--;

      else {
        // back down the tavle til previous non empty list in table is found
        for (--m_index; m_index >= 0 && m_hs->m_table[m_index].empty(); --m_index) {}

        // then go to last entry in that list
        m_list_itr = m_hs->m_table[m_index].begin();
        hash_list_itr p = m_list_itr; ++p;
        for (; p!= m_hs->m_table[m_index].end(); ++p, ++m_list_itr) {}
      }
    }
  };
  // end of the iterator class!
  //
private:
  // hash rep
  std::vector<std::list<KeyType> > m_table;
  HashFunc m_hash;
  unsigned int m_size;

public:
  // constructor accepts size of table
  ds_hashset(unsigned int init_size = 10) : m_table(init_size), m_size(0) {}

  // copy constructor uses member function copy
  ds_hashset(const ds_hashset<KeyType, HashFunc> &old) :
    m_table(old.m_table), m_size(old.m_size) {}

  ~ds_hashset() {}

  ds_hashset& operator=(const ds_hashset<KeyType, HashFunc> &old) {
    if (&old != this)
      *this = old;
  }

  unsigned int size() const { return m_size; }

  // insert key if not already there
  std::pair<iterator, bool> insert(KeyType const& key) {
    const float LOAD_FRACTION_FOR_RESIZE = 1.25;
    if (m_size >= LOAD_FRACTION_FOR_RESIZE * m_table.size())
      this->resize_table(2*m_table.size()+1);




  }
  
  // find key using hash funciton indexing and list find
  iterator find(const KeyType &key) {
    unsigned int hash_value = m_hash(key);
    unsigned int index = hash_value % m_table.size();
    hash_list_itr p = std::find(m_table[index].begin(), m_table[index].end(), key);
    if (p == m_table[index].end())
      return this->end();
    else 
      return iterator(this, index, p);
  }

  // erase key
  int erase(const KeyType &key) {
    // find key and use erase iterator function
    iterator p = find(key);
    if (p == end())
      return 0;
    else {
      erase(p);
      return 1;
    }
  }

  // erase at the iterator
  void erase(iterator p) {
    m_table[p.m_index].erase(p.m_list_itr);
  }

  // find the first entry in the table and create an associated iterator
  iterator begin() {
    if (m_size == 0)
      return end();
    int index = 0;
    while (m_table[index].empty()) {
      index++;
    }
    return iterator(this, index, m_table[index].begin());
  }

  // end iterator
  iterator end() {
    iterator p(this);
    p.m_index = -1;
    return p;
  }

  // a public print utility
  void print(std::ostream & ostr) {
    for (unsigned int i = 0; i < m_table.size(); ++i) {
      ostr << i << ": ";
      for (hash_list_itr p = m_table[i].begin(); p != m_table[i].end(); ++p)
        ostr << " " << *p;
      ostr << std::endl;
    }
  }

private:
  // resize table with same values
  void resize_table(unsigned int new_size) {
    // create new top level vector
    std::vector<std::list<KeyType> > tmp(new_size);
    // iterator over old structure
    for (iterator itr = this->begin(); itr != this->end(); ++itr) {
      KeyType key = *itr;
      // basically the intsert code but can't call insert bc two tables
      unsigned int hash_value = m_hash(key);
      unsigned int new_index = hash_value % new_size;
      // don't need to check for duplicates though
      tmp[new_index].push_back(key);
    }
    m_table = tmp;
  }

};

#endif
