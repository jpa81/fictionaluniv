
#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "course.h"
#include "database.h"
#include "str_manip_utils.h"
#include "matching.h"

#define QUIT 4
#define ADD 1
#define FIND 2
#define DELETE 3
#define LIST 5



// todo: fix the bug where menu shows up twice after running find

class Menu {
private:
	
public:
	Menu() {}



	int prompt_action() {
	    string input;
	    while (true) {

	        cout << "please select one of the following actions:" << endl;
	        cout << "(A)dd a course.\n(F)ind a course.\n(D)elete a course. \n(L)ist courses. \n(Q)uit \n\n";
	        cout << "Please input your choice. \n";


	        getline(cin, input);
	        if (check_input_option(input, "A")) {
	            return ADD;
	        } else if (check_input_option(input, "F")) {
	            return FIND;
	        } else if (check_input_option(input, "D")) {
	            return DELETE;
	        } else if (check_input_option(input, "L")) {
	            return LIST;
	        } else if (check_input_option(input, "Q")) {
	            return QUIT;
	        } else {
	            cout << "Please try again\n" << endl;
	        }

	    }
	}

	void welcome(string welcome_message) {
		cout << welcome_message << endl;

	}

	void farewell(string farewell_message) {
		cout << farewell_message << endl;
	}

//    match_type prompt_string_match(bool & goback, int item) {
//        return NUM_RANGE;
//    }

	match_type prompt_string_match(bool & goback) {
		cout << "What kind of search would you like?\n" << endl;
		cout << "(E)xact match\n(S)ubstring match\n(W)ildcard match\n\n";
		cout << "(R)eturn to main menu\n\nEnter the letter of your choice:\n";
		string input;
		getline(cin,input);
		goback = (check_input_option(input, "R"));
		if(goback) {
			return NUM_RANGE; // return value doesnt matter here.
		}
		if(check_input_option(input, "E")) {
			return STR_EXACT;
		}
		if(check_input_option(input, "S")) {
			return STR_SUBSTRING;
		}
		if(check_input_option(input, "W")) {
			return STR_WILDCARD;
		}
		cout << "Invalid selection. please try again.\n";
		return prompt_string_match(goback);
	}

    match_type prompt_num_match(bool & goback) {
        cout << "What kind of search would you like?\n" << endl;
        cout << "(E)xact match\n(Ra)nge match\n\n";
        cout << "(R)eturn to main menu\n\nEnter the letter of your choice:\n";
        string input;
        getline(cin,input);
        goback = (check_input_option(input, "R"));
        if(goback) {
            return NUM_RANGE; // return value doesnt matter here.
        }
        if(check_input_option(input, "E")) {
            return NUM_EXACT;
        }
        if(check_input_option(input, "Ra")) {
            return NUM_RANGE;
        }
        cout << "Invalid selection. please try again.\n";
        return prompt_string_match(goback);
    }


	// handle the actions

	Course prompt_add_course(bool & goback) {
		if(goback) {} // keep complier happy, delete later

		// code can go here as well.
		string new_course_number;
		string new_subject;
		string new_title;
		string new_description;
		int new_units;


        // HL: complete
        // put you "cin" statements here.


        cout << "What is the subject: ";
        getline(cin, new_subject);
        transform(new_subject.begin(), new_subject.end(), new_subject.begin(), ::toupper);
        cout << "What is the course number: ";
        getline(cin, new_course_number);
        cout << "what is the title: ";
        getline(cin, new_title);
        cout << "What is the description: ";
        getline(cin, new_description);
        cout << "What is the number of units: ";
        cin >> new_units;
        string temp;
        getline(cin,temp);

        if(cin.fail()) {
            cerr << "Error with input...exiting code with EXIT FAILURE" << endl;
            exit(EXIT_FAILURE);
        }

        Course new_course(new_course_number, new_subject, new_title, new_description, new_units,temp); // you are free to edit this

        return new_course;
	}
/*
    Course* prompt_add_course(string new_course_number, string new_subject, string new_title, string new_description, int new_units) {

        return new Course(string new_course_number, string new_subject, string new_title, string new_description, int new_units);
    }

*/

	StringSerachCriteria prompt_find_course(bool & goback) {
		// returns the course to look up
		
		// this course is not physically in the DB, 
		// but the subject and number might be a match in the DB.

		StringSerachCriteria target;

		cout << "Search by ...\n";
		cout << "(S)ubject code of course.\n";
		cout << "Course (N)umber.\n";
		cout << "(U)nits.\n";
        cout << "(T)itle of course.\n\n";
		cout << "(R)eturn to main menu\n\nEnter the letter of your choice:\n";
		string input,pattern;
		getline(cin,input);
		goback = (check_input_option(input, "R"));
		if(goback) {
			return target; // return value doesnt matter here.
		}


        if (check_input_option(input,"U")) {
            match_type mtype = NUM_RANGE;
            if(goback) {
                return target; // return value doesnt matter here.
            }
            auto lower = 0, higher = 0;

            StringSerachCriteria scr("subject", lower, higher, mtype);
            string temp;
            getline(cin,temp);
            return scr;
        }

		if (check_input_option(input,"S")) {
			match_type mtype = prompt_string_match(goback);
			if(goback) {
				return target; // return value doesnt matter here.
			}
			cout << "Please enter your query for the course subject code\n";
			getline(cin,pattern);
			StringSerachCriteria scr("subject", pattern, mtype);
            string temp;
            getline(cin,temp);
			return scr;
		}

        if (check_input_option(input,"N")) {
            match_type mtype = prompt_string_match(goback);
            if(goback) {
                return target; // return value doesnt matter here.
            }
            cout << "Please enter your query for the course subject code\n";
            getline(cin,pattern);
            StringSerachCriteria scr("number", pattern, mtype);
            string temp;
            getline(cin,temp);
            return scr;
        }

        if (check_input_option(input,"T")) {
            match_type mtype = prompt_string_match(goback);
            if(goback) {
                return target; // return value doesnt matter here.
            }
            cout << "Please enter your query for the course subject code\n";
            getline(cin,pattern);
            StringSerachCriteria scr("title", pattern, mtype);
            string temp;
            getline(cin,temp);
            return scr;
        }


        // HL : add the 2 other if statements.




		cout << "Invalid selection. please try again.\n";
		// using recursion, 
		//  but you can use a while loop instead if you prefer
		return prompt_find_course(goback); 
	}

	StringSerachCriteria prompt_delete_course(bool & goback) {
		if(goback) {} // keep complier happy, delete later
		StringSerachCriteria c_to_del;


        cout << "Delete by ...\n";
        cout << "(S)ubject code of course.\n";
        cout << "Course (N)umber.\n";
        cout << "(T)itle of course.\n\n";
        cout << "(R)eturn to main menu\n\nEnter the letter of your choice:\n";
        string input,pattern;
        getline(cin,input);
        goback = (check_input_option(input, "R"));
        if(goback) {
            return c_to_del; // return value doesnt matter here.
        }

        if (check_input_option(input,"S")) {
            match_type mtype = prompt_string_match(goback);
            if(goback) {
                return c_to_del; // return value doesnt matter here.
            }
            cout << "Please enter your query for the course subject code\n";
            getline(cin,pattern);
            StringSerachCriteria scr("subject", pattern, mtype);
            string temp;
            getline(cin,temp);
            return scr;
        }


        if (check_input_option(input,"N")) {
            match_type mtype = prompt_string_match(goback);
            if(goback) {
                return c_to_del; // return value doesnt matter here.
            }
            cout << "Please enter your query for the course subject code\n";
            getline(cin,pattern);
            StringSerachCriteria scr("number", pattern, mtype);
            string temp;
            getline(cin,temp);
            return scr;
        }


        if (check_input_option(input,"T")) {
            match_type mtype = prompt_string_match(goback);
            if(goback) {
                return c_to_del; // return value doesnt matter here.
            }
            cout << "Please enter your query for the course subject code\n";
            getline(cin,pattern);
            StringSerachCriteria scr("title", pattern, mtype);
            string temp;
            getline(cin,temp);
            return scr;
        }

		// HL: complete (follow prompt_find_course as a guide)
		return c_to_del;
	}

	course_list_order prompt_list_course(bool & goback) {
        if (goback) {} // keep complier happy, delete later


        cout << "List by ...\n";
        cout << "(A)lphabetical order.\n";
        cout << "(Re)verse Alphabetical Order.\n";
        cout << "(As)cending unit numerical order\n";
        cout << "(D)escending unit numerical order\n\n";
        cout << "(R)eturn to main menu\n\nEnter the letter of your choice:\n";
        string input, pattern;
        getline(cin, input);
        goback = (check_input_option(input, "R"));


        if (check_input_option(input,"A")) {
           cout << "What do you want to sort by:" <<endl;
           cout << "(C)ourse ID" << endl;
           cout << "(T)itle" << endl;

           string in;
           getline(cin, in);

           if(check_input_option(in, "C")) return ALPHA_ORDER_BY_COURSE_ID;
           if(check_input_option(in, "T")) return ALPHA_ORDER_BY_TITLE;

        }

        if (check_input_option(input,"Re")) {
            cout << "What do you want to sort by:" <<endl;
            cout << "(C)ourse ID" << endl;
            cout << "(T)itle" << endl;

            string in;
            getline(cin, in);

            if(check_input_option(in, "C")) return REV_ALPHA_ORDER_BY_COURSE_ID;
            if(check_input_option(in, "T")) return REV_ALPHA_ORDER_BY_TITLE;

        }

        if (check_input_option(input,"As")) {
                return ASC_ORDER_BY_UNITS;
        }

        if (check_input_option(input,"D")) {
            return DESC_ORDER_BY_UNITS;
        }

        return NOT_SELECTED;

    }
};




#endif
