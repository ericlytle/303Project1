#include <string>
using namespace std;
class Homework{
public:
	Homework(Date dDate, Date aDate, string Descrip, string Stat);
	Date getDueDate();
	Date getAssignedDate();
	string getDescription();
	string getStatus();
	void setDueDate(string date);
	void setAssignedDate(string date);
	void setDescription(string description);
	void setStatus(string status);
private:
	string  Description, Status;
	Date dueDate, assignedDate;
};

Homework::Homework(Date dDate, Date aDate, string Descrip = "", string Stat = ""){
	dueDate = dDate;
	assignedDate = aDate;
	Description = Descrip;
	Status = Stat;
}

Date Homework::getDueDate(){
	return dueDate;
}

Date Homework::getAssignedDate(){
	return assignedDate;
}

string Homework::getDescription(){
	return Description;
}

string Homework::getStatus(){
	return Status;
}

void Homework::setDueDate(string date){
	dueDate = dueDate.parseDate(date, Standard);
}

void Homework::setAssignedDate(string date){
	assignedDate = assignedDate.parseDate(date, Standard);
}

void Homework::setDescription(string description){
	Description = description;
}

void Homework::setStatus(string status){
	Status = status;
}

