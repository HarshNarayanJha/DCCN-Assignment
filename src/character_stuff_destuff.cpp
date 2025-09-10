#include <iostream>
#include <string>
using namespace std;

#define flag 'Q'
#define stf 'X'

string stuff(string input) {
  string outputString;

  outputString.push_back(flag);

  for (size_t i = 0; i < input.size(); i++) {
    if (input[i] == flag || input[i] == stf) {
      outputString.push_back(stf);
    }

    outputString.push_back(input[i]);
  }

  outputString.push_back(flag);

  return outputString;
}

string destuff(string input) {
  string outputString;

  for (size_t i = 0; i < input.size(); i++) {
    if (input[i] == flag || input[i] == stf) {
      i++;
    }

    outputString.push_back(input[i]);
  }

  return outputString;
}

int main() {
  string inputString;

  cout << "Enter input bits: ";
  cin >> inputString;

  string stuffed = stuff(inputString);
  cout << "Stuffed String: " << stuffed << '\n';

  string destuffed = destuff(stuffed);
  cout << "Destuffed String: " << destuffed << '\n';

  return 0;
}
