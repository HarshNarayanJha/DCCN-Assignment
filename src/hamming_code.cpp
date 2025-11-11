#include <iostream>
#include <vector>
using namespace std;

int parity_bit(const vector<int> &data, int pos) {
  int parity = 0;
  int n      = data.size();
  for (int i = pos; i <= n; i += 2 * pos)
    for (int j = i; j < i + pos && j <= n; j++)
      parity ^= data[j - 1];

  return parity;
}

void hamming(vector<int> data) {
  int n         = data.size();
  int error_pos = 0;
  for (int i = 1; i <= n; i <<= 1)
    if (parity_bit(data, i) != 0)
      error_pos += 1;
  if (error_pos != 0) {
    cout << "Error detected at position: " << error_pos << endl;
    data[error_pos - 1] ^= 1;
  } else {
    cout << "No error was detected" << endl;
  }
}

int main() {
  string message;
  cout << "Enter data bits: ";
  cin >> message;

  vector<int> data;

  for (const auto &c : message) {
    if (c != '0' && c != '1') {
      cout << "Invalid binary string" << endl;
      return 1;
    }

    data.push_back(c - '0');
  }

  hamming(data);

  return 0;
}
