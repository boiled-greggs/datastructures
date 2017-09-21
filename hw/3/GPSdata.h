// File: GPSdata.h
// simple class for the gps data
#ifndef __GPSdata_h_
#define __GPSdata_h_

class GPSdata {
  public:
    // construct
    GPSdata() {
      x = 0;
      y = 0;
      s = 0;
    }

    // access
    int get_x() const { return x; }
    int get_y() const { return y; }
    int get_s() const { return s; }

    // set
    void set_position(int _x, int _y) {
      x = _x;
      y = _y;
    }


  private:
    int x, y, s; // coordinates and speed in ft/min


};

#endif
