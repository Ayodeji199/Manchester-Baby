#include "realMaxTester.hpp"

// Include the files you are testing here
#include "../file/file.hpp"

using namespace std;

bool fullPass = true;
bool individualPass = true;

// This is where you can edit the tasks that the tester will perform
// Linker errors may occur if you haven't defined certain methods to avoid this,
// you may have to comment out the tests you're not using or create blank
// functions used in the header files (maybe needing to return 0)
void tasks() {
  basicFileTest();
}

void printVector(vector<string>& v) {
  cout << endl;
  cout << "Printing Vector:" << endl;
  for (int i = 0; i < (int) v.size(); i++) {
    cout << v[i] << endl;
  }
  cout << endl;
}

void basicFileTest() {
  cout << endl
       << "Basic file loading test:"
       << endl;
  vector<string> lines;
  loadFile(lines, "assembler/BabyTest1-Assembler.txt");
  printVector(lines);
  displayTest("Loads assembler text file (requires manual checking, will always pass)");
}

void displayIntro() {
  system("clear");
  cout << "Real Max Tester for BabyMaker" << endl;
  cout << "Use wisely" << endl;
}

void displayTest(string str) {
  cout << endl;
  if (individualPass) {
    cout << "\033[32m"
         << "[PASS]";
    cout << "\033[0m"
         << "\t" << str;
  } else {
    cout << "\033[31m"
         << "[FAIL]";
    cout << "\033[39;49m"
         << "\t" << str;
    individualPass = true;
  }
}

void roast() {
  int randVal = rand() % 6;
  switch (randVal) {
    case 0:
      cout << "Your program is !fantastic";
      break;
    case 1:
      cout << "If this program marked you like Mike Crabbs, you'd just fail "
              "the module";
      break;
    case 2:
      cout << "Stackoverflow called, they want your shitty code back";
      break;
    case 3:
      cout << "Check the state of your haircut";
      break;
    case 4:
      cout << "Oh I see, you usually code in Python";
      break;
    case 5:
      cout << "Your code < Windows Vista";
      break;
    default:
      cout << "Whatever you think is causing this, it's not the problem";
  }
  cout << endl;
}

void concern() {
  int randVal = rand() % 6;
  switch (randVal) {
    case 0:
      cout << "Your limitation — it’s only your imagination";
      break;
    case 1:
      cout << "When you have a dream, you've got to grab it and never let go.";
      break;
    case 2:
      cout << "No matter what you're going through, there's a light at the end "
              "of the tunnel.";
      break;
    case 3:
      cout << "Try to be a rainbow in someone else's cloud";
      break;
    case 4:
      cout << "Sometimes you will never know the value of a moment, until it "
              "becomes a memory.";
      break;
    case 5:
      cout << "It is never too late to be what you might have been.";
      break;
    default:
      cout << "Push yourself, because no one else is going to do it for you.";
      break;
  }
  cout << endl;
}

void displayFail() {
  cout << R"(
        ______      _  _ 
        |  ___|    (_)| |
        | |_  __ _  _ | |
        |  _|/ _` || || |
        | | | (_| || || |
        \_|  \__,_||_||_|            
    )";
  cout << endl;
}

void displayPass() {
  cout << R"(
         _____            
        /  ___|                                 
        \ `--.  _   _   ___  ___  ___  ___  ___ 
         `--. \| | | | / __|/ __|/ _ \/ __|/ __|
        /\__/ /| |_| || (__| (__|  __/\__ \\__ \
        \____/  \__,_| \___|\___|\___||___/|___/
    )";
  cout << endl;
}

void failIndividual() {
  fullPass = false;
  individualPass = false;
}

void oops() {
  displayFail();
  int randVal = rand() % 100;

  if (randVal < 25) {
    roast();
  } else if (randVal < 50) {
    concern();
  }
}

void checkSuccess() {
  if (fullPass) {
    displayPass();
  } else {
    oops();
  }
}

int main() {
  try {
    displayIntro();
    tasks();
    checkSuccess();
  } catch (exception& e) {
    failIndividual();
    cout << "Oops there's an exception here: " << e.what() << endl;
    oops();
  }
  return 0;
}