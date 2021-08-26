//
// Created by john_ on 2021-07-30.
//
#include <iostream>
using namespace std;
#include "course.h"




Course::Course(string new_course_number, string new_subject, string new_title, string new_description, int new_units, string new_temp)
{
    course_number = new_course_number;
    subject = new_subject;
    title = new_title;
    description = new_description;
    units = new_units;
    temp = new_temp;
    if(!unit_greater(units)) cmpt::error("units is less than 0");
}


void Course::output(ostream& outs) const 
{
    outs << subject << "," << course_number << ",";
    outs << units << "," << title << "," << description << "\n";
}


void Course::input(istream& ins)
{
    getline(ins, subject, ',');
    //cout << subject << endl;
    getline(ins, course_number, ',');
    //cout << course_number << endl;
    ins >> units;
    getline(ins, title, ',');
    getline(ins, title, ',');
    getline(ins, description, '\n');
}





ostream& operator <<(ostream& outs, const Course& tmp)
{
    tmp.output(outs);
    return outs;
}
istream& operator >> (istream& ins, Course& tmp)
{
    //cout << "whatup\n";
    tmp.input(ins);
    return ins;
}







