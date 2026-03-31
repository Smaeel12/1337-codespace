#include <iostream>
#include <stdexcept>

#include "Bureaucrat.hpp"
#include "Form.hpp"

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
  NO_THROW_ASSERT("Normal Program execution", {
    Form original("TestForm", 10, 20);

    if (original.getName() != "TestForm" || original.getSignGrade() != 10 ||
        original.getExecutionGrade() != 20 || original.getIsSigned() != false)
      throw std::runtime_error("Form getters mismatch");

    Bureaucrat b("Signer", 5);
    original.beSigned(b);
    if (!original.getIsSigned())
      throw std::runtime_error("Form should be signed after beSigned");

    Form copy(original);
    if (copy.getName() != original.getName() ||
        copy.getSignGrade() != original.getSignGrade() ||
        copy.getExecutionGrade() != original.getExecutionGrade() ||
        copy.getIsSigned() != original.getIsSigned())
      throw std::runtime_error("Form copy constructor mismatch");
    std::cout << copy;

    copy = original;
    if (copy.getName() != original.getName() ||
        copy.getSignGrade() != original.getSignGrade() ||
        copy.getExecutionGrade() != original.getExecutionGrade() ||
        copy.getIsSigned() != original.getIsSigned())
      throw std::runtime_error("Form assignment operator mismatch");

    std::cout << original;
  })

  NO_THROW_ASSERT("Signing a form twice", {
    Form f("Twice", 10, 20);
    Bureaucrat b("Signer", 5);
    f.beSigned(b);
    f.beSigned(b);
    if (!f.getIsSigned())
      throw std::runtime_error("Form not signed after second beSigned");
    std::cout << f;
  })

  NO_THROW_ASSERT("Basic Form insertion operator", {
    Form form("form", 1, 1);
    std::cout << form;
  })

  NO_THROW_ASSERT("Bureaucrat signForm method (Success & Failure cases)", {
    Form formA("formA", 1, 1);
    Form formB("formB", 1, 15);
    Bureaucrat p("Peter", 10);
    p.signForm(formA);
    p.signForm(formB);
  })

  NO_THROW_ASSERT("Form beSigned method basic usage", {
    Form form = Form("form", 1, 1);
    form.beSigned(Bureaucrat("Peter", 1));
    std::cout << form;
  })

  THROW_ASSERT("Constructor: Sign grade too high (0)", Form("form", 0, 1),
               Form::GradeTooHighException)

  THROW_ASSERT("Constructor: Sign grade too low (151)", Form("form", 151, 1),
               Form::GradeTooLowException)

  THROW_ASSERT("Constructor: Exec grade too high (0)", Form("form", 1, 0),
               Form::GradeTooHighException)

  THROW_ASSERT("Constructor: Exec grade too low (151)", Form("form", 1, 151),
               Form::GradeTooLowException)

  THROW_ASSERT(
      "beSigned: Bureaucrat grade too low",
      {
        Form f("form", 1, 1);
        f.beSigned(Bureaucrat("Peter", 2));
      },
      Form::GradeTooLowException)

  return 0;
}