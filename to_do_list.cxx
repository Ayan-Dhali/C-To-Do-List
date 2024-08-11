#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

class Task {
public:
    Task(const string& description, bool completed = false)
        : description(description), completed(completed), createdAt(time(0)) {}

    string getDescription() const { return description; }
    bool isCompleted() const { return completed; }
    time_t getCreatedAt() const { return createdAt; }

    void setDescription(const string& desc) { description = desc; }
    void markCompleted() { completed = true; }
    void markIncomplete() { completed = false; }

    string toString() const {
        char buffer[26];
        // Convert time_t to a string representation
        string createdAtStr = ctime(&createdAt);
        createdAtStr.pop_back(); // Remove newline character added by ctime
        string status = completed ? "[Completed]" : "[Pending]";
        return status + " " + description + " (Created on: " + createdAtStr + ")";
    }

private:
    string description;
    bool completed;
    time_t createdAt;
};

class ToDoList {
public:
    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    void markTaskCompleted(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].markCompleted();
        } else {
            cout << "Invalid index!" << endl;
        }
    }

    void markTaskIncomplete(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].markIncomplete();
        } else {
            cout << "Invalid index!" << endl;
        }
    }

    void deleteTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        } else {
            cout << "Invalid index!" << endl;
        }
    }

    void listTasks() const {
        if (tasks.empty()) {
            cout << "No tasks available!" << endl;
            return;
        }

        for (int i = 0; i < tasks.size(); ++i) {
            cout << i + 1 << ". " << tasks[i].toString() << endl;
        }
    }

    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (!file) {
            cout << "Unable to open file for writing!" << endl;
            return;
        }

        for (const auto& task : tasks) {
            file << task.getDescription() << "," << (task.isCompleted() ? "1" : "0") << endl;
        }

        file.close();
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Unable to open file for reading!" << endl;
            return;
        }

        tasks.clear();
        string line;
        while (getline(file, line)) {
            size_t pos = line.find(',');
            if (pos != string::npos) {
                string description = line.substr(0, pos);
                bool completed = (line.substr(pos + 1) == "1");
                tasks.emplace_back(description, completed);
            }
        }

        file.close();
    }

private:
    vector<Task> tasks;
};

int main() {
    ToDoList todoList;
    todoList.loadFromFile("tasks.txt");

    int choice;
    do {
        cout << "\nTo-Do List Menu\n";
        cout << "1. Add Task\n";
        cout << "2. Mark Task Completed\n";
        cout << "3. Mark Task Incomplete\n";
        cout << "4. Delete Task\n";
        cout << "5. List Tasks\n";
        cout << "6. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string description;
                cout << "Enter task description: ";
                getline(cin, description);
                todoList.addTask(Task(description));
                break;
            }
            case 2: {
                int index;
                todoList.listTasks();
                cout << "Enter task number to mark as completed: ";
                cin >> index;
                cin.ignore();
                todoList.markTaskCompleted(index - 1);
                break;
            }
            case 3: {
                int index;
                todoList.listTasks();
                cout << "Enter task number to mark as incomplete: ";
                cin >> index;
                cin.ignore();
                todoList.markTaskIncomplete(index - 1);
                break;
            }
            case 4: {
                int index;
                todoList.listTasks();
                cout << "Enter task number to delete: ";
                cin >> index;
                cin.ignore();
                todoList.deleteTask(index - 1);
                break;
            }
            case 5:
                todoList.listTasks();
                break;
            case 6:
                todoList.saveToFile("tasks.txt");
                cout << "Tasks saved successfully!" << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
    } while (choice != 6);

    return 0;
}