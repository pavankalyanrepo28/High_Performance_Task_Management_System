#include "task.h"
#include <sstream>
#include <iomanip>

Task::Task(int id, const std::string& title, const std::string& description)
    : id(id), title(title), description(description), completed(false),
      priority(Priority::MEDIUM) {}

int Task::getId() const {
    return id;
}

std::string Task::getTitle() const {
    return title;
}

std::string Task::getDescription() const {
    return description;
}

bool Task::isCompleted() const {
    return completed;
}

Priority Task::getPriority() const {
    return priority;
}

std::chrono::system_clock::time_point Task::getDueDate() const {
    return dueDate;
}

const std::vector<std::string>& Task::getTags() const {
    return tags;
}

void Task::setTitle(const std::string& newTitle) {
    title = newTitle;
}

void Task::setDescription(const std::string& newDescription) {
    description = newDescription;
}

void Task::setPriority(Priority newPriority) {
    priority = newPriority;
}

void Task::setDueDate(const std::chrono::system_clock::time_point& date) {
    dueDate = date;
}

void Task::addTag(const std::string& tag) {
    if (!hasTag(tag)) {
        tags.push_back(tag);
    }
}

void Task::removeTag(const std::string& tag) {
    tags.erase(
        std::remove(tags.begin(), tags.end(), tag),
        tags.end()
    );
}

bool Task::hasTag(const std::string& tag) const {
    return std::find(tags.begin(), tags.end(), tag) != tags.end();
}

void Task::toggleComplete() {
    completed = !completed;
}

bool Task::isOverdue() const {
    return !completed && dueDate < std::chrono::system_clock::now();
}

std::string Task::serialize() const {
    std::stringstream ss;
    auto tt = std::chrono::system_clock::to_time_t(dueDate);
    
    ss << id << "|"
       << title << "|"
       << description << "|"
       << (completed ? "1" : "0") << "|"
       << static_cast<int>(priority) << "|"
       << std::put_time(std::localtime(&tt), "%Y-%m-%d %H:%M:%S");
    
    for (const auto& tag : tags) {
        ss << "|" << tag;
    }
    
    return ss.str();
}

Task Task::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string item;
    std::vector<std::string> parts;
    
    while (std::getline(ss, item, '|')) {
        parts.push_back(item);
    }
    
    if (parts.size() < 6) {
        throw std::runtime_error("Invalid task data format");
    }
    
    Task task(std::stoi(parts[0]), parts[1], parts[2]);
    task.completed = (parts[3] == "1");
    task.priority = static_cast<Priority>(std::stoi(parts[4]));
    
    std::tm tm = {};
    std::stringstream ss_date(parts[5]);
    ss_date >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    task.dueDate = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    
    for (size_t i = 6; i < parts.size(); ++i) {
        task.addTag(parts[i]);
    }
    
    return task;
} 