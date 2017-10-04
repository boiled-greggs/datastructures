#include <iostream>
#include <cmath>
using namespace std;

#include "vec.h"

int main() {

  // ---------------------------------------------------
  // initialize v1 with 10 values...  the multiples of 5
  Vec<int> v1( 10, 0 );
  Vec<int>::size_type i;
  for ( i = 0; i < v1.size(); i++) {
    v1[i] = 5 * i;
  }
  cout << "v1.size() = " << v1.size() << ".  Should be 10.\n";
  cout << "Contents of v1 (multiples of 5):";
  for ( i = 0; i<v1.size(); ++i ) {
    cout << " " << v1[i];
  }
  cout << endl;

  // --------------------------------------------------------------------------
  // make v2 be a copy of v1, but then overwrite the 2nd half with the 1st half
  Vec<int> v2( v1 );
  v2[ 9 ] = v2[ 0 ];
  v2[ 8 ] = v2[ 1 ];
  v2[ 7 ] = v2[ 2 ];
  v2[ 6 ] = v2[ 3 ];
  v2[ 5 ] = v2[ 4 ];
  cout << "Contents of v1 (still multiples of 5):";
  for ( i = 0; i<v1.size(); ++i )
    cout << " " << v1[i];
  cout << endl;
  cout << "Contents of v2 (now palindrome):";
  for ( i = 0; i<v2.size(); ++i )
    cout << " " << v2[i];
  cout << endl;

  // ------------------------------------------
  // make v3 be a copy of v2, but then clear it
  Vec<int> v3;
  v3 = v2;
  v3.clear();
  cout << "\nAfter copying v2 to v3 and clearing v3,  v2.size() = "
       << v2.size() << " and v3.size() = " << v3.size() << endl;
  cout << "Contents of v2 (should be unchanged):";
  for ( i = 0; i<v2.size(); ++i ) {
    cout << " " << v2[i];
  }
  cout << endl;

  // --------------
  // test push back
  cout << "\nNow testing push_back.  Adding 3, 6, 9 to v2:\n";
  v2.push_back( 3 );
  v2.push_back( 6 );
  v2.push_back( 9 );
  cout << "v2 is now: \n";
  for ( i = 0; i<v2.size(); ++i ) {
    cout << " " << v2[i];
  }
  cout << endl;

  // -----------
  // test resize
  v1.resize(20,100);
  cout << "\nNow testing resize.  Resizing v1 to have 20 elements and v2 to have 2 elements\n";
  cout << "v1 is now (should have 100s at the end): \n";
  for ( i = 0; i<v1.size(); ++i )
    cout << " " << v1[i];
  cout << endl;
  v2.resize(2,100);
  cout << "v2 is now: \n";
  for ( i = 0; i<v2.size(); ++i )
    cout << " " << v2[i];
  cout << endl;

  // ------------------------
  // test of a vec of doubles
  cout << "\nStarting from an empty vector, z,  of doubles and doing\n"
       << "5 push_backs\n";
  Vec<double> z;
  for ( i = 0; i<5; ++i )
    z.push_back( sqrt( double(10*(i+1)) ));
  cout << "Contents of vector z: ";
  for ( Vec<double>::size_type j = 0; j < z.size(); j++ )
    cout << " " << z[j];
  cout << endl;



  // ADD MORE TEST CASES HERE
  
  cout << "\nMake new test vector for removing matching elements\n";
  cout << "Vector contents:\n  ";
  Vec<int> rem;
  rem.push_back(11); rem.push_back(22); rem.push_back(33);
  rem.push_back(11); rem.push_back(55); rem.push_back(22);
  for (unsigned int i = 0; i < rem.size(); i++) {
    cout << rem[i] << " ";
  }
  int removed = remove_matching_elements(rem, 11);
  cout << "\nRemoved element 11; new size = " << rem.size() << endl;
  cout << removed << " elements removed\n";
  cout << "Vector contents:\n  ";
  for (unsigned int i = 0; i < rem.size(); i++) {
    cout << rem[i] << " ";
  }
  cout << endl << endl;

  Vec<string> rem2;
  string s1 = "hi"; string s2 = "hello"; string s3 = "hey";
  rem2.push_back(s1); rem2.push_back(s2); rem2.push_back(s3);
  rem2.push_back(s1); rem2.push_back(s2); rem2.push_back(s3);
  rem2.push_back(s1); rem2.push_back(s2); rem2.push_back(s3);
  rem2.push_back(s1); rem2.push_back(s2); rem2.push_back(s3);
  for (unsigned int i = 0; i < rem2.size(); i++) {
    cout << rem2[i] << " ";
  }
  int removed2 = remove_matching_elements(rem2, s2);
  cout << "\nRemoved element \"hello\"; new size = " << rem2.size() << endl;
  cout << removed2 << " elements removed\n";
  cout << "Vector contents:\n  ";
  for (unsigned int i = 0; i < rem2.size(); i++) {
    cout << rem2[i] << " ";
  }
  cout << endl << endl;
  Vec<float> rem3;
  float f1 = 3.141; float f2 = 1.1239; float f3 = 5.678;
  rem3.push_back(f1); rem3.push_back(f2); rem3.push_back(f3);
  rem3.push_back(f1); rem3.push_back(f2); rem3.push_back(f3);
  rem3.push_back(f1); rem3.push_back(f2); rem3.push_back(f3);
  rem3.push_back(f1); rem3.push_back(f2); rem3.push_back(f3);
  rem3.push_back(f1); rem3.push_back(f2); rem3.push_back(f3);
  rem3.push_back(f1); rem3.push_back(f2); rem3.push_back(f3);
  rem3.push_back(f1); rem3.push_back(f2); rem3.push_back(f3);
  rem3.push_back(f1); rem3.push_back(f2); rem3.push_back(f3);
  rem3.push_back(f1); rem3.push_back(f2); rem3.push_back(f3);
  rem3.push_back(f1); rem3.push_back(f2); rem3.push_back(f3);
  for (unsigned int i = 0; i < rem3.size(); i++) {
    cout << rem3[i] << " ";
  }
  int removed3 = remove_matching_elements(rem3, f2);
  cout << "\nRemoved element 1.1239; new size = " << rem3.size() << endl;
  cout << removed3 << " elements removed\n";
  cout << "Vector contents:\n  ";
  for (unsigned int i = 0; i < rem3.size(); i++) {
    cout << rem3[i] << " ";
  }
  cout << endl << endl;
  Vec<string> rem4;
  string s4 = "wow"; string s5 = "wo"; string s6 = "w";
  rem4.push_back(s4); rem4.push_back(s5); rem4.push_back(s6);
  rem4.push_back(s4); rem4.push_back(s5); rem4.push_back(s6);
  rem4.push_back(s4); rem4.push_back(s5); rem4.push_back(s6);
  rem4.push_back(s4); rem4.push_back(s5); rem4.push_back(s6);
  rem4.push_back(s4); rem4.push_back(s5); rem4.push_back(s6);
  rem4.push_back(s4); rem4.push_back(s5); rem4.push_back(s6);
  rem4.push_back(s4); rem4.push_back(s5); rem4.push_back(s6);
  rem4.push_back(s4); rem4.push_back(s5); rem4.push_back(s6);
  rem4.push_back(s5); rem4.push_back(s5); rem4.push_back(s6);
  rem4.push_back(s4); rem4.push_back(s5); rem4.push_back(s6);
  rem4.print();
  int removed4 = remove_matching_elements(rem4, s5);
  removed4 += remove_matching_elements(rem4, s4);
 // removed4 += remove_matching_elements(rem4, s6);
  cout << "\nRemoved element \"wo\"; new size = " << rem4.size() << endl;
  cout << removed4 << " elements removed\n";
  rem4.print();
  cout << endl << endl;
  
  cout << "test print()\n";
  rem.print();
  
  Vec<int> manypush;
  manypush.print();
  int k = 1;
  for (int i = 0; i < 100; i++) {
    manypush.push_back(i);
  }
  manypush.print();

  for (int i = 0; i < 100; i++) {
    if (manypush[i]%2 == 0 ) { // || manypush[i]%3 == 0) {
      remove_matching_elements(manypush, i);
    }
    if ((i+1)%50 == 0) 
      manypush.print();
  }

  Vec<string> rem5;
  string ff = "ooph"; string fn = "nope";
  rem5.push_back(ff);
  rem5.print();
  remove_matching_elements(rem5, fn);
  rem5.print();
  remove_matching_elements(rem5, ff);
  rem5.print();
  
  Vec<int> intvec(10,10);
  intvec.print();
  return 0; 
}
