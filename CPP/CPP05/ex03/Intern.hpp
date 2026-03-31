#ifndef INTERN_HPP
#define INTERN_HPP

#include <string>

#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class Intern {
 private:
  AForm* makeShrubberyCreationForm(std::string target) const;
  AForm* makePresidentialPardonForm(std::string target) const;
  AForm* makeRobotomyRequestForm(std::string target) const;

 public:
  Intern();
  Intern(const Intern& other);
  Intern& operator=(const Intern& other);
  AForm* makeForm(std::string name, std::string target);
  ~Intern();
};

#endif
