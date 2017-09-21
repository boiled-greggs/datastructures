#include <iostream>
#include <cassert>
#include <sstream>
#include <stdlib.h>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>


// A few global constants
const int feet_per_mile = 5280;
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
    int get_x() const { return x; }
    int get_y() const { return y; }
    int get_s() const { return s; }

    // set
    void set_position(int _x, int _y) {
      x = _x;
      y = _y;
    }
    void set_speed(int speed) {
      s = speed;
    }


  private:
    int x, y, s; // coordinates and speed in ft/min
};


/* Add your code here to finish the implementation. */
void print_pace(int avg_speed) {
  if (avg_speed == 0) {
    std::cout << "N/A";
  } else {
    std::stringstream pace_out;
    float pace = 1/double(avg_speed)*double(feet_per_mile);
    int min = int(pace);
    int sec = int((pace - double(int(pace)))*double(60));
    pace_out << std::setw(2) << min << ":" << std::setfill('0') << std::setw(2) << sec;
    std::cout << pace_out.str();
  }
}

void print(GPSData data[], int n) {
  std::cout << std::setw(7) << "x-pos" << std::setw(8) << "y-pos" << std::setw(9) << "ft/min" << std::setw(10) << "min/mile" << std::endl;
  for (int i = 0; i < n; i++) {
    std::cout << std::setw(7) << data[i].get_x() << std::setw(8) << data[i].get_y() << std::setw(9) << data[i].get_s() << std::setw(10);
    print_pace(data[i].get_s());
    std::cout << std::endl;
  }
}


double distance(GPSData data[], int n, int &avg_feet_per_minute) {
  data[0].set_speed(0);
  double total_distance = 0;
  for (int i = 1; i < n; i++) {
    double dist = sqrt(pow((data[i].get_x()-data[i-1].get_x()),2) + pow((data[i].get_y()-data[i-1].get_y()),2));
    total_distance += dist;
    data[i].set_speed(int(dist/seconds_between_samples*60));
  }
  avg_feet_per_minute = int(total_distance/((n-1)*4.25)*60);
  return total_distance;
}

double filter(GPSData input[], GPSData output[], int n) {
  output[0].set_position(input[0].get_x(), input[0].get_y());
  output[0].set_speed(input[0].get_s());
  output[n-1].set_position(input[n-1].get_x(), input[n-1].get_y());
  output[n-1].set_speed(input[n-1].get_s());
  for (int i = 1; i < n-1; i++) {
    int new_x = (input[i-1].get_x()+input[i].get_x()+input[i+1].get_x())/3;
    int new_y = (input[i-1].get_y()+input[i].get_y()+input[i+1].get_y())/3;
    output[i].set_position(new_x, new_y);
  }
  int avg_input_speed, avg_output_speed;
  double input_pathlength = distance(input, n, avg_input_speed);
  double output_pathlength = distance(output, n, avg_output_speed);
  double change = 100*(input_pathlength-output_pathlength)/(input_pathlength);
  return change;
}

// ==========================================================================================

void recursive_filter(GPSData* input, GPSData* output, int n, double percent_change_threshold) {
  // make a temporary array to store the intermediate filtering result
  GPSData tmp[n];
  // run the filter once
  double percent_change = filter(input,tmp,n);
  std::cout << "RECURSE " << std::setw(5) << std::fixed << std::setprecision(2)
            << percent_change << "% change" << std::endl;
  if (fabs(percent_change) < percent_change_threshold) {
    // if the percent change is under the target threshold, we're done
    for (int i = 0; i < n; i++) {
      // copy the data from the temporary arraya into the final answer
      output[i] = tmp[i];
    }
  } else {
    // otherwise, print the intermediate result (for debugging)
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


  // Load the GPS data file contents into a vector.
  // NOTE: this is the only place we use a vector in Part 1 of the homework.
  // This is just for convenience &/ flexibility for testing.
  std::vector<int> file_contents;
  int x;
  while (istr >> x) { file_contents.push_back(x); }


  // The optional second argument is the number of data points to work with.
  int count = -1;
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

  
  // Prepare an array of the original data (the selected amount of data).
  GPSData input[count];
  for (int i = 0; i < count; i++) {
    input[i].set_position(file_contents[i*2],file_contents[i*2+1]);
  }
  std::cout << "-----------------------------------" << std::endl;
  int original_avg_speed;
  double original_distance = distance(input,count,original_avg_speed) / double (feet_per_mile);
  std::cout << "ORIGINAL" << std::endl;
  print(input,count);


  // Prepare arrays for the filter data.
  GPSData filtered[count];
  GPSData recursive_filtered[count];

  
  // Perform a single pass of filtering
  std::cout << "-----------------------------------" << std::endl;
  filter(input,filtered,count);
  int filtered_avg_speed;
  double filtered_distance = distance(filtered,count,filtered_avg_speed) / double (feet_per_mile);
  std::cout << "FILTERED" << std::endl;
  print(filtered,count);

  
  // Perform multiple passes of filtering (until the distance changes by less than the target percentage).
  std::cout << "-----------------------------------" << std::endl;
  recursive_filter(input,recursive_filtered,count,percent_change_threshold);
  int recursive_filtered_avg_speed;
  double recursive_filtered_distance = distance(recursive_filtered,count,recursive_filtered_avg_speed) / double (feet_per_mile);
  std::cout << "RECURSIVE FILTERED" << std::endl;
  print(recursive_filtered,count);


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
}

