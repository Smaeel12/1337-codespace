#ifndef FORM_HPP
#define FORM_HPP

#include <iostream>
#include <string>

#include "Bureaucrat.hpp"

class Form {
 private:
  const std::string name_;
  const int executionGrade_;
  const int signGrade_;
  bool isSigned_;

 public:
  struct GradeTooHighException : public std::exception {
    const char* what() const throw();
  };
  struct GradeTooLowException : public std::exception {
    const char* what() const throw();
  };

  const std::string& getName() const;
  int getExecutionGrade() const;
  int getSignGrade() const;
  bool getIsSigned() const;

  int beSigned(const Bureaucrat& signer);

  Form(std::string name, int signGrade, int executionGrade);
  Form(const Form& other);
  Form& operator=(const Form& other);
  ~Form();
};

std::ostream& operator<<(std::ostream& os, const Form& form);

#endif
