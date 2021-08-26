
#ifndef MATCHING_H
#define MATCHING_H

#include "course.h"
#include "str_manip_utils.h"


// for wildcard, 
//    '*' matches any sequence of chars, inculing empty string.
//    '?' matches any one char.
// '\?', '\*' can escape them.



enum match_type {
	STR_SUBSTRING,
	STR_EXACT,
	STR_WILDCARD, // OPTIONAL BUT I THINK IS FUN TO HAVE.
	NUM_EXACT,
	NUM_RANGE
};


class Criteria {
public:
	virtual bool is_match(Course &c) = 0;
	virtual ~Criteria() = default;

    int p1,p2, bounded_search;

    virtual int get_bounded_search() = 0;
};


class StringSerachCriteria: public Criteria {
public:
	string field,pattern;
	int p1, p2, bounded_search = 0;
	match_type mtype; // must be STR_?????? not NUM_???? 
						// you can do error check if you want.


	StringSerachCriteria() {}

    StringSerachCriteria(string the_field, int the_pattern, int the_pattern_2,
                         match_type the_type) : field(the_field),
                                                mtype(the_type)
    {
	    this->p1 = the_pattern;
	    this->p2 = the_pattern_2;
	    this->bounded_search = 1;

    }

    void set_bounded_search(int i){
	    this->bounded_search = i;
	}
	int get_bounded_search(){
	    return this->bounded_search;
	}

	StringSerachCriteria(string the_field, string the_pattern,
		match_type the_type) : field(the_field), pattern(the_pattern), 
	mtype(the_type)
	{}

	string attribute(Course &c) {
		if (field == "subject") {
			return c.get_subject();
		}
		if (field == "title") {
			return c.get_title();
		}
		if (field == "description") {
			return c.get_description();
		}
		if (field == "number") {
			return c.get_course_number();
		}
		return "invallid field!"; // should not reach here.
	}

	bool is_match(Course &c) {
		string attr = attribute(c);
		switch (mtype) {
			case STR_SUBSTRING:
			{
				return is_substr(attr, pattern);
			}
			case STR_EXACT:
			{
				return attr==pattern;
			}
			case STR_WILDCARD:
			{
				return wildcard_match(attr,pattern);
			}
			default:
				return false; // should not get here
		}
	}

};

// make something similar for a number search.


/*
class NumberSearchCriteria: public Criteria {
public:
    string field,pattern;
    match_type mtype; // must be STR_?????? not NUM_????
    // you can do error check if you want.

    NumberSearchCriteria() {}

    NumberSearchCriteria(string the_field, string the_pattern,
                         match_type the_type) : field(the_field), pattern(the_pattern),
                                                mtype(the_type)
    {}

    int attribute(Course &c) {
        if (field == "units") {
            return c.get_unit();
        }

        return 0; // should not reach here.
    }

    bool is_match(Course &c) {
        int attr = attribute(c);
        switch (mtype) {
            case NUM_RANGE:
            {
                auto lower = 0, higher = 0;
                cout << "Please enter the lowest integer value to search by: \n";
                cin >> lower;

                cout << "Please enter higher integer value to search by: \n";
                cin >> higher;

                for(auto i = 0 ; i < this->size_; i++){
                    if(this->arr[i].get_unit() >= lower && this->arr[i].get_unit() <= higher){
                        ret.append(this->arr[i]);
                    }
                }
                return ret;
//          result = this->filter_by_unit(lower, higher);;
            }
            case NUM_EXACT:
            {
                return attr==pattern;
            }
            default:
                return false; // should not get here
        }
    }

};
*/
#endif

