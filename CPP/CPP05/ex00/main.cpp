#include <iostream>
#include <stdexcept>

#include "Bureaucrat.hpp"

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
    Bureaucrat original("Peter", 42);

    if (original.getName() != "Peter" || original.getGrade() != 42)
      throw std::runtime_error("getter mismatch");

    original.incrementGrade();
    original.incrementGrade();
    original.incrementGrade();
    if (original.getGrade() != 39)
      throw std::runtime_error("increment/decrement logic error");

    Bureaucrat copy(original);
    if (copy.getName() != original.getName() ||
        copy.getGrade() != original.getGrade())
      throw std::runtime_error("copy ctor mismatch");
    std::cout << copy;

    original.decrementGrade();
    original.decrementGrade();
    if (original.getGrade() != 41)
      throw std::runtime_error("increment/decrement logic error");

    copy = original;
    if (copy.getName() != "Peter" || copy.getGrade() != 41)
      throw std::runtime_error("assignment operator mismatch");

    std::cout << original;
  })

  THROW_ASSERT("Construct with grade 0 (too high)", Bureaucrat("Peter", 0),
               Bureaucrat::GradeTooHighException)
  THROW_ASSERT("Construct with grade 151 (too low)", Bureaucrat("Peter", 151),
               Bureaucrat::GradeTooLowException)

  THROW_ASSERT("increment at grade 1 (overflow high)",
               Bureaucrat("Peter", 1).incrementGrade(),
               Bureaucrat::GradeTooHighException)

  THROW_ASSERT("decrement at grade 150 (overflow low)",
               Bureaucrat("Peter", 150).decrementGrade(),
               Bureaucrat::GradeTooLowException)

  THROW_ASSERT(
      "boundary up throw: 2 -> 1 -> 0",
      {
        Bureaucrat b("BoundaryUpThrow", 2);
        b.incrementGrade();
        b.incrementGrade();
      },
      Bureaucrat::GradeTooHighException)

  THROW_ASSERT(
      "boundary down throw: 149 -> 150 -> 151",
      {
        Bureaucrat b("BoundaryDownThrow", 149);
        b.decrementGrade();
        b.decrementGrade();
      },
      Bureaucrat::GradeTooLowException)

  return 0;
}
