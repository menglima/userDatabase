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

static int studentlogin(void* data, int argc, char** argv, char** azColName)
{
    int i;

    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

    return 0;
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

	void searchCourse(int CRN)
	{

		cout << "Search called succesfully\n";
	} //end function
	void addCourse(int)
	{
		cout << "add called succesfully\n";
	}//end function
	void dropCourse(int)
	{
		cout << "drop called succesfully\n";
	}//end function
	void printSchedule()
	{
		cout << "Print Schedule called succesfully\n";
	}//end function
}; //end class
#pragma endregion

#pragma region Instructor
//derived class - instructor
class instructor_c : public user_c {
public:
	instructor_c();

    instructor_c(string ID, string first, string last, string title, string yearHired, string department, string username, string password);

    string* roster = new string[25];

	void searchCourse(std::string)
	{
		cout << "Search called succesfully\n";
	}//end function
	void printClass()
	{
		cout << "print called succesfully\n";
	}//end function
	void printSched()
	{
		cout << "schdule print called succesfully\n";
	}//end function
	
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
		cout << "add course called succesfully\n";
	}//end function
	void removeCourse()
	{
		cout << "remove course called succesfully\n";
	}//end function
	void addUser()
	{
		cout << "add user called succesfully\n";
	}//end function
	void removeUser()
	{
		cout << "remove user called succesfully\n";
	}//end function
	void searchStu(std::string)
	{
		cout << "Search student called succesfully\n";
	}//end function
	void searchCourse(std::string)
	{
		cout << "Search course called succesfully\n";
	}//end function
	void printClass()
	{
		cout << "print class called succesfully\n";
	}//end function
	void printCourses()
	{
		cout << "print courses called succesfully\n";
	}//end function

}; //end class
#pragma endregion

#pragma region Courses
class courses_c : public user_c {
public:
    courses_c();

    courses_c(string CRN, string title, string department, string time, string daysofWeek, string semester, string year, string credits);
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
    int crn = 0;
    int id = 0;

	//specify type of user to then call check function
	cout << "What type of user are you? (Enter number)\n";
	cout << "1. Student\n2. Instructor\n3. Admin\n";
	cin >> choice1;


    #pragma region Student menu
    //if student, call check function to login
    //choice 1 holds option for user type
    if (choice1 == 1)
    {
        do
        {
            cout << "Enter username: \n";
            cin >> username;
            
            string studentCheck = ("SELECT EMAIL FROM STUDENT WHERE EMAIL = ('" + username + "');");
            exit = sqlite3_exec(DB, studentCheck.c_str(), studentlogin, NULL, &messageError);

            if (exit == 0)
            {
                cout << "Enter password: ";
                cin >> password;

                string studentPassCheck = ("SELECT PASSWORD FROM STUDENT WHERE PASSWORD = ('" + password + "');");
                exit = sqlite3_exec(DB, studentPassCheck.c_str(), studentlogin, NULL, &messageError);

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
                    cout << "Enter the CRN: \n";
                    cin >> crn;
                    //function call with crn  parameter
                    break;



                case 2:
                    cout << "Enter the CRN: \n";
                    cin >> crn;
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
                    cout << "Enter the CRN: \n";
                    cin >> crn;
                    //function call with crn  parameter
                    break;



                case 2:
                    cout << "Enter the CRN: \n";
                    cin >> crn;
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
