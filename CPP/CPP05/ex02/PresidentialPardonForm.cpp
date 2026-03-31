#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string target)
    : AForm(target, 25, 5) {}

PresidentialPardonForm::PresidentialPardonForm(
    const PresidentialPardonForm& other)
    : AForm(other) {}

PresidentialPardonForm& PresidentialPardonForm::operator=(
    const PresidentialPardonForm& other) {
  if (this == &other) return *this;
  *this = other;
  return *this;
}

int PresidentialPardonForm::beExecuted() const {
  std::cout << this->getName() << " has pardoned by Zaphod Beeblebrox\n";
  return 0;
}

PresidentialPardonForm::~PresidentialPardonForm() {}
