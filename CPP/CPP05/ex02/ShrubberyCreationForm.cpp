#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(std::string target)
    : AForm(target, 145, 137) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
    : AForm(other) {}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(
    const ShrubberyCreationForm& other) {
  if (this == &other) return *this;
  *this = other;
  return *this;
}

int ShrubberyCreationForm::beExecuted() const {
  std::ofstream file;
  file.exceptions(std::fstream::failbit | std::fstream::badbit);
  file.open((getName() + "_shrubbery").c_str(),
            std::fstream::out | std::fstream::trunc);
  file << "\
    oxoxoo    ooxoo\n\
  ooxoxo oo  oxoxooo\n\
 oooo xxoxoo ooo ooox\n\
 oxo o oxoxo  xoxxoxo\n\
  oxo xooxoooo o ooo\n\
    ooo\\oo\\  /o/o\n\
        \\  \\/ /\n\
         |   /\n\
         |  |\n\
         | D|\n\
         |  |\n\
         |  |\n\
  ______/____\\____\n";
  return 0;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {}
