#include <iostream>
#include <map>
#include <fstream>

std::map<int, int> find_mode(const std::map<int, int> &sequence) {
  std::map<int, int> modes;
  int max_occurs = 0;
  std::map<int, int>::const_iterator itr = modes.begin();
  for (itr = sequence.begin(); itr != sequence.end(); itr++) {
    if (itr->second > max_occurs) max_occurs = itr->second;
  }
  for (itr = sequence.begin(); itr != sequence.end(); itr++) {
    if (itr->second == max_occurs) {
      modes.insert(std::make_pair(itr->first, itr->second));
    }
  }
  return modes;
}

void read_input(std::map<int, int> &seq, std::ifstream &istr) {
  int num;
  while (istr >> num) {
    std::map<int, int>::iterator itr;
    itr = seq.find(num);
    if (itr == seq.end())
      seq.insert(std::make_pair(num, 1));
    else
      itr->second++;
  }
}

void print_map(const std::map<int, int> &map) {
  std::map<int, int>::const_iterator itr;
  std::cout << "1st\t2nd\n";
  for (itr = map.begin(); itr != map.end(); ++itr) {
    std::cout << itr->first << "\t" << itr->second << std::endl;
  }
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "incorrect number arguments\n";
    exit(1);
  }
  std::ifstream istr(argv[1]);
  std::map<int, int> sequence;
  read_input(sequence, istr);
  
  std::map<int, int> modes = find_mode(sequence);
  
  print_map(modes);
}
