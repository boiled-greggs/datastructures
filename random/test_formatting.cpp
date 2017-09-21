#include <iostream>
#include <iomanip>

int main() {
  //std::setw(int), std::setprecision(int), std::fixed, std::left

  std::cout <<"The following is an example of setw(6)" << std::endl;
  std::cout << std::setw(10) << "hello" << std::setw(6) << 6 << 6 << std::endl;
 
  std::cout << std::endl;
  std::cout << "now a test of setprecision(4)" << std::endl;
  std::cout << std::setprecision(4) << 1.12345678 << " " << 1.9876543 << std::endl;
  
  std::cout << "\n and fixed (writes in fixed point notation)" << std::endl;
  std::cout << std::fixed << 1.12342345 << " " << "fixed\n";
  
  std::cout << "\nfinally, left:\n";
  std::cout << std::left << std::setw(10) << "hello" << 1 << std::endl;
  return 0;
}
