#ifndef __time_h
#define __time_h


class Time {
public:
  Time();
  Time(int _hour, int _minute, int _second);
  
  // getters
  const int getHour() const;
  const int getMinute() const;
  const int getSecond() const;

  // setters
  void setHour(int new_hr);
  void setMinute(int new_min);
  void setSecond(int new_sec);

  // printer
  void PrintAMPM();

  

private:
  int hour, minute, second;


};

// sorting
bool isEarlierThan(const Time &t1, const Time &t2);

#endif
