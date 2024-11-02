#ifndef CLASS_H
#define CLASS_H

#include <string>

class Student {
public:
    Student(std::string name, std::string stuID, double h, double w);
    Student();
    double get_height() const;
    void set_height(double h);

    std::string name;
    std::string stuID;
private:
    double calbmi();
    double height;
    double weight;
};

#endif