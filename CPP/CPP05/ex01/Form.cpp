#include "Form.hpp"

const char* Form::GradeTooHighException::what() const throw() {
  return "Grade is too high to perform this operation.";
}

const char* Form::GradeTooLowException::what() const throw() {
  return "Grade is too low to perform this operation.";
}

Form::Form(std::string name, int signGrade, int executionGrade)
    : name_(name),
      executionGrade_(executionGrade),
      signGrade_(signGrade),
      isSigned_(false) {
  if (executionGrade_ < 1 || signGrade_ < 1)
    throw Form::GradeTooHighException();
  if (executionGrade_ > 150 || signGrade_ > 150)
    throw Form::GradeTooLowException();
}

Form::Form(const Form& other)
    : name_(other.name_),
      executionGrade_(other.executionGrade_),
      signGrade_(other.signGrade_),
      isSigned_(other.isSigned_) {}

Form& Form::operator=(const Form& other) {
  if (this == &other) return *this;
  this->isSigned_ = other.isSigned_;
  return *this;
}

const std::string& Form::getName() const { return this->name_; }

int Form::getExecutionGrade() const { return this->executionGrade_; }

int Form::getSignGrade() const { return this->signGrade_; }

bool Form::getIsSigned() const { return this->isSigned_; }

int Form::beSigned(const Bureaucrat& signer) {
  if (this->signGrade_ < signer.getGrade()) throw Form::GradeTooLowException();
  isSigned_ = true;
  return 0;
}

Form::~Form() {}

std::ostream& operator<<(std::ostream& os, const Form& form) {
  os << form.getName() << ", ";
  os << (form.getIsSigned() ? "is signed " : "is not signed ");
  os << "require grade " << form.getSignGrade() << " to sign and grade "
     << form.getExecutionGrade() << " to execute.\n";
  return os;
}
