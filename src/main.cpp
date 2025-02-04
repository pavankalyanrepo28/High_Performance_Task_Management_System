#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include "task_manager.h"

void displayTitle() {
    std::cout << "\n"
              << "+---------------------------------------------------+\n"
              << "|                    TASK COMMANDER                  |\n"
              << "|                    --------------                  |\n"
              << "|                                                   |\n"
              << "| System Info:                                      |\n"
              << "| > Build Version : 1.0.0-beta                     |\n"
              << "| > Architecture  : C++11/STL                      |\n"
              << "| > Compiler      : GCC/G++                        |\n"
              << "| > Platform      : Linux/Unix/Windows             |\n"
              << "|                                                   |\n"
              << "| Technical Stack: Native C/C++ Implementation      |\n"
              << "+---------------------------------------------------+\n\n";
}

void printMenu() {
    displayTitle();  // Add title before menu
    std::cout << "\n=== Main Menu ===\n"
              << "1. Add Task\n"
              << "2. Edit Task\n"
              << "3. Remove Task\n"
              << "4. Complete Task\n"
              << "5. Set Priority\n"
              << "6. Set Due Date\n"
              << "7. Add Tag\n"
              << "8. Remove Tag\n"
              << "9. List All Tasks\n"
              << "10. List by Priority\n"
              << "11. List Overdue Tasks\n"
              << "12. Search Tasks\n"
              << "13. Export Tasks\n"
              << "14. Import Tasks\n"
              << "0. Exit\n"
              << "Enter your choice: ";
}

std::chrono::system_clock::time_point inputDate() {
    std::tm tm = {};
    std::cout << "Enter date (YYYY-MM-DD HH:MM): ";
    std::string date_str;
    std::getline(std::cin, date_str);
    std::stringstream ss(date_str);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");
    return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

Priority inputPriority() {
    std::cout << "Select priority:\n"
              << "1. Low\n"
              << "2. Medium\n"
              << "3. High\n"
              << "4. Urgent\n"
              << "Choice: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    
    switch (choice) {
        case 1: return Priority::LOW;
        case 2: return Priority::MEDIUM;
        case 3: return Priority::HIGH;
        case 4: return Priority::URGENT;
        default: return Priority::MEDIUM;
    }
}

int main() {
    TaskManager manager;
    int choice;
    
    while (true) {
        printMenu();
        std::cin >> choice;
        std::cin.ignore();
        
        if (choice == 0) break;
        
        try {
            switch (choice) {
                case 1: {
                    std::string title, description;
                    std::cout << "Enter task title: ";
                    std::getline(std::cin, title);
                    std::cout << "Enter task description: ";
                    std::getline(std::cin, description);
                    manager.addTask(title, description);
                    break;
                }
                case 2: {
                    int id;
                    std::string title, description;
                    std::cout << "Enter task ID to edit: ";
                    std::cin >> id;
                    std::cin.ignore();
                    std::cout << "Enter new title: ";
                    std::getline(std::cin, title);
                    std::cout << "Enter new description: ";
                    std::getline(std::cin, description);
                    manager.editTask(id, title, description);
                    break;
                }
                case 3: {
                    int id;
                    std::cout << "Enter task ID to remove: ";
                    std::cin >> id;
                    manager.removeTask(id);
                    break;
                }
                case 4: {
                    int id;
                    std::cout << "Enter task ID to mark as complete: ";
                    std::cin >> id;
                    manager.completeTask(id);
                    break;
                }
                case 5: {
                    int id;
                    Priority priority = inputPriority();
                    manager.setPriority(id, priority);
                    break;
                }
                case 6: {
                    int id;
                    std::chrono::system_clock::time_point date = inputDate();
                    manager.setDueDate(id, date);
                    break;
                }
                case 7: {
                    int id;
                    std::string tag;
                    std::cout << "Enter task ID: ";
                    std::cin >> id;
                    std::cin.ignore();
                    std::cout << "Enter tag: ";
                    std::getline(std::cin, tag);
                    manager.addTagToTask(id, tag);
                    break;
                }
                case 8: {
                    int id;
                    std::string tag;
                    std::cout << "Enter task ID: ";
                    std::cin >> id;
                    std::cin.ignore();
                    std::cout << "Enter tag to remove: ";
                    std::getline(std::cin, tag);
                    manager.removeTagFromTask(id, tag);
                    break;
                }
                case 9:
                    manager.listTasks();
                    break;
                case 10:
                    manager.listTasksByPriority();
                    break;
                case 11:
                    manager.listOverdueTasks();
                    break;
                case 12: {
                    std::string keyword;
                    std::cout << "Enter keyword to search: ";
                    std::getline(std::cin, keyword);
                    manager.searchTasks(keyword);
                    break;
                }
                case 13: {
                    std::string filename;
                    std::cout << "Enter export filename: ";
                    std::getline(std::cin, filename);
                    manager.exportTasks(filename);
                    break;
                }
                case 14: {
                    std::string filename;
                    std::cout << "Enter import filename: ";
                    std::getline(std::cin, filename);
                    manager.importTasks(filename);
                    break;
                }
                default:
                    std::cout << "Invalid choice! Please try again.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }
    
    std::cout << "Thank you for using Task Manager!\n";
    return 0;
} 