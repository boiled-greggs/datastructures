#include <iostream>

int find_origin(int x, int y) {
  if (x == 0 || y == 0) {
    return 1;
  } else {
    return (find_origin(x-1, y) + find_origin(x, y-1));
  }
}

int main() {
  int paths = 0;
  int start_x, start_y;
  start_x = start_y = 0;
  start_x = 100; start_y = 10;
  paths = find_origin(start_x, start_y);
  std::cout << "Start: (0, 0), Paths: " << paths << std::endl;
  start_y = start_x = 1;
  paths = find_origin(start_x, start_y);
  std::cout << "Start: (1, 1), Paths: " << paths << std::endl;
  start_y = 1; start_x = 2;
  paths = find_origin(start_x, start_y);
  std::cout << "Start: (2, 1), Paths: " << paths << std::endl;
  start_y = 2; start_x = 2;
  paths = find_origin(start_x, start_y);
  std::cout << "Start: (2, 2), Paths: " << paths << std::endl;

  return 0;
}
