//
// Created by john_ on 2021-07-30.
//
//
#ifndef COURSE_H
#define COURSE_H

#include "cmpt_error.h" // These are the only
#include <iostream>     // files you can #include.
#include <fstream>      // Don't remove or change
#include <string>       // any of them, and don't
#include <algorithm>    // #include any others.
#include <cassert>

using namespace std;



class Course {
private:
    string course_number; //number of the course ex. 130
    string subject; //type of the course ex. CMPT
    string title; //Title of the course ex. "Introduction to Computing science and Programming II"
    string description; // Brief description of the course ex. "A rigorous introduction to computing science and computer programming,suitable for students who already have some background...."
    int units;
    string temp;


public:
    Course()
    : course_number(""), subject(""), title(""), description(""), units(3), temp("\n")
    { }
    // create couple more constructors


    Course(string new_course_number, string new_subject, string new_title, string new_description, int new_units, string new_temp);

    //Implement getters
    string get_course_number(){return course_number;}
    string get_subject() const{ return subject;}
    string get_title() const{return title;}
    string get_description() const{return description;}
    int get_unit() const{return units;}
    void output(ostream& outs) const;
    void input(istream& ins);

    // course id is "subject number"
    // EG. "CMPT 127"

    string get_course_id() const {
        return subject+" "+course_number;
    }

    string to_string() const{
        return subject + " " + course_number + "(" + " " + std::to_string(units) + ")" + "-" + description;}

    friend bool operator==(const Course& a, const Course& b) {
        
        if (a.subject == b.subject && a.course_number == b.course_number){
            return true;
        }
        else{
            return false;
        }
    }



    friend bool operator!=(const Course& a, const Course& b) {
        return !(a == b);
    }


    //implement the fact that units need to have size > 0

    bool unit_greater(int units){
        return units > 0;
    }



    //Implement setters
    void set_course_number(string new_course_number){
        course_number = new_course_number;
    }
    void set_subject(string new_subject){
        subject = new_subject;
    }
    void set_title(string new_title){
        title = new_title;
    }
    void set_description(string new_description){
        description = new_description;
    }

    void set_unit(int new_units){
        units = new_units;
        if(!unit_greater(units)) cmpt::error("units is less than 0");
    }

    // call this instead of '=' if you just to copy the other course's info.
    // Eg. Course c1,c2;
    // the code c1=c2 should be replaced with c1.set_course_info(c2).
    void set_course_info(Course & other) {
        course_number=other.course_number; //number of the course ex. 130
        subject=other.subject; //type of the course ex. CMPT
        title=other.title; //Title of the course ex. "Introduction to Computing science and Programming II"
        description=other.description; // Brief description of the course ex. "A rigorous introduction to computing science and computer programming,suitable for students who already have some background...."
        units=other.units;
    }



    




     friend ostream&operator<<(std::ostream&, const Course&);
     friend istream&operator>>(std::istream&, Course&);


};



#endif




