#include "RobotomyRequestForm.hpp"

#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm(std::string target)
    : target_(target), AForm("RobotomyRequestForm", 72, 45) {}

int RobotomyRequestForm::beExecuted() const {
  if (std::rand() % 2)
    std::cerr << "robotomy failed\n";
  else
    std::cout << "Rat-tat-tat, " << this->target_
              << " has been robotomized successfully\n";
  return 0;
}

RobotomyRequestForm::~RobotomyRequestForm() {}
