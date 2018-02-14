#ifndef _polygon_h_
#define _polygon_h_

#include <vector>
#include "utilities.h"

class Polygon { 
public:
  Polygon(const std::string &name, const std::vector<Point> pts) :
    verts(pts), name(name), equal_sides(false) {} 
  virtual ~Polygon() = default;
  bool HasAllEqualSides() {return equal_sides;}
  std::string getName() { return name; }
protected:
  std::vector<Point> verts;
  std::string name;
  bool equal_sides;
};


class Triangle : public Polygon { 
public:
  Triangle(const std::string &name, const std::vector<Point> & pts) :
    Polygon(name, pts) {
    if ( pts.size() != 3 ) {
      throw 1;
    }
  } 
  double Area();
};


class Quadrilateral : public Polygon { 
public:
  Quadrilateral(const std::string &name, const std::vector<Point> & pts) :
    Polygon(name, pts) {
    if (pts.size() != 4)
      throw 1;
  }
};

class IsoscelesTriangle : public Triangle {
public:
  IsoscelesTriangle(const std::string &name, const std::vector<Point> & pts) :
    Triangle(name, pts) {
    if (pts.size() != 3) throw 1;
    Vector side1(pts[1], pts[0]);
    Vector side2(pts[2], pts[0]);
    Vector side3(pts[2], pts[1]);
    if (EqualSides(side1.Length(), side2.Length()) ||
          EqualSides(side1.Length(), side3.Length()) ||
          EqualSides(side2.Length(), side3.Length()) ) {
      std::cout << std::endl;
    } else throw 1;
  }  


};

class EquilateralTriangle : public IsoscelesTriangle {
public:
  EquilateralTriangle(const std::string &name, const std::vector<Point> & pts) :
    IsoscelesTriangle(name,pts) {
    if (pts.size() != 3) throw 1;
    Vector side1(pts[1], pts[0]);
    Vector side2(pts[2], pts[0]);
    Vector side3(pts[2], pts[1]);
    if (!EqualSides(side1.Length(), side2.Length()) ||
          !EqualSides(side1.Length(), side3.Length()) ||
          !EqualSides(side2.Length(), side3.Length()) ) {
      throw 1;
    } else {
      equal_sides = true;
    }
  }


};

class Rectangle : public Quadrilateral {
public:
  Rectangle(const std::string &name, const std::vector<Point> & pts) :
    Quadrilateral(name, pts) {
    if (pts.size() != 4) throw 1;
    if (!RightAngle(Angle(pts[0], pts[1], pts[2])) ||
        !RightAngle(Angle(pts[1], pts[2], pts[3])) ||
        !RightAngle(Angle(pts[2], pts[3], pts[4])) ||
        !RightAngle(Angle(pts[3], pts[4], pts[0]))) {
      throw 1;
    }
  } 


};

class Square : public Rectangle {
public:
  Square(const std::string &name, const std::vector<Point> & pts) :
    Rectangle(name, pts) {
    if (pts.size() != 4) throw 1;
    Vector side1(pts[1], pts[0]);
    Vector side2(pts[2], pts[1]);
    Vector side3(pts[3], pts[2]);
    Vector side4(pts[3], pts[0]);
    if (!EqualSides(side1.Length(), side3.Length()) ||
        !EqualSides(side2.Length(), side4.Length()) ||
        !EqualSides(side3.Length(), side4.Length()) ) {
      throw 1;
    } else {
      equal_sides = true;
    }
  }

};

#endif
