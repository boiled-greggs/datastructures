#include <iostream>
#include <vector>

void reverse_vector(std::vector<int> &v) {
  for (unsigned int i = 0; i < v.size()/2; ++i) {
    int tmp = v[i];
    v[i] = v[v.size() - i - 1];
    v[v.size() - i - 1] = tmp;
  }
}

void print(std::vector<int> &v) {
  std::cout << "------------------------" << std::endl;
  std::cout << "Vector size: " << v.size() << std::endl;
  std::cout << "Vector contents: ";
  for (unsigned int i = 0; i < v.size(); ++i) {
    std::cout << " " << v[i];
  }
  std::cout << std::endl;
}

int main() {
  std::vector<int> vec1;
  for (int i = 0; i < 10; ++i) {
    vec1.push_back(i);
  }
  std::cout << "Test 1: even" << std::endl;
  print(vec1);
  std::cout << "\nand reverse" << std::endl;
  reverse_vector(vec1);
  print(vec1);

  std::vector<int> vec2;
  for (int i = 0; i < 9; ++i) {
    vec2.push_back(i);
  }
  std::cout << "\nTest 2: odd" << std::endl;
  print(vec2);
  std::cout << "\nand reverse" << std::endl;
  reverse_vector(vec2);
  print(vec2);

  std::vector<int> vec3;
  std::cout << "\nTest 3: empty" << std::endl;
  print(vec3);
  std::cout << "\nand reverse" << std::endl;
  reverse_vector(vec3);
  print(vec3);

  std::vector<int> vec4;
  std::cout << "\nTest 4: 1 val" << std::endl;
  vec4.push_back(1);
  print(vec4);
  std::cout << "\nand reverse" << std::endl;
  reverse_vector(vec4);
  print(vec4);

  std::vector<int> vec5;
  std::cout << "\nTest 5: 2 val" << std::endl;
  vec5.push_back(1); vec5.push_back(2);
  print(vec5);
  std::cout << "\nand reverse" << std::endl;
  reverse_vector(vec5);
  print(vec5);
  
  std::vector<int> vec6;
  for (int i = 0; i < 40; ++i) {
    vec6.push_back(i);
  }
  std::cout << "Test 6: big even" << std::endl;
  print(vec6);
  std::cout << "\nand reverse" << std::endl;
  reverse_vector(vec6);
  print(vec6);
  
  std::vector<int> vec7;
  for (int i = 0; i < 41; ++i) {
    vec7.push_back(i);
  }
  std::cout << "Test 7: big odd" << std::endl;
  print(vec7);
  std::cout << "\nand reverse" << std::endl;
  reverse_vector(vec7);
  print(vec7);
}
