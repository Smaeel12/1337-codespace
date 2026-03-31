#include <iostream>

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#define NO_THROW_ASSERT(TestName, CodeBlock)                             \
  try {                                                                  \
    std::cout << "---- " << TestName << " ----\n";                       \
    CodeBlock;                                                           \
    std::cout << "[:OK:] (Execution successful output above)\n";         \
  } catch (std::exception & e) {                                         \
    std::cerr << "[:FAIL:] " << e.what() << " (Unexpected exception)\n"; \
  }

int main() {
  Bureaucrat agent("Peter", 1);
  Intern graduate;

  NO_THROW_ASSERT("Intern: Create Shrubbery Creation", {
    AForm* form = graduate.makeForm("shrubbery creation", "Home");
    if (form) {
      std::cout << *form;
      agent.signForm(*form);
      agent.executeForm(*form);
      delete form;
    }
  })

  NO_THROW_ASSERT("Intern: Create Presidential Pardon", {
    AForm* form = graduate.makeForm("presidential pardon", "Neil");
    if (form) {
      std::cout << *form;
      agent.signForm(*form);
      agent.executeForm(*form);
      delete form;
    }
  })

  NO_THROW_ASSERT("Intern: Create Robotomy Request", {
    AForm* form = graduate.makeForm("robotomy request", "Bender");
    if (form) {
      std::cout << *form;
      agent.signForm(*form);
      agent.executeForm(*form);
      delete form;
    }
  })

  NO_THROW_ASSERT("Intern: Unknown Form Name (NULL Check)", {
    AForm* form = graduate.makeForm("vacation flavor", "Hawaii");
    if (form == NULL) {
      std::cout << "Intern correctly returned NULL for invalid form name.\n";
    } else {
      std::cerr << "Intern failed: returned an object for unknown name.\n";
      delete form;
    }
  })

  NO_THROW_ASSERT("Intern: Empty Strings", {
    AForm* form = graduate.makeForm("", "");
    if (!form) std::cout << "Intern correctly ignored empty strings.\n";
    delete form;
  })

  NO_THROW_ASSERT("Intern: Case Sensitivity Check", {
    AForm* form = graduate.makeForm("ROBOTOMY REQUEST", "Target");
    if (!form)
      std::cout << "Intern correctly handles strict case requirements.\n";
    delete form;
  })

  NO_THROW_ASSERT("Intern: Multiple Successive Creations", {
    AForm* f1 = graduate.makeForm("shrubbery creation", "A");
    AForm* f2 = graduate.makeForm("shrubbery creation", "B");
    if (f1 && f2) std::cout << "Intern created multiple forms successfully.\n";
    delete f1;
    delete f2;
  })

  return 0;
}