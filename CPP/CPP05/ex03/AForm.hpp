#ifndef AFORM_HPP
#define AFORM_HPP

#include <iostream>
#include <string>

#include "Bureaucrat.hpp"

class AForm {
 private:
  const std::string name_;
  const int executionGrade_;
  const int signGrade_;
  bool isSigned_;

 public:
  struct NotSignedException : public std::exception {
    const char* what() const throw();
  };
  struct GradeTooHighException : public std::exception {
    const char* what() const throw();
  };
  struct GradeTooLowException : public std::exception {
    const char* what() const throw();
  };

  const std::string getName() const throw();
  int getExecutionGrade() const throw();
  int getSignGrade() const throw();
  bool getIsSigned() const throw();

  int beSigned(const Bureaucrat& signer);
  virtual int beExecuted() const = 0;

  int execute(const Bureaucrat& executor) const;

  AForm(std::string name, int signGrade, int executionGrade);
  AForm(const AForm& other);
  AForm& operator=(const AForm& other);
  virtual ~AForm() throw();
};

std::ostream& operator<<(std::ostream& os, const AForm& form);

#endif
