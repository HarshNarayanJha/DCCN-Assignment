#include <iostream>
#include <string>
using namespace std;

string stuff(string input, int triggerOneCount = 5) {
  string outputBits;

  int oneCount = 0;

  for (size_t i = 0; i < input.size(); i++) {
    if (input[i] == '1') {
      oneCount++;
    } else {
      oneCount = 0;
    }

    outputBits.push_back(input[i]);
    if (oneCount == triggerOneCount) {
      outputBits.push_back('0');
      oneCount = 0;
    }
  }

  return outputBits;
}

string destuff(string input, int triggerOneCount = 5) {
  string outputBits;

  int oneCount = 0;

  for (size_t i = 0; i < input.size(); i++) {
    if (input[i] == '1') {
      oneCount++;
    } else {
      oneCount = 0;
    }

    outputBits.push_back(input[i]);
    if (oneCount == triggerOneCount) {
      i++;
      oneCount = 0;
    }
  }

  return outputBits;
}

int main() {
  string inputBits;

  cout << "Enter input bits: ";
  cin >> inputBits;

  string stuffed = stuff(inputBits);
  cout << "Stuffed Bits: " << stuffed << '\n';

  string destuffed = destuff(stuffed);
  cout << "Destuffed Bits: " << destuffed << '\n';

  cout << "Original Bits == Destuffed Bits: " << (inputBits == destuffed ? 'T' : 'F') << '\n';

  return 0;
}
