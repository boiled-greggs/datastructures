#include <iostream>
#include <string>
#include <map>
#include <list>
#include "costume_shop.h"


// prototypes for the helper functions
void addCostume(CostumeShop &costume_shop);
void rentCostume(CostumeShop& costume_shop);
void Lookup(CostumeShop& costume_shop);
void printPeople(CostumeShop& costume_shop);

int main() {
  // two data structures store all of the information for efficiency
  CostumeShop costume_shop;
  char c;
  while (std::cin >> c) {
    if (c == 'a') {
      addCostume(costume_shop);
    } else if (c == 'r') {
      rentCostume(costume_shop);
    } else if (c == 'l') {
      Lookup(costume_shop);
    } else if (c == 'p') {
      printPeople(costume_shop);
    } else {
      std::cerr << "error unknown char " << c << std::endl;
      exit(0);
    }
  }
}


void addCostume(CostumeShop& costume_shop) {
  std::string costume_name;
  int num;
  std::cin >> costume_name >> num;
  costume_shop.add_costume(costume_name, num);
}


void rentCostume(CostumeShop& costume_shop) {
  std::string first_name;  
  std::string last_name;
  std::string costume_name;
  std::cin >> first_name >> last_name >> costume_name;
  Name name(first_name, last_name);
  costume_shop.rent_costume(name, costume_name);
}


void Lookup(CostumeShop& costume_shop) {
  std::string costume_name;
  std::cin >> costume_name;
  costume_shop.lookup(costume_name);
}


void printPeople(CostumeShop &costume_shop) {
  costume_shop.print_people();
}
