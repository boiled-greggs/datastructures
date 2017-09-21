#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <algorithm>

// ======================================================================================

// Helper function to read the provided font from a file.  The format
// of the font file is described in comments below.  The width,
// height, and bitmap_letters variables are set by this function.
void ReadFont(const std::string &font_file, 
	      int &width,
	      int &height,
	      std::vector<std::vector<std::string> > &bitmap_letters) {

  // open the font file for reading
  std::ifstream istr(font_file.c_str());
  if (!istr) { 
    std::cerr << "ERROR: cannot open font file " << font_file << std::endl; 
    exit(0);
  }

  // read in the width & height for every character in the file
  istr >> width >> height;
  assert (width >= 1);
  assert (height >= 1);

  // Create a vector to store all 256 ASCII characters of the
  // characters.  Each character is represented as a vector of
  // <height> strings that are each <width> wide.  Initially the
  // characters are unknown (represented with the '?' character).
  bitmap_letters = std::vector<std::vector<std::string> > 
    ( 256, std::vector<std::string> ( height, std::string(width, '?')));

  // read in all the characters
  // first is the ascii integer representation of the character
  int ascii;
  while (istr >> ascii) {
    assert (ascii >= 0 && ascii < 256);
    // next the character is printed in single quotes
    char c;
    istr >> c;
    assert (c == '\'');
    // use std::noskipws to make sure we can read the space character correctly
    istr >> std::noskipws >> c;
    // verify that the ascii code matches the character
    assert (c == (char)ascii);
    // switch back to std::skipws mode
    istr >> std::skipws >> c;
    assert (c == '\'');
    // read in the letter
    std::vector<std::string> bitmap;
    std::string tmp;
    for (int i = 0; i < height; i++) {
      istr >> tmp;
      assert ((int)tmp.size() == width);
      // make sure the letter uses only '#' and '.' characters
      for (unsigned int j = 0; j < tmp.size(); j++) { 
        assert (tmp[j] == '.' || tmp[j] == '#'); 
      }
      bitmap.push_back(tmp);
    }
    // overwrite the initially unknown letter in the vector
    bitmap_letters[ascii] = bitmap;
  }
}

// ======================================================================================

void WriteMessage(std::string &text,
    std::vector<std::vector<std::string> > &bitmap_letters,
    std::string fg_char, std::string bg_char,
    std::vector<std::string> &message) {
  for(unsigned int i = 0; i < text.size(); i++) {
    char c = text[i];
    int ascii_val = int(c);
    
    //add bitmap letter at index of ascii_val to message, replacing characters
    bool letter_added = false;
    int line_no = 0;
    while(!letter_added) {
      std::string line;
      for(unsigned int j = 0; j < bitmap_letters[ascii_val][line_no].size(); j++) {
        if(bitmap_letters[ascii_val][line_no][j] == '#') {
          line += fg_char;
        } else if (bitmap_letters[ascii_val][line_no][j] == '.') {
          line += bg_char;
        }
      }
      line += bg_char;
      message[line_no] += line;
      line_no++;
      if (line_no == message.size()) { letter_added = true; }
    }
  }
}

void ReadOutput(std::string &output_textfile,
    std::vector<std::vector<std::string> > &bitmap_letters,
    int width, int height,
    std::vector<std::vector<std::string> > &output_letters,
    std::string &text) {
  std::ifstream istr(output_textfile.c_str());
  if(!istr) {
    std::cerr << "ERROR: cannot open output file " << output_textfile << " to read" << std::endl;
    exit(0);
  }
  std::string line; bool sized = false;
  int line_number = 0; 
  std::string piece;
  std::vector<std::string> lines;
  while (!istr.eof()) {
    std::getline(istr, line);
    if(!sized) {
      output_letters = std::vector<std::vector<std::string> > (line.size()/7, std::vector<std::string> (7));
      sized = true;
    }
    for (unsigned int i = 0; i < line.size()/7; i++) {
      std::string letterline = "";
      for (unsigned int j = 0; j < 7; j++) {
        letterline += line[j + i*7];
      }
      output_letters[i][line_number] = letterline;
    }
    line = "";
    line_number++;
  }
  
  char char1, char2; //characters that make up ascii message
  int k = 0; int letter_index = 0;
  char1 = output_letters[letter_index][2][k];
  while(true) {
    if (output_letters[letter_index][2][k] != char1) {
      char2 = output_letters[0][2][k];
      break;
    } else if (k < 6) {
      k++;
    } else {
      letter_index++;
      k = 0;
    }
  }
  std::string message(output_letters.size(), '?'); //create string for final message (i.e. input)
  for (unsigned int i = 0; i < bitmap_letters.size(); i++) {
    if (bitmap_letters[i][0][0] != '?') {
      std::vector<std::string> copy1 = bitmap_letters[i];
      std::vector<std::string> copy2 = bitmap_letters[i];
      for (unsigned int j = 0; j < bitmap_letters[i].size(); j++) {
        copy1[j] += '.'; copy2[j] += '.';
        std::replace(copy1[j].begin(), copy1[j].end(), '#', '>');
        std::replace(copy1[j].begin(), copy1[j].end(), '.', char2);
        std::replace(copy1[j].begin(), copy1[j].end(), '>', char1);
        std::replace(copy2[j].begin(), copy2[j].end(), '#', '>');
        std::replace(copy2[j].begin(), copy2[j].end(), '.', char1);
        std::replace(copy2[j].begin(), copy2[j].end(), '>', char2);
      }
      //go through each letter in output letters
      for (unsigned int out_let = 0; out_let < output_letters.size(); out_let++) {
        //go through each line and compare to current known letters in copy1 and copy2
        int correct1 = 0; int correct2 = 0;
        for (unsigned int lin = 0; lin < output_letters[out_let].size(); lin++) {
          if (copy1[lin] == output_letters[out_let][lin]) {
            //document the match
            correct1++; 
          } else if (copy2[lin] == output_letters[out_let][lin]) {
            //document the match
            correct2++;
          }
        }
        if (correct1 == output_letters[out_let].size() || correct2 == output_letters[out_let].size()) {
          message[out_let] = (char)i;
        }
      }
    }
  }

  std::cout << message << std::endl;
}


int main(int argc, char* argv[]) {
  std::string mode(argv[1]);
  if (mode == "display" && argc != 6) {
    std::cerr << "ERROR: incorrect number of arguments; see instructions for details." << std::endl;
    exit(1);
  } else if (mode == "read" && argc != 4) {
    std::cerr << "ERROR: incorrect number of arguments; see instructions for details." << std::endl;
    exit(1);
  }
  
  int width, height;
  std::vector<std::vector<std::string> > bitmap_letters;
  ReadFont(argv[2], width, height, bitmap_letters);
  
  if (mode == "display") {
    std::string text(argv[3]);
    std::string fg_char(argv[4]);
    std::string bg_char(argv[5]);
     
    std::vector<std::string> message(height);
     
    WriteMessage(text, bitmap_letters, fg_char, bg_char, message);
    for (unsigned int i = 0; i < message.size(); i++) {
      std::cout << message[i] << std::endl;
    }
  } else if (mode == "read") {
    std::string output_textfile(argv[3]);
    std::vector<std::vector<std::string> > output_letters;
    std::string text;

    ReadOutput(output_textfile, bitmap_letters, width, height, output_letters, text);
    
    std::cout << text << std::endl;
  }
  return 0;
}

