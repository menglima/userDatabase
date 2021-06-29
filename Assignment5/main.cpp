#include <string>
#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include <ostream>

using namespace std;


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

student_c studentlogin(void* data, int argc, char** argv, char** azColName)
{
    student_c temp;

    temp.ID = argv[0];
    temp.first = argv[1];
    temp.last = argv[2];
    temp.gradyear = argv[3];
    temp.department = argv[4];
    temp.username = argv[5];
    temp.password = argv[6];
    printf("\n");

    return temp;
}

courses_c course(void* data, int argc, char** argv, char** azColName)
{
    courses_c temp;

    temp.CRN = argv[0];
    temp.title = argv[1];
    temp.department = argv[2];
    temp.time = argv[3];
    temp.daysofWeek = argv[4];
    temp.semester = argv[5];
    temp.year = argv[6];
    temp.credits = argv[7];

    printf("\n");

    return temp;
}

instructor_c instructor(void* data, int argc, char** argv, char** azColName)
{
    instructor_c temp;

    temp.ID = argv[0];
    temp.first = argv[1];
    temp.last = argv[2];
    temp.title = argv[3];
    temp.yearHired = argv[4];
    temp.department = argv[5];
    temp.username = argv[6];
    temp.password = argv[7];

    printf("\n");

    return temp;
}

admin_c admin(void* data, int argc, char** argv, char** azColName)
{
    admin_c temp;

    temp.ID = argv[0];
    temp.first = argv[1];
    temp.last = argv[2];
    temp.title = argv[3];
    temp.office = argv[4];
    temp.username = argv[5];
    temp.password = argv[6];

    printf("\n");

    return temp;
}
#pragma region User
//base class - user
class user_c {

public:
	user_c();
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
	student_c();

    student_c(string ID, string first, string last, string gradyear, string department, string username, string password);

    string* schedule = new string[5];


	void addCourse(string CRN)
	{
		cout << "add called succesfully\n";
        //save a string from a select of a certain course and add it to the array "schedule"
        
	}//end function
	void dropCourse(string CRN)
	{
		cout << "drop called succesfully\n";
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
	}//end function
    void searchCourse(string CRN)
    {
        //open the database file
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);			//open the database
        char* messageError = 0;

        string search = ("SELECT CRN FROM COURSES WHERE COURSES.CRN = ('" + CRN + "');");
        exit = sqlite3_exec(DB, search.c_str(), callback, NULL, &messageError);

    } //end function

    string ID, first, last, gradyear, department, username, password;
}; //end class
#pragma endregion

#pragma region Instructor
//derived class - instructor
class instructor_c : public user_c {
public:
	instructor_c();

    instructor_c(string ID, string first, string last, string title, string yearHired, string department, string username, string password);

    string* roster = new string[25];

    void assembleRoster()
    {

    }
    void printRoster()
    {
        cout << "schdule print called succesfully\n";
    }//end function

	void searchCourse(string CRN)
	{
        //open the database file
        sqlite3* DB;
        int exit = 0;
        exit = sqlite3_open("C:\\Users\\menglima\\Documents\\School\\SQLite\\assignment3db.db", &DB);			//open the database
        char* messageError = 0;

        string search = ("SELECT CRN FROM COURSES WHERE COURSES.CRN = ('" + CRN + "');");
        exit = sqlite3_exec(DB, search.c_str(), callback, NULL, &messageError);
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
	admin_c();

    admin_c(string ID, string first, string last, string title, string office, string username, string password);

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
        string insert("INSERT into COURSES VALUES('" + CRN + "', '" + title + "', '" + dept + "', '" + instructor + "', '" + time + "', '" + days + "', '" + semester + "', '" + year + "', '" + credit + "');");
        exit = sqlite3_exec(DB, insert.c_str(), callback, NULL, NULL);
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

        //print all info for one course
        string search("SELECT * from COURSES where COURSES.CRN = ('" + crn + "');");
        exit = sqlite3_exec(DB, search.c_str(), callback, NULL, NULL);
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

    string ID, first, last, title, office, username, password;

}; //end class
#pragma endregion

#pragma region Courses
class courses_c : public user_c {
public:
    courses_c();

    courses_c(string CRN, string title, string department, string time, string daysofWeek, string semester, string year, string credits);

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
    student_c student("", "", "", "", "", "", "");
    instructor_c instructor("", "", "", "", "", "", "", "");
    admin_c admin("", "", "", "", "", "", "");

	//specify type of user to then call check function
	cout << "What type of user are you? (Enter number)\n";
	cout << "1. Student\n2. Instructor\n3. Admin\n";
	cin >> choice1;


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

                string studentCheck = ("SELECT EMAIL FROM STUDENT WHERE STUDENT.EMAIL = ('" + username + "');");
                exit = sqlite3_exec(DB, studentCheck.c_str(), callback, NULL, &messageError);

                cout << "Enter password: ";
                cin >> password;
                string pass = ("UPDATE STUDENT SET PASSWORD = ('" + password + "') WHERE USERNAME = ('" + username + "');");
                exit = sqlite3_exec(DB, pass.c_str(), callback, NULL, &messageError);

                exitLoop = 1;
            }
            else
            {
                //login with original username/password
                cout << "Enter username: \n";
                cin >> username;

                string studentCheck = ("SELECT EMAIL FROM STUDENT WHERE STUDENT.EMAIL = ('" + username + "');");
                exit = sqlite3_exec(DB, studentCheck.c_str(), callback, NULL, &messageError);

                cout << "Enter password: ";
                cin >> password;

                string studentPassCheck = ("SELECT PASSWORD FROM STUDENT WHERE STUDENT.PASSWORD = ('" + password + "');");
                
                student = sqlite3_exec(DB, studentPassCheck.c_str(), studentlogin, NULL, &messageError);
                
            }

            cout << "Enter username: \n";
            cin >> username;
            
            string studentCheck = ("SELECT EMAIL FROM STUDENT WHERE STUDENT.EMAIL = ('" + username + "');");
            exit = sqlite3_exec(DB, studentCheck.c_str(), callback, NULL, &messageError);

            if (exit == 0)
            {
                cout << "Enter password: ";
                cin >> password;
                int check = 0;
                string studentPassCheck = ("SELECT PASSWORD FROM STUDENT WHERE STUDENT.PASSWORD = ('" + password + "');");
                exit = sqlite3_exec(DB, studentPassCheck.c_str(), callback, NULL, &messageError);

                if (check == 0)
                {
                    cout << "No password for user: " << username << endl;
                    cout << "Enter new password: " << endl;
                    cin >> password;
                    string insertPass = ("UPDATE STUDENT SET PASSWORD = ('" + password + "') WHERE STUDENT.EMAIL = ('" + username + "');");
                    exit = sqlite3_exec(DB, insertPass.c_str(), callback, NULL, &messageError);
                    string printPass = "SELECT PASSWORD FROM STUDENT WHERE STUDENT.EMAIL = ('" + username + "');";
                    exit = sqlite3_exec(DB, printPass.c_str(), callback, NULL, &messageError);
                    cout << "\nPassword updated. Log-in with new credentials" << endl;
                }
            }
            else
            {
                cout << "Username Incorrect. Try again.\n\n";

            }
            //correct = student.login(username, password); //return an int depending on login info match
            if (correct == 1)
            {

            }
            else
            {

            }
        } while (exitLoop != 1);

            //correct holds result of login() function 1 or 0
        if (choice1 == 1)
        {
            cout << "Logged In Successfully\n\n";
            do
            {
                //enter integer for option
                cout << "Enter in the number of your choice: \n";
                cout << "1. Add course\n2. Remove course\n3. Search all courses\n4. Search one course\n5. Quit\n";
                cin >> choice2; //choice2 holds student menu option
                //switch for different options
                switch (choice2)
                {
                case 1:
                    cout << "Enter the CRN: \n";
                    cin >> crn;
                    //function call with crn  parameter
                    student.addCourse(crn);
                    break;



                case 2:
                    cout << "Enter the CRN: \n";
                    cin >> crn;
                    //function call with crn  parameter
                    student.dropCourse(crn);
                    break;



                case 3:
                    //function call for select * query
                    student.searchAll();
                    cout << "\n";
                    break;



                case 4:
                    cout << "Enter the CRN: \n";
                    cin >> crn;
                    //function call with crn  parameter
                    student.searchCourse(crn);
                    break;



                default: std::cout << "***\n";
                }//end switch



            } while (choice2 != 5); //choice2 = 5 will quit
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
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            //correct = instructor.login(username, password); //return an int depending on login info match
            if (correct == 1)
            {

            }
            else
            {
                cout << "Username or Password Incorrect. Try again.\n\n";
            }
        } while (correct != 1);
            //correct holds result of login() function 1 or 0
        if (correct == 1)
        {
            cout << "Logged In Successfully\n\n";
            do
            {
                //enter integer for option
                cout << "Enter in the number of your choice: \n";
                cout << "1. Add student\n2. Remove student\n3. Search all courses\n4. Search one course\n5. Print roster\n6. Quit\n";
                cin >> choice2; //choice2 holds student menu option
                //switch for different options
                switch (choice2)
                {
                case 1:
                    cout << "Enter the WIT ID: \n";
                    cin >> id;
                    //function call with crn  parameter
                    
                    break;



                case 2:
                    cout << "Enter the WIT ID: \n";
                    cin >> id;
                    //function call with crn  parameter
                    break;



                case 3:
                    //function call for select * query
                    cout << "\n";
                    break;



                case 4:
                    cout << "Enter the CRN: \n";
                    cin >> crn;
                    //function call with crn  parameter
                    break;



                case 5:
                    //function call for select * from course roster
                    instructor.printRoster();
                    break;



                default: std::cout << "***\n";
                }//end switch



            } while (choice2 != 6); //choice2 = 5 will quit
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
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;
        //correct = admin.login(username, password); //return an int depending on login info match
        if (correct == 1)
        {

        }
        else
        {
            cout << "Username or Password Incorrect. Try again.\n\n";
        }
    } while (correct != 1);
            //correct holds result of login() function 1 or 0
        if (correct == 1)
        {
            cout << "Logged In Successfully\n\n";
            do
            {
                //enter integer for option
                cout << "Enter in the number of your choice: \n";
                cout << "1. Add course\n2. Remove course\n3. Search all courses\n4. Search one course\n5. Quit\n";
                cin >> choice2; //choice2 holds student menu option
                //switch for different options
                switch (choice2)
                {
                case 1:
                    //function call with crn  parameter
                    admin.addCourse();
                    break;



                case 2:
                    //function call with crn  parameter
                    admin.removeCourse();
                    break;



                case 3:
                    //function call for select * query
                    admin.printCourses();
                    cout << "\n";
                    break;



                case 4:
                    //function call with crn  parameter
                    admin.searchCourse();
                    break;



                default: std::cout << "***\n";
                }//end switch



            } while (choice2 != 5); //choice2 = 5 will quit
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
