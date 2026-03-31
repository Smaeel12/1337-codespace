#include "Intern.hpp"

Intern::Intern() {}

Intern::Intern(const Intern&) {}

Intern& Intern::operator=(const Intern& other) {
  if (this == &other) return *this;
  return *this;
}

AForm* Intern::makeShrubberyCreationForm(std::string target) const {
  return new ShrubberyCreationForm(target);
}

AForm* Intern::makePresidentialPardonForm(std::string target) const {
  return new PresidentialPardonForm(target);
}

AForm* Intern::makeRobotomyRequestForm(std::string target) const {
  return new RobotomyRequestForm(target);
}

AForm* Intern::makeForm(std::string name, std::string target) {
  AForm* (Intern::* make[])(std::string) const = {
      &Intern::makeShrubberyCreationForm,
      &Intern::makePresidentialPardonForm,
      &Intern::makeRobotomyRequestForm,
  };

  std::string av_names[] = {
      "shrubbery creation",
      "presidential pardon",
      "robotomy request",
  };

  for (size_t i = 0; i < 3; i++)
    if (av_names[i] == name) return (this->*make[i])(target);

  std::cerr << "Cannot create form: unknown form name \"" << name << "\"\n";
  return NULL;
}

Intern::~Intern() {}
