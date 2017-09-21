#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include "decathlete.h"

const std::string track_events[4] = {"100","400","110H","1500"};
const std::string convert_cm[3] = {"LJ", "HJ", "PV"};

// arrays of values for constants A, B, and C, in order of events
const double A[10] = {25.4347, 0.14354, 51.39, 0.8465, 1.53775, 5.74352, 12.91, 0.2797, 10.14, 0.03768};
const double B[10] = {18., 220., 1.5, 75., 82., 28.5, 4., 100., 7., 480.};
const double C[10] = {1.81, 1.4, 1.05, 1.42, 1.81, 1.92, 1.1, 1.35, 1.08, 1.85};

// track points = int(A*(B-score)^C) ; field points = int(A*(score-B)^C)
bool is_track_event(std::string &event) {
  for (int i = 0; i < 4; i++) {
    if (event == track_events[i]) {
      return true;
    }
  }
  return false;
}

Athlete::Athlete() {
  name = std::vector<std::string> (2, "none");
  country = "DNE";
  scores = std::vector<std::string> (10, "0.0");
  total_score = 0;
  points = std::vector<int> (10);
  event_place = std::vector<int> (10);
  max_discrepancy = 0;
  highest_event[0] = 0; highest_event[1] = 100;
  lowest_event[0] = 0; lowest_event[1] = 0;
}

Athlete::Athlete(std::vector<std::string> _name, std::string _country,
    std::vector<std::string> _scores) {
  name = _name;
  country = _country;
  scores = _scores;
  total_score = 0;
  points = std::vector<int> (10);
  event_place = std::vector<int> (10);
  max_discrepancy = 0;
  highest_event[0] = 0; highest_event[1] = 100;
  lowest_event[0] = 0; lowest_event[1] = 0;
}


// accessing functions

const std::vector<std::string> &Athlete::get_name() const {
  return name;
}

const std::string &Athlete::get_country() const {
  return country;
}

const std::vector<std::string> &Athlete::get_scores() const {
  return scores;
}

const std::vector<int> &Athlete::get_points() const {
  return points;
}

// set
void Athlete::set_place(int place) {
  place_overall = place;
}

void Athlete::set_event_place(int ath, int event) {
  event_place[event] = ath;
  if (ath < lowest_event[1]) {
    lowest_event[1] = ath;
    lowest_event[0] = event;
  }
  if (ath > highest_event[1]) {
    highest_event[1] = ath;
    highest_event[0] = event;
  }
  if (place_overall < ath && ath - place_overall > max_discrepancy)
    max_discrepancy = ath - place_overall;
}

// print
void Athlete::print_scores(std::ostream &ostr, int first_max, int last_max) const {
  ostr << "\n" << std::setw(first_max + 4) << std::left << name[0] << std::setw(last_max + 4) << std::left << name[1];
  ostr << std::setw(3) << std::right << country;
  for (unsigned int i = 0; i < scores.size(); i++) {
    if (scores[i].size() <= 6) {
      ostr << std::setw(7) << scores[i];
    } else {
      ostr << std::setw(9) << scores[i];
    }
  }
}
void Athlete::calc_points(std::vector<std::string> &events) {
  points = std::vector<int> (11);
  int total_points = 0;
  std::vector<std::string> scores_copy = scores; // copy for safety
  for (unsigned int i = 0; i < scores_copy.size(); i++) {
    double double_score; 
    if (events[i] != "1500") {
      if (scores_copy[i].size() > 0){
        double_score = std::atof(scores_copy[i].c_str());
        if (is_track_event(events[i])) {
          points[i] = int(A[i] * pow((B[i] - double_score), C[i]));
          total_points += points[i];
        } else {
          // must account for LJ, HJ, PV scores
          if (events[i] == convert_cm[0] || events[i] == convert_cm[1] || 
              events[i] == convert_cm[2]) {
            double_score = 100.0*double_score;
          }
          points[i] = int(A[i]*pow((double_score - B[i]), C[i]));
          total_points += points[i];
        }
      } else { points[i] = 0;}
    } else {
      if (scores_copy[i].size() > 0) {
        std::string min = "123";
        min[0] = scores_copy[i][0]; min[1] = '.'; min[2] = '0'; // must be a better way?
        double min_to_sec = std::atof(min.c_str())*60;
        std::string sec = "12345";
        sec[0] = scores_copy[i][2];
        sec[1] = scores_copy[i][3];
        sec[2] = scores_copy[i][4];
        sec[3] = scores_copy[i][5];
        sec[4] = scores_copy[i][6];
        double secs = std::atof(sec.c_str());
        double time_in_sec = min_to_sec + secs;
        points[i] = int(A[i] * pow((B[i] - time_in_sec), C[i]));
        total_points += points[i];
      } else { points[i] = 0; }
    }
  }
  points[10] = total_points;
  
}

void Athlete::print_points(std::ostream &ostr, std::vector<std::string> &events,
    int first_max, int last_max) const {
  ostr << "\n" << std::setw(first_max + 4) << std::left << name[0] << std::setw(last_max + 4) << std::left << name[1];
  ostr << std::setw(3) << std::right << country;
  for (unsigned int i = 0; i < points.size()-1; i++) {
    ostr << std::setw(7) << points[i];
  }
  ostr << std::setw(9) << points[10];
}

void Athlete::print_custom(std::ostream &ostr, std::vector<std::string> &events, 
    int first_max, int last_max) const {
  bool lucky = true;
  for (unsigned int i = 0; i < event_place.size(); i++) {
    if (event_place[i] <= place_overall) {
      lucky = false;
      break;
    } else {
      continue;
    }
  }
  if(lucky) {
    ostr << "\n" << std::setw(first_max + 4) << std::left << name[0] << std::setw(last_max + 4) << std::left << name[1];
    ostr << std::setw(3) << std::right << country;
    ostr << std::setw(4) << events[highest_event[0]] << " " << highest_event[1] << "overall" << place_overall;
  }
}
// changing functions

void Athlete::add_score(std::string &score, int event_index) {
  scores[event_index] = score;
}

void Athlete::order_scores_seemingly_arbitrarily(std::vector<std::string> &corrected){
  scores = corrected;
}

// calculating functions


// sorting!!!
bool sort_by_country (const Athlete &a, const Athlete &b) {
  //sort by country name, then last name, then first name!
  std::vector<std::string> name1 = a.get_name();
  std::vector<std::string> name2 = b.get_name();
  return a.get_country() < b.get_country() || 
    (a.get_country() == b.get_country() && name1[1] < name2[1]) ||
    (a.get_country() == b.get_country() && name1[1] == name2[1] && name1[0] < name2[0]);
}

bool sort_by_points (const Athlete&a, const Athlete &b) {
  std::vector<int> points1 = a.get_points();
  std::vector<int> points2 = b.get_points();
  int t_points1 = points1[10];
  int t_points2 = points2[10];
  if (t_points2 > t_points1) {
    return false;
  } else {
    return true;
  }
}

bool sort_by_event1_points (const Athlete &a, const Athlete &b) {
  /*std::vector<int> points1 = a.get_points();
  std::vector<int> points2 = b.get_points();
  a.get_name()[0];
  int eventpoints1, eventpoints2; 
  if (points1.size() > 0) {
    eventpoints1 = points1[0];
  } else {
    eventpoints1 = 0;
  }
  if (points2.size() > 0) {
    eventpoints2 = points2[0];
  } else {
    eventpoints2 = 0;
  }
  */
  if (b.get_points()[0] > a.get_points()[0]) {
    return false;
  } else {
    return true;
  }
}
bool sort_by_event2_points (const Athlete &a, const Athlete &b) {
  std::vector<int> points1 = a.get_points();
  std::vector<int> points2 = b.get_points();
  int eventpoints1 = points1[1];
  int eventpoints2 = points2[1];
  if (eventpoints2 > eventpoints1) {
    return false;
  } else {
    return true;
  }
}
bool sort_by_event3_points (const Athlete &a, const Athlete &b) {
  std::vector<int> points1 = a.get_points();
  std::vector<int> points2 = b.get_points();
  int eventpoints1 = points1[2];
  int eventpoints2 = points2[2];
  if (eventpoints2 > eventpoints1) {
    return false;
  } else {
    return true;
  }
}
bool sort_by_event4_points (const Athlete &a, const Athlete &b) {
  std::vector<int> points1 = a.get_points();
  std::vector<int> points2 = b.get_points();
  int eventpoints1 = points1[3];
  int eventpoints2 = points2[3];
  if (eventpoints2 > eventpoints1) {
    return false;
  } else {
    return true;
  }
}
bool sort_by_event5_points (const Athlete &a, const Athlete &b) {
  std::vector<int> points1 = a.get_points();
  std::vector<int> points2 = b.get_points();
  int eventpoints1 = points1[4];
  int eventpoints2 = points2[4];
  if (eventpoints2 > eventpoints1) {
    return false;
  } else {
    return true;
  }
}
bool sort_by_event6_points (const Athlete &a, const Athlete &b) {
  std::vector<int> points1 = a.get_points();
  std::vector<int> points2 = b.get_points();
  int eventpoints1 = points1[5];
  int eventpoints2 = points2[5];
  if (eventpoints2 > eventpoints1) {
    return false;
  } else {
    return true;
  }
}
bool sort_by_event7_points (const Athlete &a, const Athlete &b) {
  std::vector<int> points1 = a.get_points();
  std::vector<int> points2 = b.get_points();
  int eventpoints1 = points1[6];
  int eventpoints2 = points2[6];
  if (eventpoints2 > eventpoints1) {
    return false;
  } else {
    return true;
  }
}
bool sort_by_event8_points (const Athlete &a, const Athlete &b) {
  std::vector<int> points1 = a.get_points();
  std::vector<int> points2 = b.get_points();
  int eventpoints1 = points1[7];
  int eventpoints2 = points2[7];
  if (eventpoints2 > eventpoints1) {
    return false;
  } else {
    return true;
  }
}
bool sort_by_event9_points (const Athlete &a, const Athlete &b) {
  std::vector<int> points1 = a.get_points();
  std::vector<int> points2 = b.get_points();
  int eventpoints1 = points1[8];
  int eventpoints2 = points2[8];
  if (eventpoints2 > eventpoints1) {
    return false;
  } else {
    return true;
  }
}
bool sort_by_event10_points (const Athlete &a, const Athlete &b) {
  std::vector<int> points1 = a.get_points();
  std::vector<int> points2 = b.get_points();
  int eventpoints1 = points1[9];
  int eventpoints2 = points2[9];
  if (eventpoints2 > eventpoints1) {
    return false;
  } else {
    return true;
  }
}

bool sort_by_discrepancy( const Athlete &a, const Athlete &b) {
  return b.get_max_discrep() >  a.get_max_discrep();
}
