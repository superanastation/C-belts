#include<map>
#include<string>
#include<iostream>
#include<vector>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		if (redmine.count(person) > 0)
			return redmine.at(person);
		else {
			map<TaskStatus, int> ret;
			return ret;
		}
	}
	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person) {
		//redmine.at(person).at(TaskStatus::NEW)++;
		if (redmine.count(person) > 0 && redmine.at(person).count(TaskStatus::NEW) > 0) {
			redmine.at(person).at(TaskStatus::NEW)++;
		}
		else
			redmine[person].insert({ TaskStatus::NEW, 1 });
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const string& person, int task_count) {
		map<TaskStatus, int> newby;
		map<TaskStatus, int> old;
		if (redmine.count(person) > 0) {

			old = redmine.at(person);
			old.erase(TaskStatus::DONE);
			//--- все необходимые задачи в НОВЫХ
			if (redmine.at(person).count(TaskStatus::NEW) > 0 && redmine.at(person).at(TaskStatus::NEW) > task_count) {
				old[TaskStatus::NEW] -= task_count;
				newby[TaskStatus::IN_PROGRESS] = task_count;

				task_count = 0;
			}
			//---  не все необходимые задачи в НОВЫХ, надо сделать больше задач чем их в новых
			else if (redmine.at(person).count(TaskStatus::NEW) > 0) {
				old.erase(TaskStatus::NEW);
				newby[TaskStatus::IN_PROGRESS] = redmine.at(person).at(TaskStatus::NEW);

				task_count -= redmine.at(person).at(TaskStatus::NEW);
			}
			//--- есть ещё задачи, которые необходимо выполнить
			if (task_count != 0) {
				//--- все необходимые задачи в IN_PROGRESS
				if (redmine.at(person).count(TaskStatus::IN_PROGRESS) > 0 && redmine.at(person).at(TaskStatus::IN_PROGRESS) > task_count) {
					old[TaskStatus::IN_PROGRESS] = redmine.at(person).at(TaskStatus::IN_PROGRESS) - task_count;
					newby[TaskStatus::TESTING] = task_count;

					task_count = 0;
				}
				else if (redmine.at(person).count(TaskStatus::IN_PROGRESS) > 0) {
					old.erase(TaskStatus::IN_PROGRESS);
					newby[TaskStatus::TESTING] = redmine.at(person).at(TaskStatus::IN_PROGRESS);

					task_count -= redmine.at(person).at(TaskStatus::IN_PROGRESS);
				}
				if (task_count != 0) {
					//--- все необходимые задачи в testing
					if (redmine.at(person).count(TaskStatus::TESTING) > 0 && redmine.at(person).at(TaskStatus::TESTING) > task_count) {
						old[TaskStatus::TESTING] = redmine.at(person).at(TaskStatus::TESTING) - task_count;
						newby[TaskStatus::DONE] = task_count;

						task_count = 0;
					}
					else if (redmine.at(person).count(TaskStatus::TESTING) > 0) {
						old.erase(TaskStatus::TESTING);
						newby[TaskStatus::DONE] = redmine.at(person).at(TaskStatus::TESTING);

						task_count -= redmine.at(person).at(TaskStatus::TESTING);
					}
				}
			}
			for (const auto& item : { TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING }) {
				int check = 0;
				if (newby.count(item) > 0)
					check = newby.at(item);
				if (old.count(item) > 0)
					check += old.at(item);
				if (redmine.at(person).count(item) == 0 && check != 0)
					redmine.at(person)[item] = check;
				else if (redmine.at(person).count(item) > 0 && check == 0)
					redmine.at(person).erase(item);
				else if (redmine.at(person).count(item) > 0 && check != 0)
					redmine.at(person).at(item) = check;
			}
			if (newby.count(TaskStatus::DONE))
				redmine.at(person)[TaskStatus::DONE] += newby.at(TaskStatus::DONE);
		}
		return make_tuple(newby, old);
	}

private:
	map<string, TasksInfo> redmine;
};
//void PrintTasksInfo(TasksInfo tasks_info) {
//	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
//		", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
//		", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
//		", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
//}
void PrintTasksInfo(const TasksInfo& tasks_info) {
	if (tasks_info.count(TaskStatus::NEW)) {
		std::cout << "NEW: " << tasks_info.at(TaskStatus::NEW) << " ";
	}
	if (tasks_info.count(TaskStatus::IN_PROGRESS)) {
		std::cout << "IN_PROGRESS: " << tasks_info.at(TaskStatus::IN_PROGRESS) << " ";
	}
	if (tasks_info.count(TaskStatus::TESTING)) {
		std::cout << "TESTING: " << tasks_info.at(TaskStatus::TESTING) << " ";
	}
	if (tasks_info.count(TaskStatus::DONE)) {
		std::cout << "DONE: " << tasks_info.at(TaskStatus::DONE) << " ";
	}
}

void PrintTasksInfo(const TasksInfo& updated_tasks, const TasksInfo& untouched_tasks) {
	std::cout << "Updated: [";
	PrintTasksInfo(updated_tasks);
	std::cout << "] ";

	std::cout << "Untouched: [";
	PrintTasksInfo(untouched_tasks);
	std::cout << "] ";

	std::cout << std::endl;
}

int main() {
	TeamTasks tasks;
	TasksInfo updated_tasks;
	TasksInfo untouched_tasks;

	/* TEST 1 */
	std::cout << "Alice" << std::endl;

	for (auto i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 5}, {}]

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 5);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"TESTING": 5}, {}]

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 1);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"DONE": 1}, {"TESTING": 4}]

	for (auto i = 0; i < 5; ++i) {
		tasks.AddNewTask("Alice");
	}
	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice",
		2);  // [{"IN_PROGRESS": 2}, {"NEW": 3, "TESTING": 4}]
	PrintTasksInfo(updated_tasks, untouched_tasks);

	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"NEW": 3, "IN_PROGRESS": 2, "TESTING": 4, "DONE": 1}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Alice", 4);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 3, "TESTING": 1}, {"IN_PROGRESS": 1, "TESTING": 4}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));  // {"IN_PROGRESS": 4, "TESTING": 5, "DONE": 1}
	std::cout << std::endl;

	/* TEST 2 */
	std::cout << "\nJack" << std::endl;

	tasks.AddNewTask("Jack");

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 1);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1}, {}]

	tasks.AddNewTask("Jack");

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 2);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1}, {}]

	tasks.AddNewTask("Jack");

	PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"NEW": 1, "IN_PROGRESS": 1, "TESTING": 1, "DONE": 0}
	std::cout << std::endl;

	tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Jack", 3);
	PrintTasksInfo(updated_tasks, untouched_tasks);  // [{"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}, {}]

	PrintTasksInfo(tasks.GetPersonTasksInfo("Jack"));  // {"IN_PROGRESS": 1, "TESTING": 1, "DONE": 1}
	std::cout << std::endl;

	return 0;
}
