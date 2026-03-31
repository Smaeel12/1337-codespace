#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

#define THROW_ASSERT(TestName, CodeBlock, ExpectedXcep) \
  try {                                                 \
    std::cout << "---- " << TestName << " ----\n";      \
    CodeBlock;                                          \
    std::cerr << "[:FAIL:] (No exception thrown)\n";    \
  } catch (const ExpectedXcep& e) {                     \
    std::cout << "[:OK:] " << e.what() << std::endl;    \
  } catch (...) {                                       \
    std::cerr << "[:FAIL:] (Unkown exception)\n";       \
  }

#define NO_THROW_ASSERT(TestName, CodeBlock)                             \
  try {                                                                  \
    std::cout << "---- " << TestName << " ----\n";                       \
    CodeBlock;                                                           \
    std::cout << "[:OK:] (Execution successful output above)\n";         \
  } catch (std::exception & e) {                                         \
    std::cerr << "[:FAIL:] " << e.what() << " (Unexpected exception)\n"; \
  }

int main() {
  std::srand(std::time(NULL));

  NO_THROW_ASSERT("High Level Agent: Full Sign & Execute", {
    Bureaucrat highAgent("high_agent", 1);

    ShrubberyCreationForm formA("Home");
    PresidentialPardonForm formB("Neil");
    RobotomyRequestForm formC("Laundry");

    highAgent.signForm(formA);
    highAgent.signForm(formB);
    highAgent.signForm(formC);

    std::cout << std::endl;

    highAgent.executeForm(formA);
    highAgent.executeForm(formB);
    highAgent.executeForm(formC);
  })
  std::cout << std::endl;

  NO_THROW_ASSERT("Mid Level Agent: Partial Permissions", {
    Bureaucrat midAgent("mid_agent", 70);

    ShrubberyCreationForm formA("Home");
    PresidentialPardonForm formB("Neil");
    RobotomyRequestForm formC("Laundry");

    midAgent.signForm(formA);
    midAgent.signForm(formB);
    midAgent.signForm(formC);

    std::cout << std::endl;

    midAgent.executeForm(formA);
    midAgent.executeForm(formB);
    midAgent.executeForm(formC);
  })
  std::cout << std::endl;

  NO_THROW_ASSERT("Low Level Agent: Total Failure", {
    Bureaucrat lowAgent("low_agent", 150);

    ShrubberyCreationForm formA("Home");
    PresidentialPardonForm formB("Neil");
    RobotomyRequestForm formC("Laundry");

    lowAgent.signForm(formA);
    lowAgent.signForm(formB);
    lowAgent.signForm(formC);

    std::cout << std::endl;

    lowAgent.executeForm(formA);
    lowAgent.executeForm(formB);
    lowAgent.executeForm(formC);
  })
  std::cout << std::endl;

  THROW_ASSERT(
      "Unsigned Shrubbery: Execution Attempt",
      {
        Bureaucrat exec("exec", 1);
        ShrubberyCreationForm form("Garden");
        form.execute(exec);
      },
      AForm::NotSignedException)

  THROW_ASSERT(
      "Unsigned Pardon: Execution Attempt",
      {
        Bureaucrat exec("exec", 1);
        PresidentialPardonForm form("Target");
        form.execute(exec);
      },
      AForm::NotSignedException)

  THROW_ASSERT(
      "Low Grade Execution: Shrubbery",
      {
        Bureaucrat low("low", 150);
        ShrubberyCreationForm form("Home");
        Bureaucrat signer("signer", 1);
        signer.signForm(form);
        form.execute(low);
      },
      AForm::GradeTooLowException)

  THROW_ASSERT(
      "Low Grade Execution: Robotomy",
      {
        Bureaucrat low("low", 150);
        RobotomyRequestForm form("Target");
        Bureaucrat signer("signer", 1);
        signer.signForm(form);
        form.execute(low);
      },
      AForm::GradeTooLowException)

  NO_THROW_ASSERT("Boundary Success: Shrubbery (145/137)", {
    Bureaucrat signer("signer", 145);
    Bureaucrat exec("exec", 137);
    ShrubberyCreationForm form("Border");

    signer.signForm(form);
    exec.executeForm(form);
  })

  NO_THROW_ASSERT("Boundary Success: Pardon (25/5)", {
    Bureaucrat signer("signer", 25);
    Bureaucrat exec("exec", 5);
    PresidentialPardonForm form("Border");

    signer.signForm(form);
    exec.executeForm(form);
  })

  NO_THROW_ASSERT("Boundary Success: Robotomy (72/45)", {
    Bureaucrat signer("signer", 72);
    Bureaucrat exec("exec", 45);
    RobotomyRequestForm form("Border");

    signer.signForm(form);
    exec.executeForm(form);
  })

  return 0;
}