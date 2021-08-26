// a3.h

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : <John Park>
// St.# : <301279312>
// Email: <jpa81@sfu.ca>


#ifndef DATABASE_H
#define DATABASE_H


#include "cmpt_error.h" // These are the only
#include <iostream>     // files you can #include.
#include <fstream>      // Don't remove or change
#include <string>       // any of them, and don't
#include <algorithm>    // #include any others.
#include <cassert>
#include "course.h"
#include "matching.h"


using namespace std;


// READ THIS PART
// course id is "subject number"
// EG. "CMPT 127"

enum course_list_order {
    // hopefully self explanatory :)
    ASC_ORDER_BY_UNITS,
    DESC_ORDER_BY_UNITS,
    ALPHA_ORDER_BY_COURSE_ID, //
    //Is alpha_order mean alphabetical order?
    REV_ALPHA_ORDER_BY_COURSE_ID, //
    ALPHA_ORDER_BY_TITLE, //
    REV_ALPHA_ORDER_BY_TITLE, //

    NOT_SELECTED // a dummy option mimicing a null value
};

course_list_order chosen_order = NOT_SELECTED;

// bool course_compare (Course a, Course b) {
//
// }

struct course_compare {

    bool operator () (const Course& a, const Course& b) {
        // what does it mean for a "less than" b?
        // return true if and only if a<b according to chosen_order
        

        switch (chosen_order) {
            case ASC_ORDER_BY_UNITS:
            {
                return a.get_unit()<b.get_unit();
            }
            case DESC_ORDER_BY_UNITS:
            {
                // HL:complete
                return b.get_unit() < a.get_unit();

            }
            case ALPHA_ORDER_BY_COURSE_ID:
            {
                // HL:complete
                // JP: Need to order subjects by alphabetical order

                // HL: shouln't it be get_course_id ?
                return a.get_course_id() < b.get_course_id();
            }
            // HL:complete (put the remining cases here)
            case REV_ALPHA_ORDER_BY_COURSE_ID:
            {
                return b.get_course_id() < a.get_course_id();
            }
            case ALPHA_ORDER_BY_TITLE:
            {
                return a.get_title() < b.get_title();
            }
            case REV_ALPHA_ORDER_BY_TITLE:
            {
                return b.get_title() < a.get_title();
            }


            // ...
            case NOT_SELECTED:
            {
                cmpt::error("Order for listing is not selected.");
                return false;
            }
            default:
                cout << "The unthinkable happened ...\n";
        }

        return false;
    }
};



class Database {

private:
    // ...
    int capacity_;
    Course *arr;
    int size_;

    void resize(int new_cap) {
        //if (new_cap < capacity_) return;
        capacity_ = new_cap;

        Course *new_arr = new Course[capacity_];  // create new, bigger array

        for (int i = 0; i < size_; ++i) {    // copy elements of arr
            new_arr[i].set_course_info(arr[i]);           // into new_arr
        }

        delete[] arr;                     // delete old arr

        arr = new_arr;
    }


public:
    // ...
    //default constructor for int_vec() that creates a new int_vec of size_ 0 and capacity_ 10.
    Database()
            : capacity_(10), arr(new Course[capacity_]), size_(0) {}

    //destructor that deletes all the dynamic memory used by int_vec
    ~Database() {
        //cout << "hey im gone\n";
        if (arr != nullptr) {
            delete[] arr;
            arr = nullptr;
        }
        assert(arr == nullptr);
    }

    Database(int n, Course s)
            : capacity_(n + 15), size_(n) {
        if (size_ < 0) cmpt::error("n is less than zero");
        if (size_ >= 0) capacity_ += size_;
        arr = new Course[capacity_];
        for (int i = 0; i < size_; ++i) {
            arr[i].set_course_info(s);
        }
    }

    Database(const Database &other)
            : capacity_(other.capacity_), arr(new Course[capacity_]), size_(other.size_) {

        for (int i = 0; i < size_; ++i) {
            arr[i].set_course_info(other.arr[i]);
        }
    }

    int size() const { return size_; }

    int capacity() const { return capacity_; }

    double pct_used() const { return ((double) size_ / capacity_); }


    string to_str() const {
        if (size_ == 0) return "[]";


        string result = "[" + arr[0].to_string();
        for (int i = 1; i < size_; i++) {
            result += ", " + arr[i].to_string();
        }
        return result + "]";
    }


    void print() const {
        cout << to_str();
    }

    void println() const {
        print();
        cout << "\n";
    }


    Course get(int i) const {
        if (i < 0 || i > size() - 1) cmpt::error("get: index out of bounds");
        return arr[i];
    }

    void set(int i, Course x) {
        if (i < 0 || i > size_ - 1) cmpt::error("set: index out of bounds");
        arr[i].set_course_info(x);
    }


    void append(Course x) {
        if (size_ >= capacity_) {
            resize(2 * capacity_);   // double the capacity_

        }
        assert(size_ < capacity_);
        arr[size_].set_course_info(x);
        size_++;
    }


    void append(Database other) {

        for (int i = 0; i < other.size(); i++) {
            append(other.get(i));
        }

    }


    void prepend(Course x) {
        if (size_ >= capacity_) {
            resize(2 * capacity_);   // double the capacity_

        }

        assert(size_ < capacity_);
        int i;
        for (i = size_ - 1; i >= 0; i--) {
            arr[i + 1].set_course_info(arr[i]);
        }

        arr[0].set_course_info(x);
        size_++;
    }


    void reverse() {
        int i, j;
        Course temp;
        for (i = 0, j = size_ - 1; i < j; i++, j--) {
            temp.set_course_info(arr[i]);
            arr[i].set_course_info(arr[j]);
            arr[j].set_course_info(temp);
        }
    }


    void clear() {
        size_ = 0;
    }

    void compact() {
        resize(size_);
    }

    friend bool operator==(const Database &a, const Database &b) {
        if (a.size_ != b.size_) {
            return false;
        } else {
            for (int i = 0; i < a.size_; ++i) {
                if (a.get(i) != b.get(i)) {

                    return false;
                }
            }
            return true;
        }
    }

    friend bool operator!=(const Database &a, const Database &b) {
        return !(a == b);
    }

    void remove_all(Course n) {
        int j = 0;
        for (int i = 0; i < size_; i++) {
            if (arr[i] == n) {
                j += 1;
            } else {
                set(i - j, arr[i]); // dont use arr[i-j]=arr[i];
            }
        }
        size_ = size_ - j;
    }

    Database(const string &fname)
            : capacity_(10), arr(new Course[capacity_]), size_(0) {

        ifstream inFile;


        inFile.open(fname);
        if (!inFile.is_open()) {
            cmpt::error("unable to open file");
        }

        string header;
        getline(inFile, header);

        while (true) {
            Course n;
            if (!(inFile >> n)) break;
            //cout << n << endl;
            append(n);
        }


        inFile.close();
    }






    // HL: added methods ...

    void sort(course_list_order order) {
        chosen_order = order;
        std::sort(arr, arr + size_, course_compare());
    }

    void remove_by_index(int i) {
        if (i < 0 || i > size() - 1) cmpt::error("remove: index out of bounds");
        size_--;
        for (; i < size_; i++) {
            set(i, arr[i + 1]);
        }
    }


    int find(Course target) {
        for (int i = 0; i < size_; i++) {
            if (arr[i] == target) {
                return i;
            }
        }
        return -1;
    }

    void display_with_desc() {

        // HL: complete
        // maybe display each course in a separate line?


        for (int i = 0; i < size_; i++) {
            cout << arr[i].get_course_id()<<
            "(" << arr[i].get_unit() << "), " <<  arr[i].get_title() << ", "
            << arr[i].get_description() << endl;
        }
    }


    void display() {

        // HL: complete
        // maybe display each course in a separate line?
        for (int i = 0; i < size_; i++) {
            cout << arr[i].get_course_id()<< ": " <<  arr[i].get_title() << endl;
        }
    }


    void save_to_file(const string &filename) {
        // HL: complete
        // make sure you save(write to) the file
        ofstream file;
        file.open(filename);
        file << "Course name,Course number,Units,Title,description\n";
        for (int i = 0; i < size_; i++) {
//            file << arr[i].to_string() << "\n";
            file << arr[i].get_subject() << "," <<
            arr[i].get_course_number() << "," <<
            arr[i].get_unit() << "," <<
            arr[i].get_title()<< "," <<
            arr[i].get_description() << "\n";
        }
        file.close();
    }

    Database filter_by_unit(int lower, int higher){
        Database ret;
        for(auto i = 0 ; i < this->size_; i++){
            if(this->arr[i].get_unit() >= lower && this->arr[i].get_unit() <= higher){
                ret.append(this->arr[i]);
            }
        }
        return ret;
    }

/*
    * returns a Database of ONLY the courses c, in this DB
    *  such that to_apply.is_match(c) returns true.
    *  - it's a "subset"
    */
    Database filter_by_criteria(Criteria &to_apply) {
        Course _junk;
        to_apply.is_match(_junk);
        Database result;


        auto lower = 0, higher = 0;

        if(to_apply.get_bounded_search() == 1){
            cout << "Please enter the lowest integer value to search by: \n";
            cin >> lower;

            cout << "Please enter higher integer value to search by: \n";
            cin >> higher;
//          result = this->filter_by_unit(lower, higher);

            Database ret;
            for(auto i = 0 ; i < this->size_; i++){
                if(this->arr[i].get_unit() >= lower && this->arr[i].get_unit() <= higher){
                    ret.append(this->arr[i]);
                }
            }
            return ret;
        }

        for (int i = 0; i < size_; i++) {
            if (to_apply.is_match(arr[i])) {
                result.append(arr[i]);
            }
        }


        // HL:complete

        /* 
        for (...) { 
            if(...is_match(<something at index i>)) {
                append the course to result
            }
        }
        */
        return result;
    }

    /*
    *  deletes all the courses, c, from this DB
    *  such that to_apply.is_match(c) returns true.
    *  - it's a "subset" that gets removed.
    */
    void delete_by_criteria(Criteria &to_apply) {
        Course _junk;
        to_apply.is_match(_junk); // delete this after. Keep complier happy for now
        Database result;

        int j = 0;
        for (int i = 0; i < size_; i++) {
            if (to_apply.is_match(arr[i])) {
                j += 1;
            } else {
                set(i - j, arr[i]);
            }
        }
        size_ = size_ - j;
        // HL:complete
        // look at remove_all() for guidance.




    }







}; 


// ...




#endif

