#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include "AForm.hpp"

class PresidentialPardonForm : public AForm {
 private:
  const std::string target_;

 public:
  PresidentialPardonForm(std::string target);
  int beExecuted() const;

  ~PresidentialPardonForm();
};

#endif
