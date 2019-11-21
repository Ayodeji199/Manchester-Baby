#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include <iomanip>
#include <iostream>
#include <string>

void basicFileTest();

void displayIntro();
void displayPass();
void displayFail();
void failIndividual();
void displayTest(std::string str);