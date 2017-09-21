#include <iostream>
#include <sstream>
#include <iomanip>
#include "time.h"

// construct
Time::Time() {
  hour = 0;
  minute = 0;
  second = 0;
}

Time::Time(int _hour, int _minute, int _second) {
  hour = _hour;
  minute = _minute;
  second = _second;
}

// access
const int Time::getHour() const {
  return hour;
}

const int Time::getMinute() const {
  return minute;
}

const int Time::getSecond() const {
  return second;
}

// set
void Time::setHour(int new_hr) {
  hour = new_hr;
}
void Time::setMinute(int new_min) {
  minute = new_min;
}
void Time::setSecond(int new_sec) {
  second = new_sec;
}

// print
void Time::PrintAMPM() {
  std::string AMPM;
  int right_hour = hour;
  if (hour < 12 || hour == 24) {
    AMPM = "AM";
    if (hour == 0 || hour == 24) right_hour = 12;
  } else if (hour >= 12) {
    AMPM = "PM";
    if (hour > 12) right_hour = hour - 12;
  }
  std::stringstream time_out;
  time_out << right_hour << ":" << std::setfill('0') << std::setw(2) << minute << ":" << std::setfill('0') << std::setw(2) << second << " " << AMPM << std::endl;
  std::cout << time_out.str();
}

bool isEarlierThan(const Time &t1, const Time &t2) {
  int time1, time2;
  if (t1.getHour() < 24) {
    time1 = t1.getHour()*3600 + t1.getMinute()*60 + t1.getSecond();
  } else {
    time1 = (t1.getHour()-24)*3600 + t1.getMinute()*60 + t1.getSecond();
  }
  if (t2.getHour() < 24) { 
    time2 = t2.getHour()*3600 + t2.getMinute()*60 + t2.getSecond();
  } else { 
    time2 = (t2.getHour()-24)*3600 + t2.getMinute()*60 + t2.getSecond();
  }
  if (time1 < time2) {
    return true;
  } else if (time1 == time2) {
    return true;
  } else {
    return false;
  }
}
