#include <iostream>   // library for reading & writing from the console/keyboard
#include <cmath>      // library with the square root function & absolute value
#include <cstdlib>    // library with the exit function


// Returns true if the candidate root is indeed a root of the polynomial a*x*x + b*x + c = 0 
bool check_root(int a, int b, int c, float root) {  
  // plug the value into the formula
  float check = a * root * root + b * root + c;
  // see if the absolute value is zero (within a small tolerance)
  if (fabs(check) > 0.0001) {
    std::cerr << "ERROR:  " << root << " is not a root of this formula." << std::endl;
    return false;
  } else {
    return true;
  }
}

/* Use the quadratic formula to find the two real roots of polynomial.   Returns 
true if the roots are real, returns false if the roots are imaginary.  If the roots 
are real, they are returned through the reference parameters root_pos and root_neg. */ 
bool find_roots(int a, int b, int c, float &root_pos, float &root_neg) {
  // compute the quantity under the radical of the quadratic formula
  float radical = b*b - 4*a*c;
  // if the radical is negative, the roots are imaginary
  if (radical < 0) {
    std::cerr << "ERROR: quadratic with a=1, b="<<b<<", c="<<c<<" has imaginary roots" << std::endl;
    return false;
  }
  float sqrt_radical = sqrt(radical);
  // compute the two roots
  root_pos = (-b + sqrt_radical) / (2*a);
  root_neg = (-b - sqrt_radical) / (2*a);
  
  return true;
}

int main() {
  // We will loop until we are given a polynomial with real roots
  std::cout << "Enter five values each for b and c of a quadratic function a*x*x + b*x + c = 0" << std::endl;
  double b_array[5];
  double c_array[5];
  double smaller_root[5];
  for (int i = 0; i < 5; i++) {
    std::cout << "b: ";
    std::cin >> b_array[i];
    std::cout << "c: ";
    std::cin >> c_array[i];
  }
  for (int i = 0; i < 5; i++) {
    float root1, root2;
    bool success = find_roots(1, b_array[i], c_array[i], root1, root2);
    if (root1 < root2) { 
      smaller_root[i] = root1;
    } else if (root1 > root2) {
      smaller_root[i] = root2;
    } else {
      smaller_root[i] = root1;
    }
    if (!success) continue;
    // Check our work...
    if (check_root(1,b_array[i],c_array[i], root1) && check_root(1,b_array[i],c_array[i], root2)) {
      std::cout << "The roots of quadratic with a=1, b="<<b_array[i]<<", c="<<c_array[i]<<" are: " << root1 << " and " << root2 << std::endl << "and the smaller root is " << smaller_root[i] << std::endl;
      // Verified roots, break out of the while loop
    } else {
      std::cerr << "ERROR:  Unable to verify one or both roots of quadratic with a=1, b="<<b_array[i]<<", c="<<c_array[i]<<"." << std::endl;
      // if the program has an error, we choose to exit with a
      // non-zero error code
      exit(1); 
    }

  }

  // by convention, main should return zero when the program finishes normally
  return 0; 
}
