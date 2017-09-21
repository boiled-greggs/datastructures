#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <string>
#include <vector>
#include "decathlete.h"

void read_input(std::vector<Athlete> &athletes, std::string &file,
    std::vector<std::string> &events, int &first_max, int &last_max) {
  std::ifstream istr(file);
  if (!istr) {
    std::cerr << "ERROR: cannot open results file " << file << std::endl;
    exit(0);
  }
  std::vector<std::string> athlete_tracker; // use to check if athlete added or not
  std::string info;
  while(istr >> info) {
    if (info == "event") { // new event
      std::string event;
      istr >> event;
      events.push_back(event);
    } else {
      std::string lastname, firstname, country, score;
      firstname = info;
      istr >> lastname >> country >> score; // get rest of line
      if (firstname.size() > first_max) first_max = firstname.size();
      if (lastname.size() > last_max) last_max = lastname.size();
      std::string namecheck = firstname + " " + lastname;
      bool added = false; int ath_index;
      // check if athlete has been added
      for (unsigned int i = 0; i < athlete_tracker.size(); i++) {
        if (namecheck == athlete_tracker[i]) {
          added = true; ath_index = i;
          break;
        }
      }
      if (added) {
        // add info about athlete at ath_index
        athletes[ath_index].add_score(score, events.size()-1);
      } else {
        std::vector<std::string> name(2);
        std::vector<std::string> scores(10);
        scores[events.size()-1] = score;
        name[0] = firstname; name[1] = lastname;
        Athlete athlete(name, country, scores); // lots of these lines can be combined
        athletes.push_back(athlete);
        std::string add_name = firstname + " " + lastname;
        athlete_tracker.push_back(add_name);
      }
    }
  }
}

void abbreviate(std::vector<std::string> &events) {
  for (unsigned int i = 0; i < events.size(); i++) {
    if (events[i] == "POLE_VAULT") events[i] = "PV";
    if (events[i] == "JAVELIN_THROW") events[i] = "JT";
    if (events[i] == "1500_METERS") events[i] = "1500";
    if (events[i] == "SHOT_PUT") events[i] = "SP";
    if (events[i] == "HIGH_JUMP") events[i] = "HJ";
    if (events[i] == "400_METERS") events[i] = "400";
    if (events[i] == "110_METERS_HURDLES") events[i] = "110H";
    if (events[i] == "DISCUS_THROW") events[i] = "DT";
    if (events[i] == "100_METERS") events[i] = "100";
    if (events[i] == "LONG_JUMP") events[i] = "LJ";
  }
}

void pointless_reordering_to_match_formatting(std::vector<Athlete> &athletes, std::vector<std::string> &events) {
  const std::string correct_order[10] = {"100","LJ","SP","HJ","400","110H","DT","PV","JT","1500"};
  std::vector<std::string> scores_copy;
  for (unsigned int ath = 0; ath < athletes.size(); ath++) {
    scores_copy = athletes[ath].get_scores();
    std::vector<std::string> scores_corrected(10);
    for (unsigned int correct = 0; correct < 10; correct++){
      for (unsigned int i = 0; i < events.size(); i++) {
        if (events[i] == correct_order[correct]) {
          scores_corrected[correct] = scores_copy[i];
        }
      }
    }
    athletes[ath].order_scores_seemingly_arbitrarily(scores_corrected);
  }
  for (unsigned int i = 0; i < events.size(); i++) {
    events[i] = correct_order[i];
  }
}

void write_scores(std::vector<Athlete> athletes, std::ostream &ostr,
    std::vector<std::string> &events, int first_max, int last_max) {
  std::sort(athletes.begin(), athletes.end(), sort_by_country);
  ostr << std::setw(first_max + last_max + 11) << std::left << "DECATHLETE SCORES";
  for (unsigned int i = 0; i < events.size(); i++) {
    if (events[i] != "1500") {
      ostr << std::setw(7) << std::right << events[i];
    } else {
      ostr << std::setw(9) << std::right << events[i];
    }
  }
  for (unsigned int ath = 0; ath < athletes.size(); ath++) {
    athletes[ath].print_scores(ostr, first_max, last_max);
  }
}

void write_points(std::vector<Athlete> &athletes, std::ostream &ostr, 
    std::vector<std::string> &events, int first_max, int last_max) {
  for (unsigned int i = 0; i < athletes.size(); i++) {
    athletes[i].calc_points(events);
  }
  std::sort(athletes.begin(), athletes.end(), sort_by_points);
  ostr << std::setw(first_max + last_max + 11) << std::left << "DECATHLETE POINTS";
  for (unsigned int i = 0; i < events.size(); i++) {
    ostr << std::setw(7) << std::right << events[i];
  }
  ostr << std::setw(9) << "TOTAL";
  for (unsigned int ath = 0; ath < athletes.size(); ath++) {
    athletes[ath].print_points(ostr, events, first_max, last_max);
  }
}

void write_custom(std::vector<Athlete> &athletes, std::ostream &ostr, 
    std::vector<std::string> &events, int first_max, int last_max) {
  for (unsigned int i = 0; i < athletes.size(); i++) {
    athletes[i].calc_points(events);
  }
  std::sort(athletes.begin(), athletes.end(), sort_by_points);
  for (unsigned int i = 0; i < athletes.size(); i++) {
    athletes[i].set_place(i);
  }
  std::sort(athletes.begin(), athletes.end(), sort_by_event1_points);
  for (unsigned int i = 0; i < athletes.size(); i++) {
    athletes[i].set_event_place(i, 0);
  }
  std::sort(athletes.begin(), athletes.end(), sort_by_event2_points);
  for (unsigned int i = 0; i < athletes.size(); i++) {
    athletes[i].set_event_place(i, 1);
  }
  std::sort(athletes.begin(), athletes.end(), sort_by_event3_points);
  for (unsigned int i = 0; i < athletes.size(); i++) {
    athletes[i].set_event_place(i, 2);
  }
  std::sort(athletes.begin(), athletes.end(), sort_by_event4_points);
  for (unsigned int i = 0; i < athletes.size(); i++) {
    athletes[i].set_event_place(i, 3);
  }
  std::sort(athletes.begin(), athletes.end(), sort_by_event5_points);
  for (unsigned int i = 0; i < athletes.size(); i++) {
    athletes[i].set_event_place(i, 4);
  }
  std::sort(athletes.begin(), athletes.end(), sort_by_event6_points);
  for (unsigned int i = 0; i < athletes.size(); i++) {
    athletes[i].set_event_place(i, 5);
  }
  std::sort(athletes.begin(), athletes.end(), sort_by_event7_points);
  for (unsigned int i = 0; i < athletes.size(); i++) {
    athletes[i].set_event_place(i, 6);
  }
  std::sort(athletes.begin(), athletes.end(), sort_by_event8_points);
  for (unsigned int i = 0; i < athletes.size(); i++) {
    athletes[i].set_event_place(i, 7);
  }
  std::sort(athletes.begin(), athletes.end(), sort_by_event9_points);
  for (unsigned int i = 0; i < athletes.size(); i++) {
    athletes[i].set_event_place(i, 8);
  }
  std::sort(athletes.begin(), athletes.end(), sort_by_event10_points);
  for (unsigned int i = 0; i < athletes.size(); i++) {
    athletes[i].set_event_place(i, 9);
  }

  std::sort(athletes.begin(), athletes.end(), sort_by_discrepancy);
  ostr << "Athletes who placed higher overall than they did in any event:" << std::endl;
  ostr << std::setw(first_max+last_max+12) << std::left << "ATHLETE" << "HIGH EVENT " << "OVERALL";
  for (unsigned int ath = 0; ath < athletes.size(); ath++) {
    athletes[ath].print_custom(ostr, events, first_max, last_max);
  }
  
}

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cerr << "ERROR: incorrect number of arguments: should be 4" << std::endl;
    exit(1);
  }

  std::string input(argv[1]);
  
  std::vector<Athlete> athletes; // vector of Athlete objects
  std::vector<std::string> events; // used to keep a list of events in order
  int first_max = 0; int last_max = 0; // store largest name sizes, for formatting later
  read_input(athletes, input, events, first_max, last_max);
  abbreviate(events);
  pointless_reordering_to_match_formatting(athletes, events);

  std::ofstream ostr(argv[2]);
  std::string mode(argv[3]);
  if (mode == "scores") {
    //display scores
    write_scores(athletes, ostr, events, first_max, last_max);
  } else if (mode == "points") {
    //calculate and display points
    write_points(athletes, ostr, events, first_max, last_max);
  } else if (mode == "custom") {
    //calculate and display custom stats
    write_custom(athletes, ostr, events, first_max, last_max);
  } else {
    std::cerr << "ERROR: incorrectly specified mode - must specify score, points, or custom." << std::endl;
    exit(2);
  }

  return 0;
}
