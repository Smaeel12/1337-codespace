#include "AForm.hpp"

const char* AForm::NotSignedException::what() const throw() {
  return "Form execution failed: the form must be signed before it can be "
         "executed.";
}

const char* AForm::GradeTooHighException::what() const throw() {
  return "Grade is too high to perform this operation.";
}

const char* AForm::GradeTooLowException::what() const throw() {
  return "Grade is too low to perform this operation.";
}

AForm::AForm(std::string name, int signGrade, int executionGrade)
    : name_(name),
      executionGrade_(executionGrade),
      signGrade_(signGrade),
      isSigned_(false) {
  if (executionGrade_ < 1 || signGrade_ < 1)
    throw AForm::GradeTooHighException();
  if (executionGrade_ > 150 || signGrade_ > 150)
    throw AForm::GradeTooLowException();
}

AForm::AForm(const AForm& other)
    : name_(other.name_),
      executionGrade_(other.executionGrade_),
      signGrade_(other.signGrade_),
      isSigned_(other.isSigned_) {}

AForm& AForm::operator=(const AForm& other) {
  if (this == &other) return *this;
  this->isSigned_ = other.isSigned_;
  return *this;
}

const std::string AForm::getName() const throw() { return this->name_; }

int AForm::getExecutionGrade() const throw() { return this->executionGrade_; }

int AForm::getSignGrade() const throw() { return this->signGrade_; }

bool AForm::getIsSigned() const throw() { return this->isSigned_; }

int AForm::beSigned(const Bureaucrat& signer) {
  if (this->signGrade_ < signer.getGrade()) throw AForm::GradeTooLowException();
  isSigned_ = true;
  return 0;
}

int AForm::execute(Bureaucrat const& executor) const {
  if (!this->isSigned_) throw AForm::NotSignedException();
  if (this->executionGrade_ < executor.getGrade())
    throw AForm::GradeTooLowException();
  this->beExecuted();
  return 0;
}

AForm::~AForm() throw() {}

std::ostream& operator<<(std::ostream& os, const AForm& form) {
  os << form.getName() << ", ";
  os << (form.getIsSigned() ? "is signed " : "is not signed ");
  os << "require grade " << form.getSignGrade() << " to sign and grade "
     << form.getExecutionGrade() << " to execute.\n";
  return os;
}
