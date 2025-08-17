// 1. Determine if the IP address is in Class A, B, C, D, or E.
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string ip;
  cin >> ip;

  istringstream ss(ip);
  string octec;
  vector<int> ipVec;

  while (getline(ss, octec, '.')) {
    int byte = stoi(octec);
    if (byte < 0 || byte > 255) {
      printf("Invalid IP address format\n");
      return 1;
    }
    ipVec.push_back(byte);
  }

  if (ipVec.size() != 4) {
    printf("Invalid IP address format\n");
    return 1;
  }

  int firstOctec = ipVec.at(0);
  if (firstOctec <= 127) {
    printf("Class A");
  } else if (firstOctec <= 191) {
    printf("Class B");
  } else if (firstOctec <= 223) {
    printf("Class C");
  } else if (firstOctec <= 239) {
    printf("Class D");
  } else {
    printf("Class E");
  }

  printf("\n");
}
