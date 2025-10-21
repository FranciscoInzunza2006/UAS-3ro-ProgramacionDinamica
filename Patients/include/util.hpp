
#pragma once

#include <string>

int getInt(const std::string& message = "");
int getIntRange(const int min, const int max, const std::string& message = "");

bool getBool(const std::string& message = "");

std::string getStringOrNothing(const std::string& message = "");

void waitForInput();