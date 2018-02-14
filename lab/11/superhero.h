#ifndef __superhero_h_
#define __superhero_h_
#include <iostream>

class Superhero {
public:
  Superhero(std::string name_ = "", std::string id = "", std::string power_ = "") :
    name(name_), power(power_), identity(id) { good = true; }
  
  // accessors
  std::string getName() const { return name; }
  std::string getPower() const { return power; }
  
  bool isGood() const { return good; }

  // operators
  bool operator==(/*const Superhero &hero, */const std::string &guess) {
    if (guess == identity) return true;
    else return false;
  }
  bool operator!=(/*const Superhero &hero, */const std::string &guess) {
    if (guess != identity) return true;
    else return false;
  }
  void operator-() {
    good = !good;
  }
  friend class Team;

private:
  std::string name;
  std::string power;
  std::string identity;
  bool good;
  std::string getTrueIdentity() const { return identity; }
};

std::ostream& operator<<(std::ostream &ostr, Superhero &hero) {
  if (hero.isGood())
    ostr << "Superhero " << hero.getName() << " has power " << hero.getPower() << std::endl;
  else 
    ostr << "Supervillain " << hero.getName() << " has power " << hero.getPower() << std::endl;
  return ostr;
}
bool operator> (const Superhero& a, const Superhero& b){
  if( a.getPower() == "Fire" && b.getPower() == "Wood"){ return true; }
  else if( a.getPower() == "Wood" && b.getPower() == "Water"){ return true; }
  else if( a.getPower() == "Water" && b.getPower() == "Fire"){ return true; }
  else if( a.getPower().size() > b.getPower().size() ) { return true; }
  else if( a.getPower().size() == b.getPower().size() && a.getPower() < b.getPower() ) {
    return true; }
  else return false;
  
}
#endif
