#include <iostream>
#include <iomanip>
#include "Rectangle.h"
#include "Point2D.h"


int main() {
  // for lldb
  Point2D testpoint;
  testpoint.set(10,11);
  
  Rectangle rec1(Point2D(1,2), Point2D(5,6));
  Rectangle rec2(Point2D(5,6), Point2D(6,7));
  Rectangle rec3(Point2D(2,1), Point2D(4,7));
  std::cout << "rectangles\n--------------------------------" << std::endl;
  print_rectangle(rec1);
  print_rectangle(rec2);
  print_rectangle(rec3);
  std::cout<<std::endl;  
  std::vector<Point2D> test_pts;
  test_pts.push_back(Point2D(1,1));
  test_pts.push_back(Point2D(2,2));
  test_pts.push_back(Point2D(3,3));
  test_pts.push_back(Point2D(4,4));
  test_pts.push_back(Point2D(5,5));
  test_pts.push_back(Point2D(6,6));
  test_pts.push_back(Point2D(5,6));
  test_pts.push_back(Point2D(5.5,6.6));
  test_pts.push_back(Point2D(3,6.5));

  std::cout << "test points\n--------------------------------" << std::endl;
  for (unsigned int i = 0; i < test_pts.size(); i++) {
    std::cout << "point " << i+1 << ": " << std::setw(4) << std::left << test_pts[i].x() << " " << std::setw(4) << test_pts[i].y() << std::endl;
  }
  std::cout << "---------------------------------" << std::endl;
  std::cout << "testing is_point_within function\n---------------------------------\n";  
  for (unsigned int i = 0; i < test_pts.size(); i++) {
    if (rec1.is_point_within(test_pts[i])) {
      std::cout << "point " << i+1 << " is within rectangle 1\n";
    } else {
      std::cout << "point " << i+1 << " is NOT within rectangle 1\n";
    }
  }
  for (unsigned int i = 0; i < test_pts.size(); i++) {
    if (rec2.is_point_within(test_pts[i])) {
      std::cout << "point " << i+1 << " is within rectangle 2\n";
    } else {
      std::cout << "point " << i+1 << " is NOT within rectangle 2\n";
    }
  }
  for (unsigned int i = 0; i < test_pts.size(); i++) {
    if (rec3.is_point_within(test_pts[i])) {
      std::cout << "point " << i+1 << " is within rectangle 3\n";
    } else {
      std::cout << "point " << i+1 << " is NOT within rectangle 3\n";
    }
  }

  std::cout << "---------------------------------" << std::endl;
  std::cout << "testing add_point function\n---------------------------------" << std::endl;
  for (unsigned int i = 0; i < test_pts.size(); i++) {
    if (rec1.add_point(test_pts[i])) {
      std::cout << "point " << i+1 << " was added to rectangle 1\n";
    } else {
      std::cout << "point " << i+1 << " was NOT added to rectangle 1 (not within)\n";
    }
  }
  for (unsigned int i = 0; i < test_pts.size(); i++) {
    if (rec2.add_point(test_pts[i])) {
      std::cout << "point " << i+1 << " was added to rectangle 2\n";
    } else {
      std::cout << "point " << i+1 << " was NOT added to rectangle 2 (not within)\n";
    }
  }
  for (unsigned int i = 0; i < test_pts.size(); i++) {
    if (rec3.add_point(test_pts[i])) {
      std::cout << "point " << i+1 << " was added to rectangle 3\n";
    } else {
      std::cout << "point " << i+1 << " was NOT added to rectangle 3 (not within)\n";
    }
  }

  std::cout << "---------------------------------" << std::endl;
  std::cout << "printing updated rectangles\n---------------------------------" << std::endl;
  print_rectangle(rec1);
  print_rectangle(rec2);
  print_rectangle(rec3);
  std::cout << "---------------------------------" << std::endl;
  
  std::cout << "testing points_in_both function\n---------------------------------" << std::endl;
  std::vector<Point2D> in_1_and_2 = points_in_both(rec1, rec2);
  std::vector<Point2D> in_1_and_3 = points_in_both(rec1, rec3);
  std::vector<Point2D> in_2_and_3 = points_in_both(rec2, rec3);
  std::cout << "points in both rectangle 1 and 2" << std::endl;
  for (unsigned int i = 0; i < in_1_and_2.size(); i++) {
    std::cout << std::setw(4) << std::left << in_1_and_2[i].x() << std::setw(4) << in_1_and_2[i].y() << std::endl;
  }
  std::cout << "points in both rectangle 1 and 3" << std::endl;
  for (unsigned int i = 0; i < in_1_and_3.size(); i++) {
    std::cout << std::setw(4) << std::left << in_1_and_3[i].x() << std::setw(4) << in_1_and_3[i].y() << std::endl;
  }
  std::cout << "points in both rectangle 2 and 3" << std::endl;
  for (unsigned int i = 0; i < in_2_and_3.size(); i++) {
    std::cout << std::setw(4) << std::left << in_2_and_3[i].x() << std::setw(4) << in_2_and_3[i].y() << std::endl;
  }


  return 0;
}
