#include <string>
#include <iostream>
#ifndef CLASS_H   //because header only compiles once
#define CLASS_H
using namespace std;

//base class - user
class user_c {

public:
	//constructor
	user_c(std::string f, std::string l, int i) {
		fname = f;
		lname = l;
		id = i;
		cout << fname << " " << lname << " has been created\n";
	}//end constructor
	void setName(std::string f, std::string l) {
		fname = f;
		lname = l;
	}//end set
	void setID(int i) { id = i; } //end setID
	virtual void printUser() {    //virtual to be used in derived classes
		cout << "Name: " << fname << " " << lname << std::endl;
		cout << "ID: " << id << std::endl;
	}//end print
	std::string getFirst() { return fname; } //end getname
	std::string getLast() { return lname; }//end getname
	int getID() { return id; } //end getID
	~user_c() {
		cout << fname << " " << lname << " has been destructed\n";
	}//end destructor

protected:
	std::string fname, lname;
	int id;

}; //end class



//derived class - student
class student_c : public user_c {
public:
	void search(std::string) {
		cout << "Search called succesfully\n";
	} //end function
	void add(int) {
		cout << "add called succesfully\n";
	}//end function
	void drop(int) {
		cout << "drop called succesfully\n";
	}//end function
	void printSchedule() {
		cout << "Print Schedule called succesfully\n";
	}//end function
	//constructor/destructor
	student_c(std::string f, std::string l, int i) : user_c{ f, l, i } {
		cout << "Constructor called succesfully\n";
	}//end constructor
	~student_c() {
		cout << "destructed succesfully\n";
	}//end destructor

}; //end class


//derived class - instructor
class instructor_c : public user_c {
public:
	void searchCourse(std::string) {
		cout << "Search called succesfully\n";
	}//end function
	void printClass() {
		cout << "print called succesfully\n";
	}//end function
	void printSched() {
		cout << "schdule print called succesfully\n";
	}//end function
	//constructor/destructors
	instructor_c(std::string f, std::string l, int i) : user_c{ f, l, i } {
		cout << "contructor called succesfully\n";
	}
	~instructor_c() {
		cout << "destructed succesfully\n";
	}
}; //end class


//derived class - admin
class admin_c : public user_c {
public:
	void addCourse() {
		cout << "add course called succesfully\n";
	}//end function
	void removeCourse() {
		cout << "remove course called succesfully\n";
	}//end function
	void addUser() {
		cout << "add user called succesfully\n";
	}//end function
	void removeUser() {
		cout << "remove user called succesfully\n";
	}//end function
	void searchStu(std::string) {
		cout << "Search student called succesfully\n";
	}//end function
	void searchCourse(std::string) {
		cout << "Search course called succesfully\n";
	}//end function
	void printClass() {
		cout << "print class called succesfully\n";
	}//end function
	void printCourses() {
		cout << "print courses called succesfully\n";
	}//end function
	admin_c(std::string f, std::string l, int i) : user_c{ f, l, i } {
		cout << "construtor called succesfully\n";
	}//end constructor
	~admin_c() {
		cout << "destructed succesfully\n";
	}//end destructor

}; //end class


#endif
