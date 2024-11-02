#include "class.h"

Student::Student() {
  this->name = "null";
  this->stuID = "null";
  this->height = 0;
  this->weight = 0;
}

Student::Student(std::string name, std::string stuID, double h, double w)
    : name(name), stuID(stuID), height(h), weight(w) {}

double Student::get_height() const {
    return this->height;
}

void Student::set_height(double h) {
    this->height = h;
}

double Student::calbmi() {
    return this->weight / this->height / this->height;
}