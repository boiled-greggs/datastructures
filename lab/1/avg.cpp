#include <iostream>

int main() {
  int size;
  std::cout << "Enter several values to be averaged.\nStart by entering the number of numbers to be averaged: ";
  std::cin >> size;

  float numbers[size];

  std::cout << "Now start entering the " << size << " numbers:\n";

  for (int i = 0; i < size; i++) {
    std::cin >> numbers[i];
  }
  
  float total = 0;
  for (int i = 0; i < size; i++) {
    total += numbers[i];
  }

  float avg = total/float(size);

  std::cout << "\nThe average of the input values is: " << avg << std::endl;
  std::cout << "The input values less than the average are: ";
  for (int i = 0; i < size; i++) {
    if (numbers[i] < avg) {
      std::cout << numbers[i] << "  ";
    }
  }
  std::cout << std::endl;
  return 0;
}
