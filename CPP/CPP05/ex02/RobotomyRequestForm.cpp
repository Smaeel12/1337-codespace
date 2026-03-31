#include "RobotomyRequestForm.hpp"

#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm(std::string target)
    : AForm(target, 72, 45) {}

int RobotomyRequestForm::beExecuted() const {
  if (std::rand() % 2)
    std::cerr << "robotomy failed\n";
  else
    std::cout << "Rat-tat-tat, " << this->getName()
              << " has been robotomized successfully\n";
  return 0;
}

RobotomyRequestForm::~RobotomyRequestForm() {}
