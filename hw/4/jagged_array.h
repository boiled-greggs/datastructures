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
    ~JaggedArray();
    
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

// default constructor sets everything to 0 or null
template <class T>
void JaggedArray<T>::create() {
  num_elements = num_bins = 0;
  counts = offsets = NULL;
  unpacked_values = NULL;
  packed_values = NULL;
}

// constructor creates an unpacked jagged array with number of bins n
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

// destructor
// if it's packed, free offsets and packed values
// if unpacked, delete each array in unpacked values, then
// delete unpacked values array and counts array
template <class T>
JaggedArray<T>::~JaggedArray() {
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
}

// assignment operator
// checks if same object. if not, free this's memory (packed or unpacked)
// then go to the copy constructor. finally, return the constructed array
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

// copy constructor
// set this's variable equal to copied array's
// then if packed, copy input offsets and values to this's by allocating memory
// then looping through, setting unnecessary things to NULL. if unpacked, do the
// same with the counts and unpacked values copied and packed pointers set to NULL
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

// simple - Packed arrays have NULL counts and NULL unpacked values by definition
template <class T>
bool JaggedArray<T>::isPacked() const {
  return counts == NULL && unpacked_values == NULL;
}

// elements in bin
// if unpacked, it's as simple as returning the values of counts at the bin no.
// if packed, must return either the counts from offsets[bin+1]-offsets[bin],
// or if the last offsets element, num_elements - offsets[bin]
// error and exit if trying to reach beyond array
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

// get element
// if unpacked, trivial
// if packed, must get the index in the packed_values array from the offsets
// formula + index given, then return that value from packed_values.
// error and exit if you're trying to reach beyond where you're allowed
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

// add element
// makes new array of type T with size of count[bin_no] + 1
// to hold new element. copies values from old array, then sets last
// value of new array to added element. then frees memory of old array, and
// sets the unpacked_value[bin_no] to new array. +1 counts[bin], +1 num elements
// error and exit if trying to add element to bad place or 
// if trying to add element when array is packed
template <class T>
void JaggedArray<T>::addElement(int bin_no, const T &element) {
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

// remove element
// allocates new array of size counts[bin_no] - 1, then 
// copies all the values from old bin to new one, except the value
// at the given index. then deallocates old array and assigns new
// array to unpacked_values[bin_no]. changes counts[bin_no].
// changes num elements.
// error if trying to remove element when packed, and when trying
// to remove from out of bounds
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

// print
// pretty self explanatory. for unpacked, must print across bins, so
// first it finds the maximum count so it know where to stop trying
// to print, then it print values across the bins by checking if 
// there is a value to print (from comparing counts[bin] to integer in loop).
// if it's packed it just prints directly with a loop.
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
  std::cout << std::endl;
}

// pack
// checks if it's packed first
// allocates new arrays for offsets and packed_values, then uses counts
// to assign the values of offsets. Then uses unpacked_values to assign
// the values to packed_values in order.
// finally, deallocates memory for unpacked_values and counts, then
// sets both to NULL.
template <class T>
void JaggedArray<T>::pack() {
  if (isPacked()) std::cout << "Already Packed!\n";
  else {
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
}

// unpack
// checks if it's unpacked first.
// allocates new array for counts and new array of arrays for 
// unpacked_values. Then, loops through the number of bins, and if
// there are > 0 values in a bin, makes a new array in unpacked_values,
// then assigns the values from packed_values. sets counts[bin] to the
// right number from the offsets formula. functions slightly differently
// for the last bin since counts[last] is num_elements - offsets[last],
// so it handles that case differently. If the number of values in a bin
// is 0, it sets the unpacked_values[bin] to NULL and counts[bin] to 0.
// Finally, it deallocates the memory of offsets and packed_values.
template <class T>
void JaggedArray<T>::unpack() {
  if (!isPacked()) std::cout << "Already Unpacked!\n";
  else {
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
}

// clear
// 0 elements. if it's unpacked, sets each unpacked_values[bin] to NULL
// and counts all to 0. Keeps the number of bins.
// If packed, it sets all the offsets to 0 and then frees
// packed_values, setting it to NULL after.
template <class T>
void JaggedArray<T>::clear() {
  // clears out all the bins and num elements
  num_elements = 0;
  if (!isPacked()) {
    for (int i = 0; i < num_bins; ++i) {
      delete [] unpacked_values[i];
      unpacked_values[i] = NULL;
      counts[i] = 0;
    }
  } else {
    for (int i = 0; i < num_bins; ++i) {
      offsets[i] = 0;
    }
    delete [] packed_values;
    packed_values = NULL;
  }
}



#endif
