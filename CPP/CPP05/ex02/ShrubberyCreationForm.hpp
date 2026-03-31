#ifndef SHRUBBERY_CREATION_FORM_HPP
#define SHRUBBERY_CREATION_FORM_HPP

#include <fstream>

#include "AForm.hpp"

class ShrubberyCreationForm : public AForm {
 private:
  const std::string target_;

 public:
  ShrubberyCreationForm(std::string target);
  int beExecuted() const;

  ~ShrubberyCreationForm();
};

#endif
