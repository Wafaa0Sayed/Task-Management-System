#ifndef TASKMANAGER_H
#define TASKMANAGER_H
#include <string.h>
#include "Priority Queue.h"
#include"Linked List.h"
#include <vector>
using namespace std;

class Task {
private:
    static int general_id;
    int id{};
    string title;
    string description;
    int priority{};
    string status;
    string date;

public:
    // Constructor
    Task();
    Task(string title, string desc, int prio, string status, string date);

    // Setters for Task
    void setDate(string newDate);
    void setTitle(string newTitle);
    void setPriority(int newPriority);
    void setId(int newId);
    void setDescription(const string &newDescription);
    void setStatus(const string &newStatus);

    // Getters for Task
    int getId() const;
    string getTitle() const;
    string getDescription() const;
    int getPriority() const;
    string getStatus() const;
    string getDate() const;
    int getYear();
    int getMonth();
    int getDay();

    bool operator==(const Task& other) const {
        return this->id == other.id;
    }

    void update(string newStatus, int newPriority, string newDescription);

    void showTask() const;
};
int Task::general_id = 1;
class User {
private:
    string name;
    int id;
    string email;
    PriorityQueue<Task> taskQueueByPriority;
    PriorityQueue<Task> taskQueueByDate;
    LinkedList<Task> taskList ;
    int siz ;

public:
    User(string name, int id, string email);

    static bool compareByDate(Task& t1, Task& t2) {
        if (t1.getYear() != t2.getYear())
            return t1.getYear() < t2.getYear();
        if (t1.getMonth() != t2.getMonth())
            return t1.getMonth() < t2.getMonth();
        return t1.getDay() < t2.getDay();
    }

    static bool compareByPriority( Task& t1, Task& t2) {
        return t1.getPriority() > t2.getPriority();
    }
    void addTask(const Task& task);
    void removeTaskById(int taskId);
    void updateTask(int taskId, const string& newDescription, int newPriority, const string& newStatus);

    void showTasksByDate() const;
    void showTasksByPriority() const;
    void showAllTasks() const;
};
#include "Task Manager.h"
#include <iostream>
#include <cstring>
using namespace std ;
// Task constructor
Task::Task(string title, string desc, int prio, string status, string date){
    this->id = general_id++ ;
    setTitle(title) ;
    setDescription(desc) ;
    setStatus(status) ;
    setDate(date) ;
    setId(id) ;
    setPriority(prio) ;
}

Task::Task()= default;

void Task::setDate(string newDate) {
    date = newDate ;
}

void Task::setTitle(string newTitle) {
    title = newTitle ;
}

void Task::setPriority(int newPriority) {
    priority = newPriority;
}

void Task::setId(int newId) {
    id = newId;
}

void Task::setDescription(const string &newDescription) {
    description = newDescription ;
}

void Task::setStatus(const string &newStatus) {
    status = newStatus ;
}

int Task::getYear() {
    return stoi(date.substr(0, 4));
}

int Task::getMonth() {
    return stoi(date.substr(5, 2));
}

int Task::getDay() {
    return stoi(date.substr(8, 2));
}


inline int Task::getId() const {
    return id;
}

string Task::getTitle() const {
    return title;
}

string Task::getDescription() const {
    return description;
}

int Task::getPriority() const {
    return priority;
}

string Task::getStatus() const {
    return status;
}

string Task::getDate() const {
    return date;
}

void Task::update(string newStatus, int newPriority, string newDescription) {
    if (newStatus != "") {
        setStatus(newStatus);
    }
    if (newPriority) {
        setPriority (newPriority);
    }
    if (newDescription != "") {
        setDescription(newDescription);
    }
}

void Task::showTask() const {
    cout<<"ID : "<<getId()<<endl;
    cout<<"Title : "<<getTitle()<<endl;
    cout<<"Description : "<<getDescription()<<endl;
    cout<<"Priority : "<<getPriority()<<endl;
    cout<<"Status : "<<getStatus()<<endl;
    cout<<"Date : "<<getDate()<<endl;
}

User::User(string name, int id, string email)
    : id(id), email(email),
      taskQueueByPriority(compareByPriority),
      taskQueueByDate(compareByDate) {
    this->name = name ;
    this->id = id ;
    this->email = email ;
}

void User::addTask(const Task& task) {
    taskQueueByDate.addItem(task) ;
    taskQueueByPriority.addItem(task);
    taskList.addItem(task);
}

void User::removeTaskById(int taskId) {
    auto* current = taskList.getHead();
    typename LinkedList<Task>::Node* prev = nullptr;
    Task taskToRemove;
    bool found = false;
    while (current) {
        if (current->data.getId() == taskId) {
            taskToRemove = current->data;
            if (prev) {
                prev->next = current->next;
            } else {
                taskList.setHead(current->next);
            }
            delete current;
            found = true;
            break;
        }
        prev = current;
        current = current->next;
    }
    if (!found) {
        cout<<"Task not found"<<endl;
        return ;
    }
    taskQueueByDate.removeItem(taskToRemove);
    taskQueueByPriority.removeItem(taskToRemove);
    cout << "Task with ID " << taskId << " removed successfully!" << endl;

}


inline void User::updateTask(int taskId, const string& newDescription, int newPriority, const string& newStatus) {
    int idx = -1;
    Task oldTask;

    auto* current = taskList.getHead();
    while (current != nullptr) {
        if (current->data.getId() == taskId) {
            oldTask = current->data;
            current->data.update(newStatus, newPriority, newDescription);
            idx = 1;
            break;
        }
        current = current->next;
    }

    if (idx == -1) {
        cout << "There is no task found" << endl;
        return;
    }

    taskQueueByDate.removeItem(oldTask);
    taskQueueByPriority.removeItem(oldTask);

    taskQueueByDate.addItem(current->data);
    taskQueueByPriority.addItem(current->data);

    cout << "Task with ID " << taskId << " updated successfully!" << endl;
}


inline void User::showTasksByDate() const {
    if (taskQueueByDate.isEmpty()) {
        cout << "No tasks available!" << endl;
        return;
    }

    cout << "==============================" << endl;
    cout << "   Tasks sorted by date " << endl;
    cout << "==============================" << endl;

    PriorityQueue<Task> tempQueue(taskQueueByDate);
    int counter = 1 ;
    while (!tempQueue.isEmpty()) {
        Task t = tempQueue.getTopItem();
        cout<<"***********"<<endl;
        cout<<"   Task "<<counter++<<endl;
        cout<<"***********"<<endl;
        t.showTask() ;
        cout << "----------------------" << endl;
        tempQueue.removeItem(t);
    }
    cout<<endl;
}
void User::showTasksByPriority() const {
    if (taskQueueByPriority.isEmpty()) {
        cout << "No tasks available!" << endl;
        return;
    }

    cout << "==============================" << endl;
    cout << "   Tasks sorted by priority" << endl;
    cout << "==============================" << endl;
    PriorityQueue<Task> tempQueue(taskQueueByPriority);

    int counter = 1 ;
    while (!tempQueue.isEmpty()) {
        Task t = tempQueue.getTopItem();
        cout<<"***********"<<endl;
        cout<<"   Task "<<counter++<<endl;
        cout<<"***********"<<endl;
        t.showTask() ;
        cout << "----------------------" << endl;
        tempQueue.removeItem(t);
    }
    cout<<endl;
}


void User::showAllTasks() const {
    cout << "======================" << endl;
    cout << "   User's Tasks" << endl;
    cout << "======================" << endl;
    auto* current = taskList.getHead();
    if (current == nullptr) {
        cout << "No tasks available!" << endl;
        return;
    }
    int counter = 1 ;
    while (current != nullptr) {
        cout<<"***********"<<endl;
        cout<<"   Task "<<counter++<<endl;
        cout<<"***********"<<endl;
        current->data.showTask();
        cout << "----------------------" << endl;
        current = current->next;
    }
    cout<<endl;
}


#endif // TASKMANAGER_H
