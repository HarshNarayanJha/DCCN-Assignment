#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// what parity to use
// 0 -> even
// 1 -> odd
#define PARITY 0

bool is_valid_bin_string(string *message) {
  for (size_t i = 0; i < message->length(); i++) {
    if (message->at(i) != '0' and message->at(i) != '1') {
      cout << "Invalid Input receieved, must contain either 0 or 1 (bits)" << endl;
      return false;
    }
  }

  return true;
}

void introduce_error(string *message) {
  for (size_t i = 0; i < message->length(); i++) {
    if (static_cast<double>(rand()) / RAND_MAX > 0.98) {
      message->at(i) = message->at(i) == '0' ? '1' : '0';
    }
  }
}

void single_parity() {
  // take user input
  string message;
  do {
    cout << "Enter your message: ";
    cin >> message;
  } while (message.length() == 0 || !is_valid_bin_string(&message));

  // check parity
  int parity = count(message.begin(), message.end(), '1') % 2;

  cout << "Parity is " << (parity == 0 ? "Even" : "Odd") << endl;
  cout << "Input string:\t" << message << endl;

  // add parity bit
  if (PARITY == 0) {
    // take even parity
    if (parity == 0) {
      // already even, add 0
      message.push_back('0');
    } else {
      // odd parity, add 1 to make even
      message.push_back('1');
    }
  } else if (PARITY == 1) {
    // take odd parity
    if (parity == 0) {
      // even, add 1 to make odd
      message.push_back('1');
    } else {
      // already odd
      message.push_back('0');
    }
  } else {
    cout << "Invalid PARITY, must be 0 or 1" << endl;
    return;
  }

  cout << "Message:\t" << message << endl;

  // send message
  cout << endl << "Sending message: " << message << " over the noisy channel" << endl;
  // introduce error

  cout << "Trying to introduce some errors" << endl;
  introduce_error(&message);

  // receive message
  cout << endl << "Received message: " << message << endl;

  // check error
  cout << endl << "Checking for error..." << endl;

  int rParity = count(message.begin(), message.end(), '1') % 2;
  if (rParity == PARITY) {
    cout << "No Error Found. Successful transmission" << endl;
  } else {
    cout << "ERROR FOUND! Unsuccessful transmission" << endl;
  }

  cout << endl << endl;
  return;
}

void two_dimensional_parity() {
  // take user input
  int numFrames;
  cout << "Number of frames: ";
  cin >> numFrames;

  if (numFrames <= 0) {
    cout << "Must enter atleast 1 frame" << endl;
    return;
  }

  vector<string> frames;

  for (int i = 0; i < numFrames; i++) {
    string frame;

    do {
      cout << "Enter your message: ";
      cin >> frame;
    } while (frame.length() == 0 || !is_valid_bin_string(&frame));

    frames.push_back(frame);
  }

  // add parity row
  string parityFrame;
  for (size_t i = 0; i < frames.at(0).length(); i++) {
    int p = 0;
    for (int j = 0; j < numFrames; j++) {
      p ^= (frames.at(j).at(i) - '0');
    }

    parityFrame.push_back('0' + p);
  }

  cout << endl << "Redundent row: " << parityFrame << endl;
  cout << "Message Matrix: " << endl;

  for (const auto &row : frames) {
    cout << row << endl;
  }
  cout << "--------" << endl;
  cout << parityFrame << endl;

  // add parityFrame to frames as well
  frames.push_back(parityFrame);
  numFrames++;

  // send message
  cout << endl << "Sending message frames over the noisy channel" << endl;

  // introduce error
  cout << "Trying to introduce some errors" << endl;
  for (size_t i = 0; i < frames.size(); i++) {
    introduce_error(&frames[i]);
  }

  // receive message
  cout << endl << "Received message: " << endl;
  for (const auto &row : frames) {
    cout << row << endl;
  }

  // check error
  cout << endl << "Checking for error..." << endl;

  for (size_t i = 0; i < frames.at(0).length(); i++) {
    int p = 0;
    for (int j = 0; j < numFrames; j++) {
      p ^= (frames.at(j).at(i) - '0');
    }

    if (p != 0) {
      cout << "ERROR FOUND! Unsuccessful transmission" << endl << endl;
      return;
    }
  }

  cout << "No Error Found. Successful transmission" << endl << endl;
  return;
}

string findXor(string a, string b) {
  int n         = b.length();
  string result = "";

  for (int i = 1; i < n; i++) {
    if (a[i] == b[i])
      result += "0";
    else
      result += "1";
  }
  return result;
}

string mod2div(string code, string key) {
  int n      = code.length();
  int pick   = key.length();
  string tmp = code.substr(0, pick);

  while (pick < n) {
    if (tmp[0] == '1')
      tmp = findXor(key, tmp) + code[pick];
    else
      tmp = findXor(string(pick, '0'), tmp) + code[pick];
    pick++;
  }

  if (tmp[0] == '1')
    tmp = findXor(key, tmp);
  else
    tmp = findXor(string(pick, '0'), tmp);

  return tmp;
}

void crc() {
  // take user input
  string message;
  do {
    cout << "Enter your message: ";
    cin >> message;
  } while (message.length() == 0 || !is_valid_bin_string(&message));

  string key;
  do {
    cout << "Enter your key: ";
    cin >> key;
  } while (key.length() == 0 || !is_valid_bin_string(&key));

  int n = key.length();

  string paddedMessage = message + string(n - 1, '0');
  string remainder     = mod2div(paddedMessage, key);

  string code = message + remainder;

  cout << "Message: " << code << endl;

  // send message
  cout << endl << "Sending code: " << code << " over the noisy channel" << endl;

  // introduce error
  cout << "Trying to introduce some errors" << endl;
  introduce_error(&code);

  // receive message
  cout << endl << "Received code: " << code << endl;

  // check error
  cout << endl << "Checking for error..." << endl;

  string rRemainder = mod2div(code, key);
  if (rRemainder.find('1') == string::npos) {
    cout << "No Error Found. Successful transmission" << endl;
  } else {
    cout << "ERROR FOUND! Unsuccessful transmission" << endl;
  }

  cout << endl << endl;
  return;
}

void internet_checksum() {
  cout << "Not Implemented Yet!" << endl;
  return;
}

int main() {
  // srand(static_cast<unsigned int>(Time(0)));

  int choice;
  cout << "== Error detection and correction program ==" << endl;

  int running = true;

  do {
    cout << "1. Single Parity\n2. Two-Dimensional Parity\n3. CRC\n4. Internet Checksum\n5. "
            "Exit\nChoice: ";
    cin >> choice;

    if (!cin.good()) {
      cout << endl << "Please enter a valid choice" << endl;
      return 1;
    }

    switch (choice) {
    case 1:
      single_parity();
      break;
    case 2:
      two_dimensional_parity();
      break;
    case 3:
      crc();
      break;
    case 4:
      internet_checksum();
      break;
    case 5:
      running = false;
      break;
    default:
      cout << "Please enter a valid input" << endl;
      break;
    }
  } while (running);

  return 0;
}
