#ifndef REAL_MAX_TESTER_H
#define REAL_MAX_TESTER_H

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

#include <iomanip>
#include <iostream>
#include <string>

void basicFileTest();
void assemblerFirstPassTest();

void displayIntro();
void displayPass();
void displayFail();
void failIndividual();
void displayTest(std::string str);

#endif