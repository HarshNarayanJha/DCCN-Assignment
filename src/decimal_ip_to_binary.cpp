// 2. Translate dotted decimal IP address into 32 bit address.

#include <bitset>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string ip;

  cout << "Enter an IP address: ";
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

  int ipInt = 0;

  for (size_t i = 0; i < ipVec.size(); i++) {
    ipInt = (ipInt << 8) | ipVec.at(i);
    bitset<8> ipBit(ipVec.at(i));
    cout << ipBit;

    if (i != ipVec.size() - 1) {
      printf(".");
    }
  }

  printf("\n%032b\n", ipInt);
}
