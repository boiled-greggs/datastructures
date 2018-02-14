#include <iostream>
#include <cassert>
#include <string>
#include <set>

// simple homemade smart pointers
#include "ds_smart_pointers.h"


// ====================================================
// BALLOON: a toy class with dynamically allocated memory
// ====================================================

#define MAX_NUM_ROPES 10

class Balloon {
public:
  // CONSTRUCTOR & DESTRUCTOR
  Balloon(const std::string& name_) : name(name_) {
    std::cout << "Balloon constructor " << name << std::endl;
    num_ropes = 0;
    ropes = new Balloon*[MAX_NUM_ROPES];
  }
  ~Balloon() {
    std::cout << "Balloon destructor " << name << std::endl;
    // don't try to destroy attached balloons, just delete array
    delete [] ropes;
  }

  // ACCESSORS
  const std::string& getName() const { return name; }
  int numRopes() const { return num_ropes; }
  const Balloon* getRope(int i) const { return ropes[i]; }

  // print the balloons we are attached to
  void print() { 
    std::cout << "Balloon " << name << " is connected to: ";
    for (int i = 0; i < num_ropes; i++) {
      std::cout << ropes[i]->name << " ";
    }
    if (num_ropes == 0) std::cout << "nothing";
    std::cout << std::endl;
  }
  // add a rope connecting this balloon to another
  void addRope(Balloon* b) { 
    assert (num_ropes < MAX_NUM_ROPES);
    ropes[num_ropes] = b;
    num_ropes++;
  }
  // detach a rope connecting this balloon to another
  void removeRope(Balloon* b) { 
    for (int i = 0; i < MAX_NUM_ROPES; i++) {
      if (ropes[i] == b) { ropes[i] = ropes[num_ropes-1]; num_ropes--; break; }
    }
  }

 

//private:
  std::string name;
  int num_ropes;
  // a dynamically allocated C-style array of ropes connecting to other Balloons
  Balloon** ropes; 
};

///*

void deleteAll_helper(Balloon* b, std::set<Balloon*>& bals){
  for( int i = 0; i < b->num_ropes; i++){
    if( bals.find(b->ropes[i]) == bals.end()){
      bals.insert(b->ropes[i]);
      deleteAll_helper(b->ropes[i], bals);
    }
  }
}

void deleteAll(Balloon* b){
  std::set<Balloon*> bals;
  for( int i = 0; i < b->num_ropes; i++){

    bals.insert(b->ropes[i]);
    deleteAll_helper(b->ropes[i], bals);
  }
  std::set<Balloon*>::iterator itr = bals.begin();
  for ( ; itr != bals.end(); itr++){
    delete *itr;
  }

}


//*/

class Smart_Balloon {
public:
  // CONSTRUCTOR & DESTRUCTOR
  Smart_Balloon(const std::string& name_) : name(name_) {
    std::cout << "Balloon constructor " << name << std::endl;
    num_ropes = 0;
    ropes = new dsSharedPtr<Smart_Balloon>[MAX_NUM_ROPES];
  }
  ~Smart_Balloon() {
    std::cout << "Balloon destructor " << name << std::endl;
    // don't try to destroy attached balloons, just delete array
    delete [] ropes;
  }

  // ACCESSORS
  const std::string& getName() const { return name; }
  int numRopes() const { return num_ropes; }
  const dsSharedPtr<Smart_Balloon> getRope(int i) const { return ropes[i]; }

  // print the balloons we are attached to
  void print() { 
    std::cout << "Balloon " << name << " is connected to: ";
    for (int i = 0; i < num_ropes; i++) {
      std::cout << ropes[i]->getName() << " ";
    }
    if (num_ropes == 0) std::cout << "nothing";
    std::cout << std::endl;
  }
  // add a rope connecting this balloon to another
  void addRope(dsSharedPtr<Smart_Balloon> b) { 
    assert (num_ropes < MAX_NUM_ROPES);
    ropes[num_ropes] = b;
    num_ropes++;
  }
  // detach a rope connecting this balloon to another
  void removeRope(dsSharedPtr<Smart_Balloon> b) { 
    for (int i = 0; i < MAX_NUM_ROPES; i++) {
      if (ropes[i] == b) { ropes[i] = ropes[num_ropes-1]; num_ropes--; break; }
    }
  }

private:
  std::string name;
  int num_ropes;
  // a dynamically allocated C-style array of ropes connecting to other Balloons
  dsSharedPtr<Smart_Balloon>* ropes; 
};


// ====================================================
// ====================================================

int main() {

  std::cout << "start of main" << std::endl;
  
  // ====================================================
  // SINGLE OWNER SMART POINTERS
  // ====================================================

  // first, without smart pointers!
  Balloon* alice(new Balloon("Hello Kitty"));
  
  // now, with our homemade single owner smart pointer
  dsAutoPtr<Balloon> bob(new Balloon("Spiderman"));

  // both alice & bob work like regular pointers...
  alice->print();
  bob->print();

  delete alice;



  //
  // CHECKPOINT 2A: INSERT NECESSARY EXPLICIT DEALLOCATION
  //


  
  // ====================================================
  // SIMPLE SHARED POINTERS
  // ====================================================

  // first, without smart pointers
  Balloon* cathy(new Balloon("Buzz Lightyear"));  
  Balloon* daniel(cathy);
  Balloon* elaine(new Balloon("Pokemon"));
  Balloon* fred(elaine);
  daniel = fred;
  fred = NULL;
  elaine = cathy;
  cathy = NULL;

  delete elaine;
  delete daniel;
  


  //
  // CHECKPOINT 2B: INSERT NECESSARY EXPLICIT DEALLOCATION
  //



  daniel = NULL;
  elaine = NULL;
  

  // now, with our homemade shared pointer
  dsSharedPtr<Balloon> cathy2(new Balloon("Buzz Lightyear2"));
  dsSharedPtr<Balloon> daniel2(cathy2);
  dsSharedPtr<Balloon> elaine2(new Balloon("Pokemon2"));
  dsSharedPtr<Balloon> fred2(elaine2);
  daniel2 = fred2;
  fred2 = NULL;
  elaine2 = cathy2;
  cathy2 = NULL;
   // NOTE:  no explicit destruction required!
  daniel2 = NULL;
  elaine2 = NULL;

  //delete cathy2;
  //delete elaine;


  // ====================================================
  // SHARED POINTERS WITH INTERCONNECTED STRUCTURES
  // ====================================================

/*
  Balloon* georgette(new Balloon("Mr Potato Head"));
  Balloon* henry(new Balloon("Snoopy"));

  georgette->addRope(henry);
  henry = new Balloon("Tigger");
  georgette->addRope(henry);
  georgette->print();
  henry->print();
  
  Balloon* isabelle(new Balloon("Shrek"));
  henry->addRope(isabelle);
  isabelle = new Balloon("Barney the Purple Dinosaur");
  georgette->addRope(isabelle);

  henry->print();
  georgette->print();
  isabelle->print();
*/




  //
  // CHECKPOINT 2C: REWRITE THE ABOVE EXAMPLE TO USE SHARED POINTERS
  //


  dsSharedPtr<Smart_Balloon> georgette2(new Smart_Balloon("Mr Potato Head"));
  dsSharedPtr<Smart_Balloon> henry2(new Smart_Balloon("Snoopy"));

  georgette2->addRope(henry2);
  henry2 = new Smart_Balloon("Tigger");
  georgette2->addRope(henry2);
  georgette2->print();
  henry2->print();
  
  dsSharedPtr<Smart_Balloon> isabelle2(new Smart_Balloon("Shrek"));
  henry2->addRope(isabelle2);
  isabelle2 = new Smart_Balloon("Barney the Purple Dinosaur");
  georgette2->addRope(isabelle2);

  henry2->print();
  georgette2->print();
  isabelle2->print();






  // ====================================================
  // CYCLIC STRUCTURES
  // ====================================================


  // FOR CHECKPOINT 3


  ///*
  Balloon* jacob(new Balloon("Dora the Explorer"));
  Balloon* katherine(new Balloon("Kung Fu Panda"));
  Balloon* larry(new Balloon("Scooby Doo"));
  Balloon* miranda(new Balloon("SpongeBob SquarePants"));
  Balloon* nicole(new Balloon("Papa Smurf"));

  jacob->addRope(katherine);
  katherine->addRope(larry);
  larry->addRope(jacob);
  miranda->addRope(jacob);
  nicole->addRope(miranda);
  larry->addRope(nicole);

  katherine = NULL;
  larry = NULL;
  miranda = NULL;
  nicole = NULL;

  // jacob points to a cyclic structure!

  // to cleanup this structure:
  deleteAll(jacob);
  
  jacob = NULL;
  //*/



  std::cout << "end of main" << std::endl;
  return 0;

  //
  // NOTE: when smart pointers go out of scope, the destructors for
  //       those objects will be called automatically
  //
}

// ====================================================