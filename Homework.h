#include <string>
using namespace std;
class Homework{
public:
	Homework();
	Homework(Date dDate, Date aDate, string Descrip, string Stat);
	Date getDueDate();
	Date getAssignedDate();
	Date getCompletedDate();
	string getDescription();
	string getStatus();
	void setDueDate(Date date);
	void setAssignedDate(Date date);
	void setDescription(string description);
	void setStatus(string status);
	bool operator ==(Homework HW) const;
	bool isLate();
private:
	string  Description, Status;
	Date dueDate, assignedDate, completedDate;
};

Homework::Homework(){
	dueDate = dueDate;
	assignedDate = assignedDate;
	Description = "";
	Status = "";
	completedDate = completedDate.parseDate("2100/01/01", Standard);
}

Homework::Homework(Date dDate, Date aDate, string Descrip = "", string Stat = ""){
	dueDate = dDate;
	assignedDate = aDate;
	Description = Descrip;
	Status = Stat;
	completedDate = completedDate.parseDate("2100/01/01", Standard);
}

bool Homework::isLate()
{
	return completedDate > dueDate;
}

Date Homework::getDueDate(){
	return dueDate;
}

Date Homework::getAssignedDate(){
	return assignedDate;
}

Date Homework::getCompletedDate()
{
	return completedDate;
}

string Homework::getDescription(){
	return Description;
}

string Homework::getStatus(){
	return Status;
}

void Homework::setDueDate(Date date){
	dueDate = date;

}

void Homework::setAssignedDate(Date date){
	assignedDate = date;
}

void Homework::setDescription(string description){
	Description = description;
}

void Homework::setStatus(string status){
	Status = status;
}

bool Homework::operator==(Homework HW) const{
	return Description == HW.getDescription() && Status == HW.getStatus() && dueDate == HW.getDueDate() && assignedDate == HW.getAssignedDate();
}

