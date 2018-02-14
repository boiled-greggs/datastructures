#ifndef __hash_h_
#define __hash_h_

#include <vector>
#include <algorithm>
#include <stdlib.h>
#include "image.h"

// seed class 
class Seed {
  public:
    Seed() : avg(0) {}
    Seed(const Image<int> &im, int x_, int y_, int seed) {
      int average = 0;
      x = x_; y = y_;
      for (int i = 0; i < seed; ++i) {
        for (int j = 0; j < seed; ++j) {
          pixels.push_back(im.GetPixel(x+i,y+j));
          average += im.GetPixel(x+i,y+j);
        }
      }
      avg = float(average) / float(pixels.size());
    }
    
    // two seeds are equal if they have the same avg
    // and the all the same pixels. should keep things
    // pretty unique.
    bool operator==(const Seed &s) {
      if (avg == s.avg && pixels == s.pixels)
        return true;
      else return false;
    }
    
    // Representation
    std::vector<int> pixels;
    float avg;
    int x;
    int y;

};

// Hash Table class
class HashTable {
  public:
    HashTable() {
      size_ = 0; table = std::vector<std::vector<Seed> >(256, std::vector<Seed>());
    }
    int size() const { return size_; }
    
    // grabs a seed from the table, dependent on the number
    // of seeds you'll be looking at total, and which one
    // you're on right now. it iterates through the table,
    // and if the location determined from the two arguments
    // is in that part of the table, it returns that seed
    Seed getSeed(int i, int num) {
      int interval = size_/num;
      int distance = i*interval;
      int count = 0;
      for (int j = 0; j < table.size(); ++j) {
        if (distance < count+table[j].size() && distance >= count) {
          int d = distance - count;
          return table[j][d];
        }
        count += table[j].size();
      }
    }
    
    // put things in the table
    void addSeed(const Seed &s) {
      int index = hash_func(s);
      table[index].push_back(s);
      size_++;
    }
    
    // determine if this table has a given seed. use the hash
    // function on the seed to find the index in the table, and
    // check the vector at that index for the seed. return a pair
    // with true and the seed if it's there. else false.
    std::pair<bool, Seed> hasSeed(const Seed &s) {
      int index = hash_func(s);
      std::vector<Seed>::iterator itr;
      if (table[index].size() == 0) return std::make_pair(false, Seed());
      else {
        for (itr = table[index].begin(); itr != table[index].end(); ++itr)
          if (*itr == s)
            return std::make_pair(true, *itr);
        if (itr == table[index].end())
          return std::make_pair(false, Seed());
      }
      return std::make_pair(false, Seed());
    }

  private:
    // representation
    std::vector<std::vector<Seed> > table;
    int size_;

    // hash function. it takes the average pixel value
    // of the seed and uses it as the index in the table.
    // originally used a vector of size 128 so it was bit/2,
    // but this one is a little more efficient.
    int hash_func(const Seed &s) {
      int bit = (int)s.avg;
      int index = bit;
      return index;
    }

};


#endif
