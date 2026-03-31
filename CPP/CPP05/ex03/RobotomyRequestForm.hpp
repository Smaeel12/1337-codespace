#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "AForm.hpp"

class RobotomyRequestForm : public AForm {
 private:
  const std::string target_;

 public:
  RobotomyRequestForm(std::string target);
  int beExecuted() const;

  ~RobotomyRequestForm();
};

#endif
