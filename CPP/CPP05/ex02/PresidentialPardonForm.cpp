#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target)
    : AForm(target, 25, 5) {}

int PresidentialPardonForm::beExecuted() const {
  std::cout << this->getName() << " has pardoned by Zaphod Beeblebrox\n";
  return 0;
}

PresidentialPardonForm::~PresidentialPardonForm() {}
