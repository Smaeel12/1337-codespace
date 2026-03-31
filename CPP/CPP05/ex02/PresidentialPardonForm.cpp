#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target)
    : target_(target), AForm("PresidentialPardonForm", 25, 5) {}

int PresidentialPardonForm::beExecuted() const {
  std::cout << this->target_ << " has pardoned by Zaphod Beeblebrox\n";
  return 0;
}

PresidentialPardonForm::~PresidentialPardonForm() {}
