
#include <iostream>
#include <cassert>
#include <sstream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include "the_stack.h"


TheStack thestack;

// A few global constants
const intptr_t feet_per_mile = 5280;
const double seconds_between_samples = 4.25;

class GPSData {
  public:
    // construct
    GPSData() {
      x = 0;
      y = 0;
      s = 0;
    }

    // access
    intptr_t get_x() const { return x; }
    intptr_t get_y() const { return y; }
    intptr_t get_s() const { return s; }

    // set
    void set_position(intptr_t _x, intptr_t _y) {
      x = _x;
      y = _y;
    }
    void set_speed(intptr_t speed) {
      s = speed;
    }


  private:
    intptr_t x, y, s; // coordinates and speed in ft/min
};


/* Add your code here to finish the implementation. */
void print_pace(intptr_t avg_speed) {
  if (avg_speed == 0) {
    std::cout << "N/A";
  } else {
    std::stringstream pace_out;
    double pace = 1/double(avg_speed)*feet_per_mile; // convert
    intptr_t min = intptr_t(pace); // rounds down so this is the minutes of the pace
    intptr_t sec = intptr_t((pace - intptr_t(pace))*60); // subtract minutes from total pace and convert
    pace_out << min << ":" << std::setfill('0') << std::setw(2) << sec;
    std::cout << pace_out.str();
  }
}

void print(GPSData data[], intptr_t n) {
  std::cout << std::setw(7) << "x-pos" << std::setw(8) << "y-pos" << std::setw(9) << "ft/min" << std::setw(10) << "min/mile" << std::endl;
  for (intptr_t i = 0; i < n; i++) {
    std::cout << std::setw(7) << data[i].get_x() << std::setw(8) << data[i].get_y() << std::setw(9) << data[i].get_s() << std::setw(10);
    print_pace(data[i].get_s());
    std::cout << std::endl;
  }
}


double distance(GPSData data[], intptr_t n, intptr_t &avg_feet_per_minute) {
  // uses pythagorean thm to get distance for each of path, then finds speed by using
  // the time between samples. then, finds average speed from total distance and
  // returns total distance.
  data[0].set_speed(0);
  double total_distance = 0;
  for (intptr_t i = 1; i < n; i++) {
    double dist = sqrt(pow((data[i].get_x()-data[i-1].get_x()),2) + pow((data[i].get_y()-data[i-1].get_y()),2));
    total_distance += dist;
    data[i].set_speed(intptr_t(dist/4.25*60));
  }
  avg_feet_per_minute = intptr_t(total_distance/((n-1)*4.25)*60);
  return total_distance;
}

double filter(GPSData input[], GPSData output[], intptr_t n) {
  // sets initial and final data objects, then loops through the rest to find
  // the averaged new positions from input[], which are then set in output.
  // finally, sends both to distance to get new and old pathlength, then
  // uses results to get the percent change.
  output[0].set_position(input[0].get_x(), input[0].get_y());
  output[0].set_speed(input[0].get_s());
  output[n-1].set_position(input[n-1].get_x(), input[n-1].get_y());
  output[n-1].set_speed(input[n-1].get_s());
  for (intptr_t i = 1; i < n-1; i++) {
    intptr_t new_x = (input[i-1].get_x()+input[i].get_x()+input[i+1].get_x())/3;
    intptr_t new_y = (input[i-1].get_y()+input[i].get_y()+input[i+1].get_y())/3;
    output[i].set_position(new_x, new_y);
  }
  intptr_t avg_input_speed, avg_output_speed;
  double input_pathlength = distance(input, n, avg_input_speed);
  double output_pathlength = distance(output, n, avg_output_speed);
  double change = 100*(input_pathlength-output_pathlength)/(input_pathlength);
  return change;
}

// ==========================================================================================

void recursive_filter(GPSData* input, GPSData* output, intptr_t n, double percent_change_threshold) {
  thestack.set_label((intptr_t*)__builtin_frame_address(0),"FUNCTION RECURSIVE_FILTER");
  thestack.tag_return_address((intptr_t*)(__builtin_frame_address(0))+1);
  // make a temporary array to store the intptr_termediate filtering result
  GPSData tmp[n];
  thestack.set_label((intptr_t*)&tmp[0],"tmp[0]");
  thestack.set_label((intptr_t*)&tmp[n-1],"tmp[n-1]");
  std::cout << "recurive filter stack\n";
  thestack.print();
  // run the filter once
  double percent_change = filter(input,tmp,n);
  std::cout << "RECURSE " << std::setw(5) << std::fixed << std::setprecision(2)
            << percent_change << "% change" << std::endl;
  if (fabs(percent_change) < percent_change_threshold) {
    // if the percent change is under the target threshold, we're done
    for (intptr_t i = 0; i < n; i++) {
      // copy the data from the temporary arraya intptr_to the final answer
      output[i] = tmp[i];
    }
  } else {
    // otherwise, print the intptr_termediate result (for debugging)
    print(tmp,n);
    // and repeat!
    recursive_filter(tmp,output,n,percent_change_threshold);
  }
}

// ==========================================================================================

int main(int argc, char** argv) {
  // The mandatory first argument is the GPS data input file.
  if (argc < 2) {
    std::cerr << "ERROR!  This program must be called with at least one argument, the GPS data input file" << std::endl;
  }
  std::ifstream istr(argv[1]);
  assert (istr.good());


  // Load the GPS data file contents intptr_to a vector.
  // NOTE: this is the only place we use a vector in Part 1 of the homework.
  // This is just for convenience &/ flexibility for testing.
  std::vector<intptr_t> file_contents;
  intptr_t x;
  while (istr >> x) { file_contents.push_back(x); }


  // The optional second argument is the number of data pointptr_ts to work with.
  intptr_t count = -1;
  if (argc > 2) {
    count = atoi(argv[2]);
  }
  // If the argument is not provided, or if it is larger than the size
  // of the file, just use the whole file.
  if (count < 0 || file_contents.size() / 2 < count) count = file_contents.size() / 2;

  
  // The optional third argument is the distance percentage change stopping criterion
  double percent_change_threshold = 0.5;
  if (argc > 3) {
    percent_change_threshold = atof(argv[3]);
  }  
  assert (percent_change_threshold > 0.0);

//  thestack.set_label((intptr_t*)&percent_change_threshold, "\% change");
  // Prepare an array of the original data (the selected amount of data).
  GPSData input[count];
  for (intptr_t i = 0; i < count; i++) {
    input[i].set_position(file_contents[i*2],file_contents[i*2+1]);
  }
//   std::cout << "-----------------------------------" << std::endl;
//  thestack.set_label((intptr_t*)&input[0], "input[0]");
//  std::cout << "STACK BEFORE FUNCTION DISTANCE\n";
  intptr_t original_avg_speed;
  double original_distance = distance(input,count,original_avg_speed) / double (feet_per_mile);
//  std::cout << "STACK AFTER FUNCTION DISTANCE\n";
//  std::cout << "PRINTED STACK\n-----------------------------" << std::endl;
//  std::cout << "ORIGINAL" << std::endl;
//  print(input,count);


  // Prepare arrays for the filter data.

//  GPSData filtered[count];
  GPSData recursive_filtered[count];
//  thestack.set_label((intptr_t*)&filtered[0], "filtered[0]");
  // Perform a single pass of filtering
//  std::cout << "-----------------------------------" << std::endl;
//  std::cout << "STACK BEFORE FUNCTION FILTER (redundant)" << std::endl;
//  filter(input,filtered,count);
//  std::cout << "STACK AFTER FUNCTION FILTER" << std::endl;
//  thestack.print();
//  intptr_t filtered_avg_speed;
//  double filtered_distance = distance(filtered,count,filtered_avg_speed) / double (feet_per_mile);
//  std::cout << "PRINTED STACK\n-----------------------------" << std::endl;
//  std::cout << "FILTERED" << std::endl;
//  print(filtered,count);

  
  // Perform multiple passes of filtering (until the distance changes by less than the target percentage).
  std::cout << "-----------------------------------" << std::endl;
  recursive_filter(input,recursive_filtered,count,percent_change_threshold);
  intptr_t recursive_filtered_avg_speed;
  double recursive_filtered_distance = distance(recursive_filtered,count,recursive_filtered_avg_speed) / double (feet_per_mile);
//  std::cout << "RECURSIVE FILTERED" << std::endl;
//  print(recursive_filtered,count);

/*
  // Output
  std::cout << "-----------------------------------" << std::endl;
  std::cout << "ORIGINAL:           "
            << std::fixed << std::setprecision(2) << std::setw(5) << original_distance
            << " miles, " << std::setw(4) << original_avg_speed << " feet per minute, ";
  print_pace(original_avg_speed);
  std::cout << " minutes per mile" << std::endl;
  std::cout << "FILTERED:           "
            << std::fixed << std::setprecision(2) << std::setw(5) << filtered_distance
            << " miles, " << std::setw(4) << filtered_avg_speed   << " feet per minute, ";
  print_pace(filtered_avg_speed);
  std::cout << " minutes per mile" << std::endl;  
  std::cout << "RECURSIVE FILTERED: "
            << std::fixed << std::setprecision(2) << std::setw(5) << recursive_filtered_distance
            << " miles, " << std::setw(4) << recursive_filtered_avg_speed << " feet per minute, ";
  print_pace(recursive_filtered_avg_speed);
  std::cout << " minutes per mile" << std::endl;
*/
}

