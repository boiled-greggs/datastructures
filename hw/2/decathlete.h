// decathlete.h

class Athlete {
public:
  Athlete();
  Athlete(std::vector<std::string> _name, std::string _country,
        std::vector<std::string> _scores);

  // access things
  const std::vector<std::string> &get_name() const;
  const std::string &get_country() const;
  const std::vector<std::string> &get_scores() const;
  const std::vector<int> &get_points() const;
  const int &get_place_overall() const { return place_overall; }
  const int get_max_discrep() const { return max_discrepancy; }

  // setter
  void set_place(int place);
  void set_event_place(int i, int event);
  // print things
  void print_scores(std::ostream &ostr, int first_max, int last_max) const;
  void print_points(std::ostream &ostr, std::vector<std::string> &events, int first_max, int last_max) const;
  void print_custom(std::ostream &ostr, std::vector<std::string> &events, int first_max, int alst_max) const;
  // change things
  void add_score(std::string &score, int event_index);
  void order_scores_seemingly_arbitrarily(std::vector<std::string> &corrected);
  void calc_points(std::vector<std::string> &events);

private:
  std::vector<std::string> name;
  std::string country;
  std::vector<std::string> scores;
  int total_score;
  std::vector<int> points;
  std::vector<int> event_place;
  int place_overall;
  int max_discrepancy;
  int highest_event[2];
  int lowest_event[2];
};

// sorting
bool sort_by_country (const Athlete &a, const Athlete &b);
bool sort_by_points (const Athlete &a, const Athlete &b);
bool sort_by_event1_points (const Athlete &a, const Athlete &b);
bool sort_by_event2_points (const Athlete &a, const Athlete &b);
bool sort_by_event3_points (const Athlete &a, const Athlete &b);
bool sort_by_event4_points (const Athlete &a, const Athlete &b);
bool sort_by_event5_points (const Athlete &a, const Athlete &b);
bool sort_by_event6_points (const Athlete &a, const Athlete &b);
bool sort_by_event7_points (const Athlete &a, const Athlete &b);
bool sort_by_event8_points (const Athlete &a, const Athlete &b);
bool sort_by_event9_points (const Athlete &a, const Athlete &b);
bool sort_by_event10_points (const Athlete &a, const Athlete &b);
bool sort_by_discrepancy (const Athlete &a, const Athlete &b);
