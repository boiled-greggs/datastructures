#include <iostream>
#include <string>
#include <utility>
#include <cassert>

#include "ds_set.h"

int main() {

  ds_set<std::string> set1;
  set1.insert("hello");
  set1.insert("good-bye");
  set1.insert("friend");
  set1.insert("abc");
  set1.insert("puppy");
  set1.insert("zebra");
  set1.insert("daddy");
  set1.insert("puppy");  // should recognize that this is a duplicate!

  assert(set1.sanity_check());
  assert (set1.size() == 7);

  ds_set<std::string>::iterator p = set1.begin();
  assert(p != set1.end() && *p == std::string("abc"));

  p = set1.find( "foo" );
  assert (p == set1.end());

  p = set1.find("puppy");
  assert (p != set1.end());
  assert (*p == "puppy");

  std::cout << "Here is the tree, printed sideways.\n"
	    << "The indentation is proportional to the depth of the node\n"
	    << "so that the value stored at the root is the only value printed\n"
	    << "without indentation.  Also, for each node, the right subtree\n"
	    << "can be found above where the node is printed and indented\n"
	    << "relative to it\n";
  set1.print_as_sideways_tree( std::cout );
  std::cout << std::endl;


  // copy the set
  ds_set<std::string> set2( set1 );
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size());
  

  //  Now add stuff to set2
  set2.insert( std::string("a") );
  set2.insert( std::string("b") );
  std::cout << "After inserting stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() - 2);


  //  Now erase stuff from set2
  set2.erase("hello");
  set2.erase("a");
  set2.erase("hello"); // should recognize that it's not there anymore!
  set2.erase("abc");
  set2.erase("friend");
  std::cout << "After erasing stuff:\n";
  set2.print_as_sideways_tree( std::cout );
  std::cout << std::endl;
  assert(set1.sanity_check());
  assert(set2.sanity_check());
  assert(set1.size() == set2.size() + 2);


  // Test the iterators!

  ds_set<int> intset1;
  intset1.insert(8);
  intset1.insert(4);
  intset1.insert(12);
  intset1.insert(2);
  intset1.insert(6);
  intset1.insert(10);
  intset1.insert(14);
  intset1.insert(1);
  intset1.insert(3);
  intset1.insert(5);
  intset1.insert(7);
  intset1.insert(9);
  intset1.insert(11);
  intset1.insert(13);
  intset1.insert(15);

  intset1.print_as_sideways_tree(std::cout);

  ds_set<int>::iterator intp = intset1.end();

  for (int i = 0; i < 14; ++i) {
    --intp;
    std::cout << "decrement " << i << ": " << *intp << std::endl;
  }

  ds_set<int> intset2;
  intset2.insert(8);
  intset2.insert(2);
  intset2.insert(3);
  intset2.insert(1);
  intset2.insert(4);
  intset2.insert(13);
  intset2.insert(5);
  intset2.insert(7);
  intset2.insert(15);
  intset2.insert(12);
  intset2.insert(6);
  intset2.insert(10);
  intset2.insert(14);
  intset2.insert(9);
  intset2.insert(11);

  intset2.print_as_sideways_tree(std::cout);

  ds_set<int>::iterator intp2 = intset2.end();

  for (int i = 0; i < 14; ++i) {
    --intp2;
    std::cout << "decrement " << i << ": " << *intp2 << std::endl;
  }
  int j = 0;
  int accint = intset1.accumulate(j);
  std::cout << "\naccumulation of ints: " << accint << std::endl;
  std::string s = "";
  std::string accstring = set1.accumulate(s);
  std::cout << "\naccumulation set 1: " << accstring << std::endl;











  return 0;
}
