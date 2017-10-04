#ifndef __jagged_array_h_
#define __jagged_array_h_

template <class T> class JaggedArray {
  public:
    typedef T* iterator;
    typedef const T* const_iterator;

    // Constructors | Assignment Operators | Destructors
    JaggedArray() { this->create(); }
    JaggedArray(int n) { this->create(n); }
    JaggedArray(const JaggedArray& jar) { copy(jar); }
    JaggedArray& operator=(const JaggedArray& jar);
    ~JaggedArray() {
      if (isPacked()) {
        delete [] offsets;
        delete [] packed_values;
      }
      else {
        for (int i = 0; i < num_bins; ++i) {
          delete [] unpacked_values[i];
        }
        delete [] unpacked_values;
        delete [] counts;
      }
    }

    // Accessors | Other Members
    int numElements() const { return num_elements; }
    int numBins() const { return num_bins; }
    int numElementsInBin(int bin_no) const;
    T getElement(int bin_no, int index) const;

    bool isPacked() const;

    void addElement(int bin_no, const T& element);
    void removeElement(int bin_no, int index);
    
    void clear(); // delete everything, then create
    // more
    void pack();
    void unpack();
    void print();


  private:
    // private members
    void create();
    void create(int n);
    void copy(const JaggedArray<T> &jar);

    // all the info
    int num_elements;
    int num_bins;
    int* counts;
    T** unpacked_values;
    int* offsets;
    T* packed_values;

};

template <class T>
void JaggedArray<T>::create() {
  num_elements = num_bins = 0;
  counts = offsets = NULL;
  unpacked_values = NULL;
  packed_values = NULL;
}

template <class T>
void JaggedArray<T>::create(int n) {
  num_bins = n;
  num_elements = 0;
  counts = new int[n];
  for (int i = 0; i < n; ++i) {
    counts[i] = 0;
  }
  unpacked_values = new T*[n];
  for (int i = 0; i < n; ++i) {
    unpacked_values[i] = NULL; 
  }
  offsets = NULL; packed_values = NULL;
}

template <class T>
JaggedArray<T>& JaggedArray<T>::operator=(const JaggedArray<T> &jar) {
  if (this != &jar) {
    if (isPacked()) {
      delete [] offsets;
      delete [] packed_values;
    } else {
      for (int i = 0; i < num_bins; ++i) {
        delete [] unpacked_values[i];
      }
      delete [] unpacked_values;
      delete [] counts;
    }
    this -> copy(jar);
  }
  return *this;
}


template <class T>
void JaggedArray<T>::copy(const JaggedArray<T> &jar) {
  this->num_bins = jar.num_bins;
  this->num_elements = jar.num_elements;
  if (jar.isPacked()) {
    this->offsets = new int[jar.num_bins];
    for (int i = 0; i < jar.num_bins; ++i) {
      this->offsets[i] = jar.offsets[i];
    }
    this->packed_values = new T[jar.num_elements];
    for (int i = 0; i < jar.num_elements; ++i) {
      this->packed_values[i] = jar.packed_values[i];
    }
    counts = NULL;
    unpacked_values = NULL;
  } else {
    this->counts = new int[jar.num_bins];
    for (int i = 0; i < jar.num_bins; ++i) {
      this->counts[i] = jar.counts[i];
    }
    this->unpacked_values = new T*[jar.num_bins];
    for (int i = 0; i < jar.num_bins; ++i) {
      this->unpacked_values[i] = new T[jar.counts[i]];
      for (int j = 0; j < jar.counts[i]; ++j) {
        this->unpacked_values[i][j] = jar.unpacked_values[i][j];
      }
    }
    offsets = NULL;
    packed_values = NULL;
  }
}

template <class T>
bool JaggedArray<T>::isPacked() const {
  return counts == NULL && unpacked_values == NULL;
}

template <class T>
int JaggedArray<T>::numElementsInBin(int bin_no) const {
  if (bin_no < num_bins && bin_no >= 0) {
    if (!isPacked()) return counts[bin_no];
    else {
      if (bin_no != num_bins-1) {
        return offsets[bin_no+1] - offsets[bin_no];
      } else {
        return num_elements - offsets[bin_no];
      }
    }
  } else {
    std::cerr << "ERROR: Tried to access nonexistent bin!" << std::endl;
    exit(1);
  }

}

template <class T>
T JaggedArray<T>::getElement(int bin_no, int index) const{ 
  if (bin_no < num_bins && bin_no >= 0) {
    if (!isPacked()) {
      if (index < counts[bin_no] && index >= 0) return unpacked_values[bin_no][index];
      else {
        std::cerr << "ERROR: tried to access nonexistent element in bin " << bin_no << std::endl;
        exit(1);
      }
    } else {
      if (bin_no < num_bins-1 && index < offsets[bin_no+1]-offsets[bin_no] && index >= 0) {
        return packed_values[offsets[bin_no]+index];
      } else if (bin_no == num_bins-1 && index < num_elements-offsets[bin_no] && index >= 0) {
        return packed_values[offsets[bin_no]+index];
      } else {
        std::cerr << "ERROR: Tried to access nonexistent element in bin " << bin_no << std::endl;
        exit(1);
      }
    }
  } else {
    std::cerr << "ERROR: Tried to access nonexistent bin!" << std::endl;
    exit(1);
  }
}

template <class T>
void JaggedArray<T>::addElement(int bin_no, const T &element) {
  // num elements + 1
  // makes new array of type T with size of count of [bin_no] array + 1
  // to hold new element. copies values from old array, then sets last
  // value of new array to added element. then deletes old array, and
  // sets the unpacked_value{bin_no] to new array
  if (!isPacked()) {
    if (bin_no < num_bins && bin_no >= 0) {
    if (counts[bin_no] != 0) {
      T* new_data = new T[counts[bin_no]+1];
      for (int i = 0; i < counts[bin_no]; ++i) {
        new_data[i] = unpacked_values[bin_no][i];
      }
      new_data[counts[bin_no]] = element;
      counts[bin_no] += 1;
      delete [] unpacked_values[bin_no];
      unpacked_values[bin_no] = new_data;
    } else {
      unpacked_values[bin_no] = new T[1];
      unpacked_values[bin_no][0] = element;
      counts[bin_no] += 1;
    }
    num_elements += 1;
    } else {
      std::cerr << "ERROR: cannot add element to nonexistent bin" << std::endl;
      exit(1);
    }
  } else {
    std::cerr << "ERROR: cannot add elements when packed\n";
    exit(1);
  }
}

template <class T>
void JaggedArray<T>::removeElement(int bin_no, int index) {
  if (!isPacked()) {
    if (bin_no < num_bins && bin_no >= 0) {
    T* new_data = new T[counts[bin_no]-1];
    for (int i = 0; i < counts[bin_no]; ++i) {
      if (i < index) new_data[i] = unpacked_values[bin_no][i];
      else if (i > index) new_data[i-1] = unpacked_values[bin_no][i];
    }
    counts[bin_no] -= 1;
    delete [] unpacked_values[bin_no];
    unpacked_values[bin_no] = new_data;
    num_elements -= 1;
    } else {
      std::cerr << "ERROR: That bin doesn't exist!" << std::endl;
    }
  } else {
    std::cerr << "ERROR: cannot remove elements when packed\n";
    exit(1);
  }
}

template <class T>
void JaggedArray<T>::print() {
  if(!isPacked()) {
    std::cout << "unpacked JaggedArray\n";
    std::cout << "  num_bins: " << num_bins << std::endl;
    std::cout << "  num_elements: " << num_elements << std::endl;
    std::cout << "  counts: ";
    int max = 0;
    for (int i = 0; i < num_bins; ++i) {
      std::cout << " " << counts[i];
      if (counts[i] > max) max = counts[i];
    }
    std::cout << "\n  values: ";
    for (int i = 0; i < max; ++i) {
      for (int j = 0; j < num_bins; ++j) {
        if (counts[j] >= i+1) {
          std::cout << " " << unpacked_values[j][i];
        } else {
          std::cout << "  ";
        }
      }
      std::cout << std::endl;
      if (i!=max-1) std::cout << "          ";
    }
  } else if (isPacked()) {
    std::cout << "packed JaggedArray\n";
    std::cout << "  num_bins: " << num_bins << std::endl;
    std::cout << "  num_elements: " << num_elements << std::endl;
    std::cout << "  offsets: ";
    for (int i = 0; i < num_bins; ++i) {
      std::cout << " " << offsets[i];
    }
    std::cout << "\n  values: ";
    for (int i = 0; i < num_elements; ++i) {
      std::cout << " " << packed_values[i];
    }
    std::cout << std::endl;
  }
}


template <class T>
void JaggedArray<T>::pack() {
  offsets = new int[num_bins];
  packed_values = new T[num_elements];
  for (int i = 0; i < num_bins; ++i) {
    if (i == 0) {
      offsets[i] = 0;
    }
    else {
      offsets[i] = offsets[i-1] + counts[i-1];
    }
  }
  for (int i = 0; i < num_bins; ++i) {
    for (int j = 0; j < counts[i]; ++j) {
      packed_values[j+offsets[i]] = unpacked_values[i][j];
    }
  }
  for (int i = 0; i < num_bins; ++i) {
    delete [] unpacked_values[i];
  }
  delete [] unpacked_values;
  unpacked_values = NULL;
  delete [] counts;
  counts = NULL;
}

template <class T>
void JaggedArray<T>::unpack() {
  counts = new int[num_bins];
  unpacked_values = new T*[num_bins];
  for (int i = 0; i < num_bins; ++i) {
    if (i != num_bins-1) {
      if (offsets[i+1]-offsets[i] > 0) {
        unpacked_values[i] = new T[offsets[i+1]-offsets[i]];
        for (int j = 0; j < offsets[i+1]-offsets[i]; ++j) {
          unpacked_values[i][j] = packed_values[j + offsets[i]];
        }
        counts[i] = offsets[i+1]-offsets[i];
      } else {
        unpacked_values[i] = NULL;
        counts[i] = 0;
      }
    } else {
      if (num_elements-offsets[i] > 0){
        unpacked_values[i] = new T[num_elements - offsets[i]];
        for (int j = 0; j < num_elements - offsets[i]; ++j) {
          unpacked_values[i][j] = packed_values[j + offsets[i]];
        }
        counts[i] = num_elements - offsets[i];
      } else {
        unpacked_values[i] = NULL;
        counts[i] = 0;
      }
    }
  }
  delete [] offsets;
  delete [] packed_values;
}

template <class T>
void JaggedArray<T>::clear() {
  // clears out all the bins and num elements
  for (int i = 0; i < num_bins; ++i) {
    delete [] unpacked_values[i];
    unpacked_values[i] = NULL;
    counts[i] = 0;
  }
  num_elements = 0;
}



















#endif
