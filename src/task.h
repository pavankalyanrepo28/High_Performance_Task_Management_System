#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>
#include <chrono>

enum class Priority {
    LOW,
    MEDIUM,
    HIGH,
    URGENT
};

class Task {
private:
    int id;
    std::string title;
    std::string description;
    bool completed;
    Priority priority;
    std::chrono::system_clock::time_point dueDate;
    std::vector<std::string> tags;

public:
    Task(int id, const std::string& title, const std::string& description);
    
    // Getters
    int getId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    bool isCompleted() const;
    Priority getPriority() const;
    std::chrono::system_clock::time_point getDueDate() const;
    const std::vector<std::string>& getTags() const;
    
    // Setters
    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void setPriority(Priority priority);
    void setDueDate(const std::chrono::system_clock::time_point& date);
    
    // Tag operations
    void addTag(const std::string& tag);
    void removeTag(const std::string& tag);
    bool hasTag(const std::string& tag) const;
    
    void toggleComplete();
    bool isOverdue() const;
    
    // Serialization
    std::string serialize() const;
    static Task deserialize(const std::string& data);
};

#endif // TASK_H 