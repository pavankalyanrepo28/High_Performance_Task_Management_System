#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <vector>
#include <string>
#include <map>
#include "task.h"

class TaskManager {
private:
    std::vector<Task> tasks;
    std::map<std::string, std::vector<int>> tagIndex;
    int nextId;
    
    void updateTagIndex(const Task& task);
    void removeFromTagIndex(const Task& task);

public:
    TaskManager();
    
    // Task management
    void addTask(const std::string& title, const std::string& description);
    void removeTask(int id);
    void completeTask(int id);
    void editTask(int id, const std::string& title, const std::string& description);
    void setPriority(int id, Priority priority);
    void setDueDate(int id, const std::chrono::system_clock::time_point& date);
    void addTagToTask(int id, const std::string& tag);
    void removeTagFromTask(int id, const std::string& tag);
    
    // Task queries
    std::vector<Task> searchByTitle(const std::string& keyword) const;
    std::vector<Task> searchByTag(const std::string& tag) const;
    std::vector<Task> getOverdueTasks() const;
    std::vector<Task> getTasksByPriority(Priority priority) const;
    
    // List operations
    void listTasks() const;
    void listCompletedTasks() const;
    void listPendingTasks() const;
    void listTasksByPriority() const;
    void listOverdueTasks() const;
    
    // Import/Export
    void exportTasks(const std::string& filename) const;
    void importTasks(const std::string& filename);
};

#endif // TASK_MANAGER_H 