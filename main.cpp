#include "Task Manager.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    string userName, userEmail;
    int userId;

    cout << "Enter your name: \n";
    getline(cin, userName);
    cout << "Enter your ID: \n";
    cin >> userId;
    cin.ignore();
    cout << "Enter your email: \n";
    getline(cin, userEmail);

    User user(userName, userId, userEmail);

    int choice;

    while (true) {
        cout << "\n1. Add Task\n"
             << "2. Show Tasks by Priority\n"
             << "3. Show Tasks by Date\n"
             << "4. Show All Tasks\n"
             << "5. Update Task\n"
             << "6. Delete Task\n"
             << "7. Exit\n";
        cout << "Enter your choice: \n";
        cin >> choice;
        cin.ignore();
        if (choice == 1) {
            string title, description, status, date;
            int priority;
            cout << "Enter Task Title :   \n";
            getline(cin, title);
            cout << "Enter Task Description :   \n";
            getline(cin, description);
            cout << "Enter Task Priority (1-5) :   \n";
            cin >> priority;
            cin.ignore();
            cout << "Enter Task Status :   \n";
            getline(cin, status);
            cout << "Enter Task Date (YYYY-MM-DD) :   \n";
            getline(cin, date);

            Task task(title, description, priority, status, date);
            user.addTask(task);
        }
        else if (choice == 2) {
            user.showTasksByPriority();
        }
        else if (choice == 3) {
            user.showTasksByDate();
        }
        else if (choice == 4) {
            user.showAllTasks();
        }
        else if (choice == 5) {
            int taskId, newPriority = 0;
            string newDescription, newStatus;

            cout << "Enter Task ID to update: \n";
            cin >> taskId;
            cin.ignore();

            int choice2;
            while (true) {
                cout << "\n1. Update Description\n"
                     << "2. Update Priority\n"
                     << "3. Update Status\n"
                     << "4. Exit\n";
                cout << "Enter your choice: \n";
                cin >> choice2;
                cin.ignore();

                if (choice2 == 1) {
                    cout << "Enter new Description :   \n";
                    getline(cin, newDescription);
                }
                else if (choice2 == 2) {
                    cout << "Enter new Priority (1-5) :   \n";
                    cin >> newPriority;
                    cin.ignore();
                }
                else if (choice2 == 3) {
                    cout << "Enter new Status :   \n";
                    getline(cin, newStatus);
                }
                else if (choice2 == 4) {
                    cout << "Exiting program..." << endl;
                    break;
                }
                else {
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
            user.updateTask(taskId, newDescription, newPriority, newStatus);
        }
        else if (choice == 6) {
            int taskId ;
            cout << "Enter Task ID to remove: ";
            cin >> taskId;
            cin.ignore();
            user.removeTaskById(taskId) ;
        }
        else if (choice == 7) {
            cout << "Exiting program..." << endl;
            break;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
