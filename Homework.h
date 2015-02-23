#include <string>
using namespace std;
class Homework{
public:
	Homework(string dDate, string aDate, string Descrip, string Stat);
	string getDueDate();
	string getAssignedDate();
	string getDescription();
	string getStatus();
	void setDueDate(string date);
	void setAssignedDate(string date);
	void setDescription(string description);
	void setStatus(string status);
private:
	string Description, Status; 
	Date dueDate, assignedDate;
};

Homework::Homework(string dDate = "", string aDate = "", string Descrip = "", string Stat = ""){
	dueDate = dueDate.parseDate(dDate, DateFormat::Standard);
	assignedDate = assignedDate.parseDate(aDate, DateFormat::Standard);
	assignedDate = aDate;
	Description = Descrip;
	Status = Stat;
}

string Homework::getDueDate(){
	return dueDate;
}

string Homework::getAssignedDate(){
	return assignedDate;
}

string Homework::getDescription(){
	return Description;
}

string Homework::getStatus(){
	return Status;
}

void Homework::setDueDate(string date){
	dueDate = date;
}

void Homework::setAssignedDate(string date){
	assignedDate = date;
}

void Homework::setDescription(string description){
	Description = description;
}

void Homework::setStatus(string status){
	Status = status;
}

