#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>

class Form;

class Bureaucrat {
 private:
  const std::string name_;
  int grade_;

 public:
  struct GradeTooHighException : public std::exception {
    const char* what() const throw();
  };
  struct GradeTooLowException : public std::exception {
    const char* what() const throw();
  };

  const std::string& getName() const;
  int getGrade() const;

  int incrementGrade();
  int decrementGrade();

  int signForm(Form& form) const;

  Bureaucrat(std::string name, int grade);
  Bureaucrat(const Bureaucrat& other);
  Bureaucrat& operator=(const Bureaucrat& other);
  ~Bureaucrat();
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& obj);

#endif
