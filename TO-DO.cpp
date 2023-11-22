#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Task {
    string description;
    bool completed;

    Task(string desc) : description(desc), completed(false) {}
};

void addTask(vector<Task>& tasks, const string& description);
void viewTasks(const vector<Task>& tasks);
void markCompleted(vector<Task>& tasks, const string& description);
void removeTask(vector<Task>& tasks, const string& description);

int main() {
    vector<Task> tasks;
    char choice;

    do {
        cout << "\n--- To-Do List Manager ---\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Mark Task as Completed\n";
        cout << "4. Remove Task\n";
        cout << "5. Exit\n";
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case '1':
                {
                    string taskDescription;
                    cout << "Enter task description: ";
                    cin.ignore();
                    getline(cin, taskDescription);
                    addTask(tasks, taskDescription);
                    break;
                }
            case '2':
                viewTasks(tasks);
                break;
            case '3':
                {
                    string taskDescription;
                    cout << "Enter task description to mark as completed: ";
                    cin.ignore();
                    getline(cin, taskDescription);
                    markCompleted(tasks, taskDescription);
                    break;
                }
            case '4':
                {
                    string taskDescription;
                    cout << "Enter task description to remove: ";
                    cin.ignore();
                    getline(cin, taskDescription);
                    removeTask(tasks, taskDescription);
                    break;
                }
            case '5':
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }

    } while (choice != '5');

    return 0;
}

void addTask(vector<Task>& tasks, const string& description) {
    tasks.push_back(Task(description));
    cout << "Task added: " << description << endl;
}

void viewTasks(const vector<Task>& tasks) {
    if (tasks.empty()) {
        cout << "No tasks to display.\n";
    } else {
        cout << "\n--- Task List ---\n";
        for (const Task& task : tasks) {
            cout << "- " << (task.completed ? "[X]" : "[ ]") << " " << task.description << endl;
        }
    }
}

void markCompleted(vector<Task>& tasks, const string& description) {
    auto it = find_if(tasks.begin(), tasks.end(),
                      [&description](const Task& task) {
                          return task.description == description;
                      });

    if (it != tasks.end()) {
        it->completed = true;
        cout << "Task marked as completed: " << description << endl;
    } else {
        cout << "Task not found.\n";
    }
}

void removeTask(vector<Task>& tasks, const string& description) {
    auto it = find_if(tasks.begin(), tasks.end(),
                      [&description](const Task& task) {
                          return task.description == description;
                      });

    if (it != tasks.end()) {
        tasks.erase(it);
        cout << "Task removed: " << description << endl;
    } else {
        cout << "Task not found.\n";
    }
}
