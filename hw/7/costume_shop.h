#ifndef _costume_shop__
#define _costume_shop__

class Name {
public:
  Name(const std::string &first_, const std::string &last_) :
    _first(first_), _last(last_) {}
  const std::string &first() const { return _first; }
  const std::string &last() const { return _last; }
private:
  std::string _first;
  std::string _last;
};
std::ostream& operator<< (std::ostream& ostr, const Name& name);
bool operator< (const Name &n1, const Name&n2);

// container for everything that needs to be tracked for the 
// costume
class CostumeInfo {
public:
  CostumeInfo(int num_tot = 0, int num_left = 0) :
    num_tot(num_tot), num_left(num_left) {}
  
  int get_numleft() const { return num_left; }
  int get_numtotal() const { return num_tot; }
  std::list<Name> &get_renters() { return renters; }
  
  void add_copies(int num) { num_tot += num; num_left += num; }
  bool rent_one(const Name &name);
  void return_one(const Name &name);
  void print_info() const;

private:
  int num_tot;
  int num_left;
  std::list<Name> renters;

};

class CostumeShop {
public:
  CostumeShop();

  void add_costume(const std::string &costume_name, int num);
  void rent_costume(const Name& name, const std::string &costume_name);
  void lookup(const std::string &costume_name) const;
  void print_people();

private:
  std::map<std::string, CostumeInfo> costumes;
  std::map<Name, std::string> customers;

};

#endif
