#include <list>
#include <iostream>
#include <cassert>

bool reverse_splice(std::list<int> &data, std::list<int>::iterator &i, std::list<int>::iterator &j) {
  std::list<int>::iterator tmp1, tmp2;
  int count = 0;
  tmp1 = i; tmp2 = j;
  bool allowed = false;
  while (tmp1 != data.end()) {
    if (tmp1 == j) {
      allowed = true;
      break;
    } else {
      count++;
      tmp1++;
    }
  }
  if (allowed) {
    int limit = 0;
    while(limit < count/2 + count%2) {
      tmp1 = i; tmp2 = j;
      i = data.insert(i, *j);
      j = data.insert(j, *tmp1);
      i = data.erase(tmp1);
      j = data.erase(tmp2);
      j--; j--;
      ++limit;
    }
    for ( int k = 0; k < count/2; k++) {
      i++; j--;
    }
    return true;
  } else {
    return false;
  }
}


int main() {

  std::list<int> data;

  data.push_back(1);
  data.push_back(2);
  data.push_back(3);
  data.push_back(4);
  data.push_back(5);
  data.push_back(6);
  data.push_back(7);
  data.push_back(8);
  data.push_back(9);

  std::list<int>::iterator i;
  i = data.begin();
  i++;i++;
  std::list<int>::iterator j;
  j = data.begin();
  j++;j++;
  j++;j++;
  j++;j++;
  //j++;j++;j++;

  // verify the iterators
  assert (*i == 3);
  //assert (*j == 8);
  assert (*j == 7);
  
  // print the initial data
  for (std::list<int>::iterator k = data.begin(); k != data.end(); k++) {
    std::cout << " " << *k;    
  }
  std::cout << std::endl;
  
  bool success = reverse_splice(data,i,j);
  assert (success);
  
  // print the data after the operation  
  for (std::list<int>::iterator k = data.begin(); k != data.end(); k++) {
    std::cout << " " << *k;    
  }
  std::cout << std::endl;
  
  // verify the iterators
  assert (*i == 3);
  //assert (*j == 8);
  assert (*j == 7);
  
  success = reverse_splice(data, i, j);
  if (!success) std::cout << "nope!" << std::endl;
  
}
