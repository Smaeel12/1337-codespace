#include "Bureaucrat.hpp"

#include "AForm.hpp"

const char* Bureaucrat::GradeTooHighException::what() const throw() {
  return "Grade is too High: minimum valid grade is 1";
}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
  return "Grade is too Low: maximum valid grade is 150";
}

Bureaucrat::Bureaucrat(std::string name, int grade)
    : name_(name), grade_(grade) {
  if (grade_ < 1) throw Bureaucrat::GradeTooHighException();
  if (grade_ > 150) throw Bureaucrat::GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat& other)
    : name_(other.name_), grade_(other.grade_) {}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
  if (this == &other) return *this;
  this->grade_ = other.grade_;
  return *this;
}

const std::string& Bureaucrat::getName() const { return this->name_; }
int Bureaucrat::getGrade() const { return this->grade_; }

int Bureaucrat::incrementGrade() {
  this->grade_--;
  if (grade_ < 1) throw Bureaucrat::GradeTooHighException();
  return 0;
}

int Bureaucrat::decrementGrade() {
  this->grade_++;
  if (grade_ > 150) throw Bureaucrat::GradeTooLowException();
  return 0;
}

int Bureaucrat::signForm(AForm& form) const {
  try {
    form.beSigned(*this);
    std::cout << name_ << " signed " << form.getName() << std::endl;
  } catch (std::exception& e) {
    std::cerr << name_ << " couldn't sign " << form.getName() << " because "
              << e.what() << std::endl;
  }
  return 0;
}

int Bureaucrat::executeForm(AForm const& form) const {
  try {
    form.execute(*this);
    std::cout << name_ << " executed " << form.getName() << std::endl;
  } catch (std::exception& e) {
    std::cerr << name_ << " couldn't execute " << form.getName() << " because "
              << e.what() << std::endl;
  }
  return 0;
}

Bureaucrat::~Bureaucrat() {}

std::ostream& operator<<(std::ostream& os, const Bureaucrat& obj) {
  os << obj.getName() << ", bureaucrat grade " << obj.getGrade() << ".\n";
  return os;
}
