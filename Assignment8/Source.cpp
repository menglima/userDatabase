#include <string>
#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <ostream>
#include <vector>
#include <list>

using namespace std;

#pragma region Callback Functions
/*************************************************************************************************
 The callback() function is invoked for each result row coming out of the evaluated SQL statement
 1st argument - the 4th argument provided by sqlite3_exec() and is typically not used
 2nd argument - number of columns in the result
 3rd argument - an array of strings containing the fields in that row
 4th argument - an array of strings containing the names of the columns
*************************************************************************************************/
static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

    }

    printf("\n");

    return 0;
}

static int studentlogin(void* data, int argc, char** argv, char** azColName)
{

    if (argc == 0)    //nothing in the row; shouldn’t happen

        return -1;

    auto& container = *static_cast<vector<string>*>(data);         //create vector


    //store data from the first column if it exists
    if (!argv[0])
    {
        container.push_back("NULL");

    }
    else
    {
        container.push_back(argv[0]);    //store column 0
        container.push_back(argv[1]);
        container.push_back(argv[2]);
        container.push_back(argv[3]);
        container.push_back(argv[4]);
        container.push_back(argv[5]);
        container.push_back(argv[6]);
        printf("\n");

    }
    return 0;
}

static int courseSet(void* data, int argc, char** argv, char** azColName)
{
    if (argc == 0)    //nothing in the row; shouldn’t happen

        return -1;

    auto& container = *static_cast<vector<string>*>(data);         //create vector


    //store data from the first column if it exists
    if (!argv[0])
    {
        container.push_back("NULL");

    }
    else
    {
        container.push_back(argv[0]);    //store column 0
        container.push_back(argv[1]);
        container.push_back(argv[2]);
        container.push_back(argv[3]);
        container.push_back(argv[4]);
        container.push_back(argv[5]);
        container.push_back(argv[6]);
        container.push_back(argv[7]);
        container.push_back(argv[8]);
        container.push_back(argv[9]);

        printf("\n");

    }
    return 0;
}

static int courseCheck(void* data, int argc, char** argv, char** azColName)
{
    if (argc == 0)    //nothing in the row; shouldn’t happen

        return -1;

    auto& container = *static_cast<vector<string>*>(data);         //create vector


    //store data from the first column if it exists
    if (!argv[0])
    {
        container.push_back("NULL");

    }
    else
    {
        container.push_back(argv[0]);    //store column 0
        container.push_back(argv[1]);
        container.push_back(argv[2]);
        container.push_back(argv[3]);
        container.push_back(argv[4]);
        container.push_back(argv[5]);
        container.push_back(argv[6]);
        container.push_back(argv[7]);
        container.push_back(argv[8]);
        container.push_back(argv[9]);

        printf("\n");

    }
    return 0;
}

static int instructorLogin(void* data, int argc, char** argv, char** azColName)
{

    if (argc == 0)    //nothing in the row; shouldn’t happen

        return -1;

    auto& container = *static_cast<vector<string>*>(data);         //create vector


    //store data from the first column if it exists
    if (!argv[0])
    {
        container.push_back("NULL");

    }
    else
    {
        container.push_back(argv[0]);    //store column 0
        container.push_back(argv[1]);
        container.push_back(argv[2]);
        container.push_back(argv[3]);
        container.push_back(argv[4]);
        container.push_back(argv[5]);
        container.push_back(argv[6]);
        container.push_back(argv[7]);
        printf("\n");

    }
    return 0;
}

static int adminLogin(void* data, int argc, char** argv, char** azColName)
{
    if (argc == 0)    //nothing in the row; shouldn’t happen

        return -1;

    auto& container = *static_cast<vector<string>*>(data);         //create vector


    //store data from the first column if it exists
    if (!argv[0])
    {
        container.push_back("NULL");

    }
    else
    {
        container.push_back(argv[0]);    //store column 0
        container.push_back(argv[1]);
        container.push_back(argv[2]);
        container.push_back(argv[3]);
        container.push_back(argv[4]);
        container.push_back(argv[5]);
        container.push_back(argv[6]);
        printf("\n");

    }
    return 0;
}
#pragma endregion

#pragma region User
//base class - user
class user_c {

public:
    user_c() {}
    //constructor
    user_c(string u, string p)
    {
        username = u;
        password = p;
        //cout << username << " has been created\n";
    }//end constructor
    void setName(string u, string p)
    {
        username = u;
        password = p;
    }//end set

    string getFirst() { return username; } //end getname
    string getLast() { return password; }//end getname

protected:
    string username, password;
}; //end class

#pragma endregion 

#pragma region Student
//derived class - student
class student_c : public user_c {

public:
    student_c() {}

    student_c(string ID, string first, string last, string gradyear, string department, string username, string password) {}

    void addCourse(string CRN, int count)
    {
        //save a string from a select of a certain course and add it to the array "schedule"
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        vector<string> container;
        vector<string> day;



        if (count == 0)
        {
            //search for the course CRN in database
            string setCourse = ("SELECT * FROM COURSES WHERE CRN = ('" + CRN + "');");
            exit = sqlite3_exec(DB, setCourse.c_str(), courseSet, &container, &messageError);
            if (container.size() == 0)
            {
                cout << "Incorrect CRN. Try again.\n";

            }
            else
            {
                //insert into student schedule
                string insertCourse = ("INSERT INTO SCHEDULE VALUES('" + container[0] + "', '" + container[1] + "', '" + container[2] + "', '" + container[3] + "', '" + container[4] + "', '" + container[5] + "', '" + container[6] + "', '" + container[7] + "', '" + container[8] + "');");
                exit = sqlite3_exec(DB, insertCourse.c_str(), callback, NULL, &messageError);

                cout << "Course successfully added\n";
            }

        }
        else
        {
            //search for the course CRN in database
            string setCourse = ("SELECT * FROM COURSES WHERE CRN = ('" + CRN + "');");
            exit = sqlite3_exec(DB, setCourse.c_str(), courseSet, &container, &messageError);
            if (container.size() == 0)
            {
                cout << "Incorrect CRN. Try again.\n";

            }
            else
            {

                string days = ("SELECT * FROM SCHEDULE WHERE SEMESTER = ('" + container[6] + "');");
                exit = sqlite3_exec(DB, days.c_str(), courseCheck, &day, &messageError);
                //check day conflict
                if (container[5] == day[5])
                {
                    //check time conflict
                    if (container[4] == day[4])
                    {
                        cout << "Time/Day confict in schedule. Try again.";
                    }

                }
                //add to schedule because no time or day conflicts
                else
                {
                    //insert into student schedule
                    string insertCourse = ("INSERT INTO SCHEDULE VALUES('" + container[0] + "', '" + container[1] + "', '" + container[2] + "', '" + container[3] + "', '" + container[4] + "', '" + container[5] + "', '" + container[6] + "', '" + container[7] + "', '" + container[8] + "');");
                    exit = sqlite3_exec(DB, insertCourse.c_str(), callback, NULL, &messageError);
                    cout << "Course successfully added\n";

                }
            }


        }



    }//end function
    void dropCourse()
    {
        //save a string from a select of a certain course and add it to the array "schedule"
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        string crn;
        cout << "Enter the CRN for the course you want to remove: \n";
        cin >> crn;

        string deleteCourse = ("DELETE FROM SCHEDULE WHERE SCHEDULE.CRN = ('" + crn + "');");
        exit = sqlite3_exec(DB, deleteCourse.c_str(), courseSet, NULL, &messageError);

        cout << "Course removed successfully\n";

    }//end function
    void searchAll()
    {
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        //print all courses
        string search("SELECT * from COURSES;");
        exit = sqlite3_exec(DB, search.c_str(), callback, NULL, &messageError);
    }//end function
    void searchCourse(string CRN)
    {
        //open the database file
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);			//open the database
        char* messageError = 0;

        vector <string> container;
        string search = ("SELECT * FROM COURSES WHERE COURSES.CRN = ('" + CRN + "');");
        exit = sqlite3_exec(DB, search.c_str(), courseSet, &container, &messageError);
        if (container.size() == 0)
        {
            cout << "Incorrect CRN. Try again.\n";

        }
       

    } //end function

    void printSchedule()
    {
        //open the database file
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);			//open the database
        char* messageError = 0;

        string printSchedule = ("SELECT * FROM SCHEDULE;");
        exit = sqlite3_exec(DB, printSchedule.c_str(), callback, NULL, &messageError);

    }

    string ID, first, last, gradyear, department, username, password;
}; //end class
#pragma endregion

#pragma region Instructor
//derived class - instructor
class instructor_c : public user_c {
public:
    instructor_c() {}

    instructor_c(string ID, string first, string last, string title, string yearHired, string department, string username, string password) {}

    string* roster = new string[25];

    void addCourse(string CRN)
    {
        //save a string from a select of a certain course and add it to the array "schedule"
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        vector<string> container;

        string setCourse = ("SELECT * FROM COURSES WHERE CRN = ('" + CRN + "');");
        exit = sqlite3_exec(DB, setCourse.c_str(), courseSet, &container, &messageError);
        if (container.size() == 0)
        {
            cout << "Incorrect CRN. Try again.\n";

        }
        else
        {

            string insertCourse = ("INSERT INTO SCHEDULE VALUES('" + container[0] + "', '" + container[1] + "', '" + container[2] + "', '" + container[3] + "', '" + container[4] + "', '" + container[5] + "', '" + container[6] + "', '" + container[7] + "', '" + container[8] + "');");
            exit = sqlite3_exec(DB, insertCourse.c_str(), callback, NULL, &messageError);

            cout << "Course successfully added\n";
        }




    }//end function
    void dropCourse()
    {
        //save a string from a select of a certain course and add it to the table "schedule"
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        string crn;
        cout << "Enter the CRN for the course you want to remove: \n";
        cin >> crn;

        string deleteCourse = ("DELETE FROM SCHEDULE WHERE SCHEDULE.CRN = ('" + crn + "');");
        exit = sqlite3_exec(DB, deleteCourse.c_str(), courseSet, NULL, &messageError);



        cout << "Course removed successfully\n";



    }//end function



    void printSchedule()
    {
        //open the database file
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        string printSchedule = ("SELECT * FROM SCHEDULE;");
        exit = sqlite3_exec(DB, printSchedule.c_str(), callback, NULL, &messageError);



    }//end function

    void assembleRoster()
    {
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        string ID;
        cout << "Enter ID to add to roster: \n";
        cin >> ID;

        vector<string> container;

        string setCourse = ("SELECT * FROM STUDENT WHERE ID = ('" + ID + "');");
        exit = sqlite3_exec(DB, setCourse.c_str(), studentlogin, &container, &messageError);
        if (container.size() == 0)
        {
            cout << "Incorrect CRN. Try again.\n";

        }
        else
        {
            string insertCourse = ("INSERT INTO ROSTER VALUES('" + container[0] + "', '" + container[1] + "', '" + container[2] + "', '" + container[3] + "', '" + container[4] + "', '" + container[5] + "');");
            exit = sqlite3_exec(DB, insertCourse.c_str(), callback, NULL, &messageError);

            cout << "Student successfully added to roster\n";
        }


    }

    void removeStudent()
    {
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        string ID;
        cout << "Enter ID to remove student from roster: \n";
        cin >> ID;

        string deleteCourse = ("DELETE FROM ROSTER WHERE ROSTER.ID = ('" + ID + "');");
        exit = sqlite3_exec(DB, deleteCourse.c_str(), callback, NULL, &messageError);

        cout << "Student removed successfully from roster\n";

    }
    void printRoster()
    {
        //open the database file
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);			//open the database
        char* messageError = 0;

        string printSchedule = ("SELECT * FROM ROSTER;");
        exit = sqlite3_exec(DB, printSchedule.c_str(), callback, NULL, &messageError);


    }//end function

    void searchCourse()
    {
        //open the database file
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);			//open the database
        char* messageError = 0;

        string CRN;
        cout << "Enter the CRN for the course you want to search: \n";
        cin >> CRN;

        vector <string> container;
        string search = ("SELECT * FROM COURSES WHERE COURSES.CRN = ('" + CRN + "');");
        exit = sqlite3_exec(DB, search.c_str(), courseSet, &container, &messageError);
        if (container.size() == 0)
        {
            cout << "Incorrect CRN. Try again.\n";

        }

    }//end function
    void searchAll()
    {
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        //print all courses
        string search("SELECT * from COURSES;");
        exit = sqlite3_exec(DB, search.c_str(), callback, NULL, NULL);
    }

    string ID, first, last, title, yearHired, department, username, password;

}; //end class
#pragma endregion

#pragma region Admin

//derived class - admin
class admin_c : public user_c {
public:
    admin_c() {}

    admin_c(string ID, string first, string last, string title, string office, string username, string password) {}

    void addCourse()
    {
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        string CRN, year, credit;
        string title, dept, instructor, time, days, semester;

        cout << "Enter in the CRN: ";
        cin >> CRN;
        cout << "Enter in the title: ";
        cin >> title;
        cout << "Enter in the department: ";
        cin >> dept;
        cout << "Enter in the instructor: ";
        cin >> instructor;
        cout << "Enter in the time: ";
        cin >> time;
        cout << "Enter in the days: ";
        cin >> days;
        cout << "Enter in the semester: ";
        cin >> semester;
        cout << "Enter in the year: ";
        cin >> year;
        cout << "Enter in the credits: ";
        cin >> credit;
        string insert("INSERT into COURSES VALUES('" + CRN + "', '" + title + "', '" + dept + "', '" + instructor + "', '" + time + "', '" + days + "', '" + semester + "', '" + year + "', '" + credit + "', '" "');");
        exit = sqlite3_exec(DB, insert.c_str(), callback, NULL, NULL);

        cout << "Course added successfully.\n";

    }//end function
    void removeCourse()
    {
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        string crn;
        cout << "Enter in the CRN for the course to remove: ";
        cin >> crn;

        string remove("DELETE from COURSES WHERE COURSES.CRN = ('" + crn + "');");
        exit = sqlite3_exec(DB, remove.c_str(), callback, NULL, NULL);

        cout << "Course removed successfully.\n";

    }//end function
    void searchCourse()
    {
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        string crn;
        cout << "Enter the crn for the course to be searched: ";
        cin >> crn;

        vector <string> container;
        //print all info for one course
        string search("SELECT * from COURSES where COURSES.CRN = ('" + crn + "');");
        exit = sqlite3_exec(DB, search.c_str(), courseSet, &container, &messageError);
        if (container.size() == 0)
        {
            cout << "Incorrect CRN. Try again.\n";
          
        }

    }//end function

    void printCourses()
    {
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        //print all courses
        string search("SELECT * from COURSES;");
        exit = sqlite3_exec(DB, search.c_str(), callback, NULL, NULL);
    }//end function

    void addStudent()
    {
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        string id, first, last, year, major, email, password;

        cout << "Enter in the ID: ";
        cin >> id;
        cout << "Enter in the first name: ";
        cin >> first;
        cout << "Enter in the last name: ";
        cin >> last;
        cout << "Enter in the grad. year: ";
        cin >> year;
        cout << "Enter in the major: ";
        cin >> major;
        cout << "Enter in the email: ";
        cin >> email;
        cout << "Enter in the password: ";
        cin >> password;

        string insert("INSERT into student VALUES('" + id + "', '" + first + "', '" + last + "', '" + year + "', '" + major + "', '" + email + "', '" + password + "');");
        exit = sqlite3_exec(DB, insert.c_str(), callback, NULL, NULL);
        cout << "Student added successfully.\n";

    }
    void addInstructor()
    {
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        string id, first, last, title, year, department, email, password;

        cout << "Enter in the ID: ";
        cin >> id;
        cout << "Enter in the first name: ";
        cin >> first;
        cout << "Enter in the last name: ";
        cin >> last;
        cout << "Enter in the title: ";
        cin >> title;
        cout << "Enter in the year hired: ";
        cin >> year;
        cout << "Enter in the department: ";
        cin >> department;
        cout << "Enter in the email: ";
        cin >> email;
        cout << "Enter in the password: ";
        cin >> password;

        string insert("INSERT into instructor VALUES('" + id + "', '" + first + "', '" + last + "', '" + title + "', '" + year + "', '" + department + "', '" + email + "', '" + password + "');");
        exit = sqlite3_exec(DB, insert.c_str(), callback, NULL, NULL);
        cout << "Instructor added successfully.\n";
    }
    void removeStudent()
    {

        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        string id;
        cout << "Enter in the ID for the student to remove: ";
        cin >> id;

        string remove("DELETE from student WHERE student.id = ('" + id + "');");
        exit = sqlite3_exec(DB, remove.c_str(), callback, NULL, NULL);
        
        cout << "Student removed successfully.\n";
    }
    void removeInstructor()
    {
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        string id;
        cout << "Enter in the ID for the instructor to remove: ";
        cin >> id;

        string remove("DELETE from instructor WHERE instructor.id = ('" + id + "');");
        exit = sqlite3_exec(DB, remove.c_str(), callback, NULL, NULL);

        cout << "Instructor removed successfully.\n";
    }

    void printStudent()
    {
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        //print all courses
        string search("SELECT * from student;");
        exit = sqlite3_exec(DB, search.c_str(), callback, NULL, NULL);
    }
    void printInstructor()
    {
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        //print all courses
        string search("SELECT * from instructor;");
        exit = sqlite3_exec(DB, search.c_str(), callback, NULL, NULL);
    }
    void linkUnlink()
    {
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);            //open the database
        char* messageError = 0;

        string crn = "";
        cout << "Enter the CRN for the course you want to link/unlink: ";
        cin >> crn;

        int option;
        cout << "Do you want to link (1) or unlink (2)?: ";
        cin >> option;

        if (option == 1)
        {

            int stuInst;
            cout << "Student (1) or Instructor (2)?: ";
            cin >> stuInst;
            if (stuInst == 1)
            {

                string email;
                cout << "Enter the e-mail of the student you want to link: ";
                cin >> email;
                string link = ("UPDATE COURSES SET STUDENT = ('" + email + "') WHERE CRN = ('" + crn + "');");
                exit = sqlite3_exec(DB, link.c_str(), callback, NULL, &messageError);


                cout << "Student successfully linked.\n";
                


            }
            else if (stuInst == 2)
            {
                string last;
                cout << "Enter the last name of the instructor you want to link: ";
                cin >> last;
                string link = ("UPDATE COURSES SET instructor = ('" + last + "') WHERE CRN = ('" + crn + "');");
                exit = sqlite3_exec(DB, link.c_str(), callback, NULL, &messageError);
                cout << "Instructor successfully linked.\n";


            }
            else
            {
                cout << "Enter a valid option. Try again.\n\n";
                return;

            }
        }
        else if (option == 2)
        {
            int stuInst;
            cout << "Student (1) or Instructor (2)?: ";
            cin >> stuInst;
            if (stuInst == 1)
            {

                string link = ("UPDATE COURSES SET STUDENT = '' WHERE CRN = ('" + crn + "');");
                exit = sqlite3_exec(DB, link.c_str(), callback, NULL, &messageError);
                cout << "Student successfully unlinked.\n";


            }
            else if (stuInst == 2)
            {

                string link = ("UPDATE COURSES SET instructor = '' WHERE CRN = ('" + crn + "');");
                exit = sqlite3_exec(DB, link.c_str(), callback, NULL, &messageError);
                cout << "Instructor successfully unlinked.\n";

            }
            else
            {
                cout << "Enter a valid option. Try again.\n\n";
                return;
            }
        }
        else
        {
            cout << "Enter a valid option. Try again.\n\n";
            return;
        }
        cout << "\n";
        return;
    }
    string ID, first, last, title, office, username, password;

}; //end class
#pragma endregion

#pragma region Courses
class courses_c : public user_c {
public:
    courses_c() {}

    courses_c(string CRN, string title, string department, string time, string daysofWeek, string semester, string year, string credits) {}

    string getCRN()
    {
        return CRN;
    }

    courses_c* next, * previous;

    string CRN, title, department, time, daysofWeek, semester, year, credits;
};

#pragma endregion

#pragma region Main
int main(int argc, char** argv)
{

    //open the database file
    sqlite3* DB;

    /*******************************************************************
    Creating a table
    Create a string then pass the string into the sqlite3_exec function
    ********************************************************************/
    int exit = 0;
    exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);			//open the database
    char* messageError = 0;

    //declare new student, instructor, admin with username and password
    string username = "";
    string password = "";
    int choice1 = 0;
    int choice2 = 0;
    int correct = 0;
    string crn;
    int id = 0;

    //instantiate objects for student admin and instructor
    student_c* student = new student_c();
    instructor_c* instructor = new instructor_c();
    admin_c* admin = new admin_c();

    //specify type of user to then call check function
    cout << "What type of user are you? (Enter number)\n";
    cout << "1. Student\n2. Instructor\n3. Admin\n";
    cin >> choice1;

    //clear the schedule table every time a user is chosen
    string deleteSchedule = ("DELETE FROM SCHEDULE;");
    exit = sqlite3_exec(DB, deleteSchedule.c_str(), callback, NULL, &messageError);
    int scheduleCount = 0;

#pragma region Student menu
    //if student, call check function to login
    //choice 1 holds option for user type
    int exitLoop = 0;

    if (choice1 == 1)
    {
        do
        {
            string verify = "";
            cout << "Is this your first time logging in? (Y/N): " << endl;
            cin >> verify;

            if ((verify == "Y") || (verify == "y"))
            {

                //ask for new password then update db file with that password
                cout << "Enter username: \n";
                cin >> username;

                cout << "Enter password: \n";
                cin >> password;
                string pass = ("UPDATE STUDENT SET PASSWORD = ('" + password + "') WHERE USERNAME = ('" + username + "');");
                exit = sqlite3_exec(DB, pass.c_str(), callback, NULL, &messageError);
            
                cout << "Password Updated" << endl;
                exitLoop = 1;
            }
            else
            {
                //login with original username/password
                cout << "Enter username: \n";
                cin >> username;
                //username needs to be correct and the only thing being checked is password

                cout << "Enter password: \n";
                cin >> password;
                password = password;
                string studentPassCheck = ("SELECT * FROM STUDENT WHERE STUDENT.EMAIL = ('" + username + "');");

                vector<string> container;         //local vector called container

                /* Execute sqlite statement created as a string named statement */

                //call the new callback function and pass in the vector by reference
                exit = sqlite3_exec(DB, studentPassCheck.c_str(), studentlogin, &container, &messageError);

                if (container.size() == 0)
                {
                    cout << "Incorrect login. Try again.\n";
                    exitLoop = 0;

                }
                else if ((username == container[5]) && (password == container[6]))
                {
                    cout << "Logged in successfully\n" << endl;
                    exitLoop = 1;
                }
                else
                {
                    cout << "Incorrect login. Try again." << endl;
                }


            }

        } while (exitLoop != 1);
        //correct holds result of login() function 1 or 0
        if (choice1 == 1)
        {
            do
            {
                //enter integer for option
                cout << "Enter in the number of your choice: \n";
                cout << "1. Add course\n2. Remove course\n3. Search all courses\n4. Search one course\n5. Print Schedule\n6. Quit\n";
                cin >> choice2; //choice2 holds student menu option
                //switch for different options
                switch (choice2)
                {
                case 1:
                    cout << "Enter the CRN for the course you want to add: \n";
                    cin >> crn;
                    //function call with crn  parameter
                    student->addCourse(crn, scheduleCount);
                    scheduleCount++;

                    break;



                case 2:

                    //function call with crn  parameter
                    student->dropCourse();
                    scheduleCount--;
                    break;



                case 3:
                    //function call for select * query
                    student->searchAll();
                    cout << "\n";
                    break;



                case 4:
                    cout << "Enter the CRN: \n";
                    cin >> crn;
                    //function call with crn  parameter
                    student->searchCourse(crn);
                    break;

                case 5:
                    student->printSchedule();
                    break;

                default: std::cout << "***\n";
                }//end switch



            } while (choice2 != 6); //choice2 = 5 will quit
        }//end student menu

    }//end login for student
#pragma endregion

#pragma region Instructor menu
//if instructor
//choice1 will hold 2 for instructor
    else if (choice1 == 2)
    {
        do
        {
            string verify = "";
            cout << "Is this your first time logging in? (Y/N): " << endl;
            cin >> verify;

            if ((verify == "Y") || (verify == "y"))
            {
                //ask for new password then update db file with that password
                cout << "Enter username: \n";
                cin >> username;

                cout << "Enter password: \n";
                cin >> password;
                string pass = ("UPDATE INSTRUCTOR SET PASSWORD = ('" + password + "') WHERE USERNAME = ('" + username + "');");
                exit = sqlite3_exec(DB, pass.c_str(), callback, NULL, &messageError);

                cout << "Password Updated" << endl;
                exitLoop = 1;
            }
            else
            {
                //login with original username/password
                cout << "Enter username: \n";
                cin >> username;

                //username needs to be correct and the only thing being checked is password

                cout << "Enter password: \n";
                cin >> password;

                string instructorPassCheck = ("SELECT * FROM INSTRUCTOR WHERE INSTRUCTOR.EMAIL = ('" + username + "');");

                vector<string> container;         //local vector called container

                /* Execute sqlite statement created as a string named statement */

                //call the new callback function and pass in the vector by reference
                exit = sqlite3_exec(DB, instructorPassCheck.c_str(), instructorLogin, &container, &messageError);

                if (container.size() == 0)
                {
                    cout << "Incorrect login. Try again.\n";
                    exitLoop = 0;

                }
                else if ((username == container[6]) && (password == container[7]))
                {
                    cout << "Logged in successfully\n" << endl;
                    exitLoop = 1;
                }
                else
                {
                    cout << "Incorrect login. Try again." << endl;
                }


            }

        } while (exitLoop != 1);
        //correct holds result of login() function 1 or 0
        if (choice1 == 2)
        {
            do
            {
                //enter integer for option
                cout << "Enter in the number of your choice: \n";
                cout << "1. Add student\n2. Remove student\n3. Search all courses\n4. Search one course\n5. Print roster\n6. Add course\n7. Remove course\n8. Print schedule\n9. Quit\n";
                cin >> choice2; //choice2 holds student menu option
                //switch for different options
                switch (choice2)
                {
                case 1:

                    //function call with crn  parameter
                    instructor->assembleRoster();
                    break;



                case 2:
                    //function call with crn  parameter
                    instructor->removeStudent();
                    break;



                case 3:
                    //function call for select * query
                    instructor->searchAll();
                    cout << "\n";
                    break;



                case 4:
                    //function call with crn  parameter
                    instructor->searchCourse();
                    break;



                case 5:
                    //function call for select * from course roster
                    instructor->printRoster();
                    break;

                case 6:
                    cout << "Enter the CRN for the course you want to add: \n";
                    cin >> crn;
                    //function call with crn  parameter
                    instructor->addCourse(crn);
                    break;



                case 7:
                    instructor->dropCourse();
                    break;



                case 8:
                    instructor->printSchedule();
                    cout << endl;
                    break;


                default: std::cout << "***\n";
                }//end switch



            } while (choice2 != 9); //choice2 = 5 will quit
        }//end student menu
    }//end login for instructor
#pragma endregion

#pragma region Admin menu
//if admin, call check function to login
//choice 1 holds option for user type
    else if (choice1 == 3)
    {
        do
        {
            string verify = "";
            cout << "Is this your first time logging in? (Y/N): " << endl;
            cin >> verify;

            if ((verify == "Y") || (verify == "y"))
            {
                //ask for new password then update db file with that password
                cout << "Enter username: \n";
                cin >> username;

                cout << "Enter password: \n";
                cin >> password;
                string pass = ("UPDATE ADMIN SET PASSWORD = ('" + password + "') WHERE USERNAME = ('" + username + "');");
                exit = sqlite3_exec(DB, pass.c_str(), callback, NULL, &messageError);

                cout << "Password Updated" << endl;
                exitLoop = 1;
            }
            else
            {
                //login with original username/password
                cout << "Enter username: \n";
                cin >> username;

                //username needs to be correct and the only thing being checked is password

                cout << "Enter password: \n";
                cin >> password;

                string adminPassCheck = ("SELECT * FROM ADMIN WHERE ADMIN.EMAIL = ('" + username + "');");

                vector<string> container;         //local vector called container

                /* Execute sqlite statement created as a string named statement */

                //call the new callback function and pass in the vector by reference
                exit = sqlite3_exec(DB, adminPassCheck.c_str(), adminLogin, &container, &messageError);
                if (container.size() == 0)
                {
                    cout << "Incorrect login. Try again.\n";
                    exitLoop = 0;

                }
                else if ((username == container[5]) && (password == container[6]))
                {
                    cout << "Logged in successfully\n" << endl;
                    exitLoop = 1;
                }
                else
                {
                    cout << "Incorrect login. Try again." << endl;
                }


            }

        } while (exitLoop != 1);
        //correct holds result of login() function 1 or 0
        if (choice1 == 3)
        {
            string clearLink = ("UPDATE COURSES SET STUDENT = '';");
            exit = sqlite3_exec(DB, clearLink.c_str(), callback, NULL, &messageError);

            do
            {
                //enter integer for option
                cout << "Enter in the number of your choice: \n";
                cout << "1. Add course\n2. Remove course\n3. Search all courses\n4. Search one course\n5. Add Student\n6. Add Instructor\n7. Remove Student\n8. Remove Instructor\n9. Print Student list\n10. Print Instructor list\n11. Link/Unlink\n12. Quit\n";
                cin >> choice2; //choice2 holds student menu option
                //switch for different options
                switch (choice2)
                {
                case 1:
                    //function call with crn  parameter
                    admin->addCourse();
                    break;



                case 2:
                    //function call with crn  parameter
                    admin->removeCourse();
                    break;



                case 3:
                    //function call for select * query
                    admin->printCourses();
                    cout << "\n";
                    break;



                case 4:
                    //function call with crn  parameter
                    admin->searchCourse();
                    break;

                case 5: 
                    admin->addStudent();
                    break;

                case 6:
                    admin->addInstructor();

                    break;

                case 7:

                    admin->removeStudent();

                    break;
                case 8:

                    admin->removeInstructor();

                    break;
                case 9:

                    admin->printStudent();

                    break;
                case 10:

                    admin->printInstructor();

                    break;
                case 11:

                    admin->linkUnlink();

                    break;

                default: std::cout << "***\n";
                }//end switch



            } while (choice2 != 12); //choice2 = 5 will quit
        }//end student menu
    }//end login for admin
#pragma endregion

    else
    {
        cout << "Invalid Input\n";
    }
    return 0;
}
#pragma endregion
