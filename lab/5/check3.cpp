#include <iostream>
#include <list>
#include <vector>
#include <cassert>



void print(const std::string &label, const std::list<std::string> &data) {
    std::cout << label;
      for (std::list<std::string>::const_iterator itr = data.begin();
                 itr != data.end(); itr++) {
            std::cout << " " << *itr;
              }
        std::cout << std::endl;
}

void update(std::list<std::string> &data, std::vector<std::string> &add, 
    std::vector<std::string> &remove) {
  // add first
  // iterate through add. check if add[i] in data. if it's not,
  // add it in. you can do this easily bc it's already sorted.
  if (data.size() > 0) { 
    for (unsigned int i = 0; i < add.size(); ++i) {
      std::list<std::string>::iterator itr = data.begin();
      bool in_list = false;
      for (unsigned int j = 0; j < data.size(); j++) {
        if (add[i].find(*itr) != std::string::npos) {
          in_list = true;
          break;
        }
        ++itr;
      }
      itr = data.begin();
      std::list<std::string>::iterator itr_end = data.end(); --itr_end;
      if (!in_list) {
        std::cout << add[i] << std::endl;
        if (add[i] < *itr) data.push_front(add[i]);
        if (add[i] > *itr_end) data.push_back(add[i]);
        for (unsigned int j = 0; j < data.size(); j++) {
          std::list<std::string>::iterator itr2 = itr;
          ++itr2;
          if (*itr < add[i] && *itr2 > add[i]) {
            data.insert(itr2, add[i]);
          }
          ++itr;
        }
      }
    }
  } else {
    for (unsigned int i = 0; i < add.size(); ++i) {
      data.push_back(add[i]);
    }
    data.sort();
  }

  for (unsigned int i = 0; i < remove.size(); ++i) {
    std::list<std::string>::iterator itr = data.begin();
    while ( itr != data.end() ) {
      if ( (*itr).find(remove[i]) != std::string::npos) {
        itr = data.erase(itr);
      } else {
        ++itr;
      }
    }
  }
}

int main() {


    // Examples demonstrating STL string find:
    // catfish contains the substring fish
    assert (std::string("catfish").find(std::string("fish")) != std::string::npos);
    // fish contains the substring fish
    assert (std::string("fish").find(std::string("fish")) != std::string::npos);
    // fish does not contain the substring catfish
    assert (std::string("fish").find(std::string("catfish")) == std::string::npos);
    
    // A simple example:
    std::list<std::string> data;
    data.push_back("antelope");
    data.push_back("catfish");
    data.push_back("giraffe");
    data.push_back("llama");
    data.push_back("jellyfish");
    data.push_back("whale_shark");
    data.push_back("zebra");
    
    std::vector<std::string> add;
    add.push_back("tiger");
    add.push_back("llama");
    add.push_back("elephant");
    
    std::vector<std::string> remove;
    remove.push_back("fish");
    remove.push_back("bear");
    remove.push_back("whale");
    
    std::cout << "-----------------------\nTest 1\n-----------------------\n";
    print ("before:",data);
    update(data,add,remove);
    print ("after: ",data);
    
    // at the end, data should contain: antelope elephant giraffe llama tiger zebra
    assert (data.size() == 6);
    std::cout << "-----------------------" << std::endl;

    std::cout << "Test 2: remove all elements\n-----------------------\n";
    std::list<std::string> test;
    test.push_back("hello"); test.push_back("hi"); test.push_back("hey");
    test.push_back("goodbye"); test.push_back("bye"); test.push_back("see_ya");
    test.sort();
    
    std::vector<std::string> add2;

    std::vector<std::string> rem2;
    rem2.push_back("hello"); rem2.push_back("hi"); rem2.push_back("hey");
    rem2.push_back("goodbye"); rem2.push_back("bye"); rem2.push_back("see_ya");

    print("before:",test);
    update(test,add2,rem2);
    print("after:",test);

    std::cout << "-----------------------" << std::endl;
  
    std::cout << "Test 3: add to empty list\n-----------------------\n";

    std::list<std::string> test2;
    
    std::vector<std::string> add3;
    add3.push_back("adding"); add3.push_back("strings"); add3.push_back("is");
    add3.push_back("so"); add3.push_back("much"); add3.push_back("fun"); add3.push_back("!");
    
    std::vector<std::string> rem3;

    print("before:", test2);
    update(test2,add3,rem3);
    print("after:", test2);
    
    std::cout << "-----------------------" << std::endl;

    std::cout << "Test 4: add to empty, then remove all elements\n-----------------------\n";
    
    std::list<std::string> test3;
    
    std::vector<std::string> add4;
    add4.push_back("one"); add4.push_back("two"); add4.push_back("three");
    add4.push_back("four"); add4.push_back("five"); add4.push_back("six");
    add4.push_back("seven");
    
    std::vector<std::string> rem4;
    rem4.push_back("one"); rem4.push_back("two"); rem4.push_back("three");
    rem4.push_back("four"); rem4.push_back("five"); rem4.push_back("six");
    rem4.push_back("seven");

    print("before:", test3);
    update(test3,add4,rem4);
    print("after:", test3);
    
    std::cout << "-----------------------" << std::endl;

    std::cout << "Test 5\n-----------------------\n";
    std::list<std::string> test4;
    test4.push_back("antelope");
    test4.push_back("catfish");
    test4.push_back("giraffe");
    test4.push_back("llama");
    test4.push_back("jellyfish");
    test4.push_back("whale_shark");
    test4.push_back("zebra");
    
    std::vector<std::string> add5;
    add.push_back("aaaaa");
    add.push_back("zzzzz");
    
    std::vector<std::string> rem5;
    
    print ("before:",test4);
    update(test4,add5,rem5);
    print ("after: ",test4);



}

