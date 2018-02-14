#include <iostream>
#include <iomanip>
#include <map>
#include <list>
#include <sstream>

#include "costume_shop.h"

// write names
std::ostream& operator<< (std::ostream &ostr, const Name &name) {
  std::string str = name.first() + " " + name.last();
  ostr << std::left << str;
  return ostr;
}

// name sort for maps
bool operator< (const Name &n1, const Name &n2) {
  return n1.last() < n2.last() || (n1.last() == n2.last() && n1.first() < n2.first());
}

// if costume can be rented, reduce num left and add new renter
// ( this keeps chronological order of renters )
bool CostumeInfo::rent_one(const Name& name) {
  if (num_left > 0) {
    num_left--;
    renters.push_back(name);
    return true;
  } else {
    return false;
  }
}

// return costume. increments num left and remove the renter 
// from the list of renters
void CostumeInfo::return_one(const Name &name) {
  num_left++;
  std::list<Name>::iterator itr = renters.begin();
  while (itr != renters.end()) {
    if (itr->first() == name.first() && itr->last() == name.last()) {
      renters.erase(itr);
      break;
    } else ++itr;
  }
}

// print costume info
// prints the number of costumes available and who's renting them
void CostumeInfo::print_info() const {
  if (num_left > 1) std::cout << "  " << num_left << " copies available\n";
  else if (num_left > 0) std::cout << "  " << num_left << " copy available\n";
  if (num_left < num_tot) {
    if (num_tot-num_left > 1)
      std::cout << "  " << num_tot-num_left << " copies rented by:\n";
    else if (num_tot-num_left == 1)
      std::cout << "  1 copy rented by:\n";
    std::list<Name>::const_iterator itr;
    for(itr = renters.begin(); itr != renters.end(); ++itr) {
      std::cout << "    " << *itr << std::endl;
    }
  }
}

CostumeShop::CostumeShop() {
  return;
}

// add costume. if the costume isn't in the shop, adds it to the shop with the
// "costumes" map. if it is, adds more copies.
void CostumeShop::add_costume(const std::string &costume_name, int num) {
  if ( costumes.find(costume_name) == costumes.end() ) {
    CostumeInfo info(num, num);
    costumes[costume_name] = info;
  } else {
    costumes[costume_name].add_copies(num);
  }
  if (num == 1) std::cout << "Added " << num << " " << costume_name << " costume.\n";
  else std::cout << "Added " << num << " " << costume_name << " costumes.\n";
}

// rent costume. first ensures the new customer is added, then finds the costume
// desired and if it exists and is available, checks that the customer does
// not already have the costume. If they don't then either the currently rented
// costume is returned and the new costume rented, or the new costume is simply
// rented. Then prints the result of renting.
void CostumeShop::rent_costume(const Name &name, const std::string &costume_name) {
  std::map<std::string, CostumeInfo>::iterator itr = costumes.find(costume_name);
  customers[name]; // count every new customer, even if they don't rent
  if (itr != costumes.end()) {
    if (customers[name] == costume_name){
      std::cout << name << " already has a " << costume_name << " costume.\n";
    } else if (costumes.find(costume_name) != costumes.end() && customers[name] != costume_name) {
      std::string tmp_cost = customers[name];
      bool success = costumes[costume_name].rent_one(name);
      if (success) {
        if (tmp_cost.size() > 0) costumes[tmp_cost].return_one(name);
        customers[name] = costume_name;
        if (tmp_cost.size() == 0) std::cout << name << " rents a " << costume_name << " costume.\n";
        else if (tmp_cost.size() > 0) 
          std::cout << name << " returns a " << tmp_cost << " costume before renting a " << costume_name << " costume.\n";
      } else {
        std::cout << "No " << costume_name << " costumes available." << std::endl;
      }
    }
  } else {
    std::cout << "The shop doesn't carry " << costume_name << " costumes.\n";
  }
}

// lookup. if the shop carries the costume, then this function prints the
// info for that function with print_info(). Otherwise it states the lack
// of costume
void CostumeShop::lookup(const std::string &costume_name) const {
  std::map<std::string, CostumeInfo>::const_iterator itr = costumes.find(costume_name);
  if (itr != costumes.end()) {
    if (itr->second.get_numleft() >= 0) {
      std::cout << "Shop info for " << costume_name << " costumes:" << std::endl;
      itr->second.print_info();
    }
  } else {
    std::cout << "The shop doesn't carry " << costume_name << " costumes." << std::endl;
  }
}

// print people prints the attendees of the party and what they're wearing.
// Since the map is already sorted, this is as simple as printing the keys
// and values of the customers map.
void CostumeShop::print_people() {
  std::map<Name, std::string>::const_iterator itr;
  if ( customers.size() == 1 )
    std::cout << "Costume info for the " << customers.size() << " party attendee:\n";
  else if ( customers.size() > 1 )
    std::cout << "Costume info for the " << customers.size() << " party attendees:\n";
  for (itr = customers.begin(); itr != customers.end(); ++itr) {
    if (itr->second.size() > 0)
      std::cout << "  " << itr->first << " is wearing a " << itr->second << " costume.\n";
    else 
      std::cout << "  " <<  itr->first << " does not have a costume.\n";
  }
}
