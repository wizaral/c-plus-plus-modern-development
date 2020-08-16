#include <iostream>
#include <map>
#include <string>
#include <tuple>
using std::cin, std::cout, std::endl;
using std::map, std::string, std::tuple;

enum class TaskStatus {
    NEW,
    IN_PROGRESS,
    TESTING,
    DONE,
};
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
    map<string, TasksInfo> data;

public:
    const TasksInfo &GetPersonTasksInfo(const string &person) const {
        return data.at(person);
    }
    void AddNewTask(const string &person) {
        ++data[person][TaskStatus::NEW];
    }

    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string &person, int task_count) {
        TasksInfo updated, untouched;
        TasksInfo &current = data[person];

        for (TaskStatus st = TaskStatus::NEW; st != TaskStatus::DONE; st = get_next(st)) {
            if (current[st] && task_count) {
                int min = std::min(current[st], task_count);
                updated[get_next(st)] += min;
                current[st] -= min;
                task_count -= min;
            }
        }

        for (TaskStatus st = TaskStatus::NEW; st != TaskStatus::DONE; st = get_next(st)) {
            if (current[st]) {
                untouched[st] = current[st];
            }
        }

        for (auto st : {TaskStatus::IN_PROGRESS, TaskStatus::TESTING, TaskStatus::DONE}) {
            if (updated.count(st)) {
                current[st] += updated[st];
            }
            if (current[st] == 0) {
                current.erase(st);
            }
        }

        if (current[TaskStatus::NEW] == 0) {
            current.erase(TaskStatus::NEW);
        }

        return std::make_tuple(updated, untouched);
    }

private:
    TaskStatus get_next(TaskStatus st) {
        return static_cast<TaskStatus>(static_cast<int>(st) + 1);
    }
};
