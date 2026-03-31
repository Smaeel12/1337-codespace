#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>

class AForm;

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

  const std::string getName() const throw();
  int getGrade() const throw();

  int incrementGrade();
  int decrementGrade();

  int signForm(AForm& form) const;
  int executeForm(AForm const& form) const;

  Bureaucrat(std::string name, int grade);
  Bureaucrat(const Bureaucrat& other);
  Bureaucrat& operator=(const Bureaucrat& other);
  ~Bureaucrat() throw();
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat& obj);

#endif
