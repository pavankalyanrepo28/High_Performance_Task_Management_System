#include "task_manager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

TaskManager::TaskManager() : nextId(1) {}

void TaskManager::updateTagIndex(const Task& task) {
    for (const auto& tag : task.getTags()) {
        tagIndex[tag].push_back(task.getId());
    }
}

void TaskManager::removeFromTagIndex(const Task& task) {
    for (const auto& tag : task.getTags()) {
        auto& ids = tagIndex[tag];
        ids.erase(std::remove(ids.begin(), ids.end(), task.getId()), ids.end());
        if (ids.empty()) {
            tagIndex.erase(tag);
        }
    }
}

void TaskManager::addTask(const std::string& title, const std::string& description) {
    tasks.emplace_back(nextId++, title, description);
    std::cout << "Task added successfully!\n";
}

void TaskManager::removeTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                          [id](const Task& task) { return task.getId() == id; });
    
    if (it != tasks.end()) {
        removeFromTagIndex(*it);
        tasks.erase(it);
        std::cout << "Task removed successfully!\n";
    } else {
        std::cout << "Task not found!\n";
    }
}

void TaskManager::editTask(int id, const std::string& title, const std::string& description) {
    for (auto& task : tasks) {
        if (task.getId() == id) {
            task.setTitle(title);
            task.setDescription(description);
            std::cout << "Task updated successfully!\n";
            return;
        }
    }
    std::cout << "Task not found!\n";
}

void TaskManager::setPriority(int id, Priority priority) {
    for (auto& task : tasks) {
        if (task.getId() == id) {
            task.setPriority(priority);
            std::cout << "Priority updated successfully!\n";
            return;
        }
    }
    std::cout << "Task not found!\n";
}

void TaskManager::setDueDate(int id, const std::chrono::system_clock::time_point& date) {
    for (auto& task : tasks) {
        if (task.getId() == id) {
            task.setDueDate(date);
            std::cout << "Due date updated successfully!\n";
            return;
        }
    }
    std::cout << "Task not found!\n";
}

std::vector<Task> TaskManager::searchByTitle(const std::string& keyword) const {
    std::vector<Task> results;
    for (const auto& task : tasks) {
        if (task.getTitle().find(keyword) != std::string::npos) {
            results.push_back(task);
        }
    }
    return results;
}

std::vector<Task> TaskManager::searchByTag(const std::string& tag) const {
    std::vector<Task> results;
    auto it = tagIndex.find(tag);
    if (it != tagIndex.end()) {
        for (int id : it->second) {
            auto task_it = std::find_if(tasks.begin(), tasks.end(),
                                      [id](const Task& t) { return t.getId() == id; });
            if (task_it != tasks.end()) {
                results.push_back(*task_it);
            }
        }
    }
    return results;
}

void TaskManager::exportTasks(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file) {
        std::cout << "Error opening file for export!\n";
        return;
    }
    
    for (const auto& task : tasks) {
        file << task.serialize() << "\n";
    }
    std::cout << "Tasks exported successfully!\n";
}

void TaskManager::importTasks(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file for import!\n";
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        try {
            Task task = Task::deserialize(line);
            tasks.push_back(task);
            updateTagIndex(task);
            nextId = std::max(nextId, task.getId() + 1);
        } catch (const std::exception& e) {
            std::cout << "Error importing task: " << e.what() << "\n";
        }
    }
    std::cout << "Tasks imported successfully!\n";
}

void TaskManager::completeTask(int id) {
    for (auto& task : tasks) {
        if (task.getId() == id) {
            task.toggleComplete();
            std::cout << "Task status updated!\n";
            return;
        }
    }
    std::cout << "Task not found!\n";
}

void TaskManager::listTasks() const {
    if (tasks.empty()) {
        std::cout << "No tasks available!\n";
        return;
    }
    
    std::cout << "\nAll Tasks:\n";
    for (const auto& task : tasks) {
        std::cout << "ID: " << task.getId() 
                  << " | Title: " << task.getTitle()
                  << " | Status: " << (task.isCompleted() ? "Completed" : "Pending")
                  << "\n";
    }
}

void TaskManager::listCompletedTasks() const {
    bool found = false;
    std::cout << "\nCompleted Tasks:\n";
    
    for (const auto& task : tasks) {
        if (task.isCompleted()) {
            std::cout << "ID: " << task.getId() 
                      << " | Title: " << task.getTitle() << "\n";
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "No completed tasks!\n";
    }
}

void TaskManager::listPendingTasks() const {
    bool found = false;
    std::cout << "\nPending Tasks:\n";
    
    for (const auto& task : tasks) {
        if (!task.isCompleted()) {
            std::cout << "ID: " << task.getId() 
                      << " | Title: " << task.getTitle() << "\n";
            found = true;
        }
    }
    
    if (!found) {
        std::cout << "No pending tasks!\n";
    }
} 