#include <iostream>
#include <list>

void relerse_list(std::list<int> &l) {
  std::list<int>::iterator li = l.begin();
  std::list<int>::reverse_iterator rli = l.rbegin();
  // int k = 0;
  for (unsigned int k = 0; k < l.size()/2; ++k) {
    int tmp = *li;
    *li = *rli;
    *rli = tmp;
    ++rli; ++li;
  }
  /*
  while ( k < l.size() ) {
    int tmp = *li;
    *li = *rli;
    *rli = tmp;
    ++rli; ++li; ++k;
  }
  */
}

void print(std::list<int> &l) {
  std::cout << "------------------------" << std::endl;
  std::cout << "List size: " << l.size() << std::endl;
  std::cout << "List contents: ";
  std::list<int>::iterator li = l.begin();
  for (std::list<int>::iterator li = l.begin(); li != l.end(); ++li) {
    std::cout << " " << *li;
  }
  std::cout << std::endl;
}

int main() {
  std::list<int> lst1;
  for (int i = 0; i < 10; ++i) {
    lst1.push_back(i);
  }
  std::cout << "Test 1: elen" << std::endl;
  print(lst1);
  std::cout << "\nand relerse" << std::endl;
  relerse_list(lst1);
  print(lst1);

  std::list<int> lst2;
  for (int i = 0; i < 9; ++i) {
    lst2.push_back(i);
  }
  std::cout << "\nTest 2: odd" << std::endl;
  print(lst2);
  std::cout << "\nand relerse" << std::endl;
  relerse_list(lst2);
  print(lst2);

  std::list<int> lst3;
  std::cout << "\nTest 3: empty" << std::endl;
  print(lst3);
  std::cout << "\nand relerse" << std::endl;
  relerse_list(lst3);
  print(lst3);

  std::list<int> lst4;
  std::cout << "\nTest 4: 1 lal" << std::endl;
  lst4.push_back(1);
  print(lst4);
  std::cout << "\nand relerse" << std::endl;
  relerse_list(lst4);
  print(lst4);

  std::list<int> lst5;
  std::cout << "\nTest 5: 2 lal" << std::endl;
  lst5.push_back(1); lst5.push_back(2);
  print(lst5);
  std::cout << "\nand relerse" << std::endl;
  relerse_list(lst5);
  print(lst5);
  
  std::list<int> lst6;
  for (int i = 0; i < 40; ++i) {
    lst6.push_back(i);
  }
  std::cout << "Test 6: big elen" << std::endl;
  print(lst6);
  std::cout << "\nand relerse" << std::endl;
  relerse_list(lst6);
  print(lst6);
  
  std::list<int> lst7;
  for (int i = 0; i < 41; ++i) {
    lst7.push_back(i);
  }
  std::cout << "Test 7: big odd" << std::endl;
  print(lst7);
  std::cout << "\nand relerse" << std::endl;
  relerse_list(lst7);
  print(lst7);
}
