#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "course.h"
#include "database.h"
#include "menu.h"
#include "str_manip_utils.h"
#include "matching.h"
#define SRC_EXE "final_project" // source code or exeutable filename
using namespace std;
typedef Database DB;

void print_asc_order_units(DB database);

void print_des_order_units(DB database);

void print_alpha_order_course_id(DB database);

void print_rev_alpha_order_course_id(DB database);

void print_alpha_order_title(DB database);

void print_rev_alpha_order_course_ide_id(DB database);

void print_rev_alpha_order_title(DB database);

#define QUIT 4
#define ADD 1
#define FIND 2
#define DELETE 3
#define LIST 5

int main(int argc, char*argv[]) {
    if (argc<2) {
        cout << "Usage: ./" << SRC_EXE << " <your database TXT file>" << endl;
        return 1;
    }
    string filename = argv[1];
    DB course_db(filename);
    Menu menu;
    bool goback=false;
    string welcome_message = "Welcome to my University please select your options.";
    menu.welcome(welcome_message);

    int action = menu.prompt_action();

    while (action != QUIT) {
        switch (action) {
            case ADD:
            {

                Course new_course = menu.prompt_add_course(goback);
                if(!goback) {
                    if (course_db.find(new_course)>=0) {
                        cout << "\n" << endl;
                        cout << "This course already exists in the database... see the list below\n" << endl;
                        course_db.display_with_desc();

                    } else {
                        cout << "adding course" <<endl;
                        course_db.append(new_course);
                    }
                }
                break;
            }
            case FIND:
            {
                StringSerachCriteria cr = menu.prompt_find_course(goback);
                if (!goback) {
                    Database find_db = course_db.filter_by_criteria(cr);
                    if (find_db.size()>0) {
                        // add some descriptive message if necessary
                        find_db.display_with_desc();
                        string temp;
                        getline(cin,temp);
                    } else {
                        // print a course not found message
                        cout << "no courses found" << endl;
                    }
                }
                break;
            }
            case DELETE:
            {
                StringSerachCriteria cr = menu.prompt_delete_course(goback);
                if(cr.field.empty()) break;
                if(!goback) {
                    Database del_db = course_db.filter_by_criteria(cr);
                    if (del_db.size()>0) {
                        // JP: Delete, using the destructor? I'm not sure how to delete off dynamic array do we use clear()?
                        // HL: No destructor, its like a "remove" element from array
                        ///   Not deleting the whole array.
                        string response;
                        // display the course, ask for confirmation of deletion.
                        del_db.display_with_desc();
                        cout << "would you like to delete these courses (Y/N)?" << endl;
                        // HL: complete: get the cin and handle the deletion.
                        // Y: delete all the seleected courses (call delete_by_criteria)
                        // N: do nothing.
                        getline(cin, response);
                        if(response == "Y" || response == "y" || response == "(y)" || response == "(Y)") {
                            course_db.delete_by_criteria(cr);
                            cout << "You've deleted a course";
                            //course_db.display();
                        }
                        if(response == "N" || response == "n" || response == "(n)" || response == "(N)") {
                            cout << "You've done nothing" << endl;
                        }
                    } else {
                        // print a course not found message
                        cout << "no courses found" << endl;
                        // HL: complete
                    }
                }
                break;
            }
            case LIST:
            {
                auto x = menu.prompt_list_course(goback);

                switch(x){
                    case ASC_ORDER_BY_UNITS:                    print_asc_order_units(course_db); break;
                    case DESC_ORDER_BY_UNITS:                   print_des_order_units(course_db); break;
                    case ALPHA_ORDER_BY_COURSE_ID:              print_alpha_order_course_id(course_db); break;
                    case REV_ALPHA_ORDER_BY_COURSE_ID:          print_rev_alpha_order_course_ide_id(course_db); break;
                    case ALPHA_ORDER_BY_TITLE:                  print_alpha_order_title(course_db); break;
                    case REV_ALPHA_ORDER_BY_TITLE:              print_rev_alpha_order_title(course_db); break;

                    case NOT_SELECTED:
                        break;
                }
//                course_db.display(x);
                //I would like to do this but its not working -> system("cls");
                break;
            }
            default:
            {
                // do stuff for if all the other cases fails
                cout << "should not print here at all\n";
            }
        }
        action = menu.prompt_action();
    }
    string farewell_message = "Well, this is my university, I hope you liked it.";
    menu.farewell(farewell_message);
    course_db.save_to_file(filename);
    // delete course_db; (**)
    return 0;
}


void print_rev_alpha_order_title(DB database) {
    database.sort(REV_ALPHA_ORDER_BY_TITLE);
    database.display_with_desc();
    cout << endl;
}

void print_rev_alpha_order_course_ide_id(DB database) {
    database.sort(REV_ALPHA_ORDER_BY_COURSE_ID);
    database.display_with_desc();
    cout << endl;
}

void print_alpha_order_title(DB database) {
    database.sort(ALPHA_ORDER_BY_TITLE);
    database.display_with_desc();
    cout << endl;
}

void print_alpha_order_course_id(DB database) {
    database.sort(ALPHA_ORDER_BY_COURSE_ID);
    database.display_with_desc();
    cout << endl;
}

void print_des_order_units(DB database) {
    database.sort(DESC_ORDER_BY_UNITS);
    database.display_with_desc();
    cout << endl;
}

void print_asc_order_units(DB database) {
    database.sort(ASC_ORDER_BY_UNITS);
    database.display_with_desc();
    cout << endl;
}
