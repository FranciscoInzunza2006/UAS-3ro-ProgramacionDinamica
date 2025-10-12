
#pragma once

#include <ctime>
#include <string>

class Appointment {
   private:
    std::time_t date;
    std::string reason;
    std::string result;

   public:
    Appointment();
    ~Appointment();
};
