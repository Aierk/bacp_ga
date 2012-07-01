#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <cstring>

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " ";

int main( int argc, const char* argv[])
{
  // create a file-reading object
  ifstream fin;
  fin.open(argv[1]); // open a file
  if (!fin.good()) 
    return 1; // exit if file not found
  

  
    // read each line of the file
  while (!fin.eof())
  {
    // read an entire line into memory
    char buf[MAX_CHARS_PER_LINE];
    fin.getline(buf, MAX_CHARS_PER_LINE);
    if ( buf[0] == '/' || buf[0] == '#' ) continue;
    
    // parse the line into blank-delimited tokens
    int n = 0; // a for-loop index
    
    // array to store memory addresses of the tokens in buf
    const char* token[MAX_TOKENS_PER_LINE] = {0}; // initialize to 0
    
    // parse the line
    token[0] = strtok(buf, DELIMITER); // first token

    if (token[0]) // zero if line is blank
    {
      for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
      {
        token[n] = strtok(0, DELIMITER); // subsequent tokens
        if (!token[n]) break; // no more tokens
      }
    }

    // process (print) the tokens
    for (int i = 0; i < n; i++)
    {
      cout << "Token[" << i << "] = " << token[i] << endl;
      if (!strcmp(token[i], "courses")) break;
    }
    cout << endl;
  }
  return 0;
}