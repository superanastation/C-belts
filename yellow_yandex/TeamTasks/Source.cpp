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
		return redmine.at(person);
	}
	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person) {
		redmine.at(person).at(TaskStatus::NEW)++;
		/*if (redmine.count(person) > 0 && redmine.at(person).count(TaskStatus::NEW) > 0) {
			redmine.at(person).at(TaskStatus::NEW)++;
		}
		else
			redmine[person].insert( { TaskStatus::NEW, 1 });*/
			//redmine.insert( person,{TaskStatus::NEW, 1} );
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(
		const string& person, int task_count) {
		int count_=0;
		for (const auto& item : GetPersonTasksInfo(person)) {
			count_ += item.second;
		}
		map<TaskStatus, int> newby;
		map<TaskStatus, int> old;
		//while (task_count > 0) {
		//	for (const auto& item : { TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING, TaskStatus::DONE }) {
		//		item + 1;
		//	}
		//}
		if (redmine.at(person).count(TaskStatus::NEW) > task_count) {
			redmine.at(person).at(TaskStatus::NEW) -= task_count;
			old = redmine.at(person);
			redmine.at(person)[TaskStatus::IN_PROGRESS] += task_count;//.at(TaskStatus::IN_PROGRESS)
			task_count = 0;
			newby[TaskStatus::IN_PROGRESS] = task_count;
		}
		else if(redmine.at(person).count(TaskStatus::NEW) > 0){
			int count_new = redmine.at(person).count(TaskStatus::NEW);
			redmine.at(person).erase(TaskStatus::NEW);
			redmine.at(person)[TaskStatus::IN_PROGRESS] += count_new;//.at(TaskStatus::IN_PROGRESS) 
			task_count -= count_new;
			newby[TaskStatus::IN_PROGRESS] = task_count;
		}
		if (task_count != 0) {
			if (redmine.at(person).count(TaskStatus::IN_PROGRESS) > task_count) {
				redmine.at(person).at(TaskStatus::IN_PROGRESS) -= task_count;
				redmine.at(person)[TaskStatus::TESTING] += task_count;//.at(TaskStatus::IN_PROGRESS)
				task_count = 0;
			}
			else if (redmine.at(person).count(TaskStatus::IN_PROGRESS) > 0) {
				int count_new = redmine.at(person).count(TaskStatus::IN_PROGRESS);
				redmine.at(person).erase(TaskStatus::IN_PROGRESS);
				redmine.at(person)[TaskStatus::TESTING] += count_new;//.at(TaskStatus::IN_PROGRESS) 
				task_count -= count_new;
			}
		}
		if (task_count != 0) {
			if (redmine.at(person).count(TaskStatus::TESTING) > task_count) {
				redmine.at(person).at(TaskStatus::TESTING) -= task_count;
				redmine.at(person)[TaskStatus::DONE] += task_count;//.at(TaskStatus::IN_PROGRESS)
				task_count = 0;
			}
			else if (redmine.at(person).count(TaskStatus::TESTING) > 0) {
				int count_new = redmine.at(person).count(TaskStatus::TESTING);
				redmine.at(person).erase(TaskStatus::TESTING);
				redmine.at(person)[TaskStatus::DONE] += count_new;//.at(TaskStatus::IN_PROGRESS) 
				task_count -= count_new;
			}
		}


		//	if (redmine.at(person).count(TaskStatus::NEW) <= task_count && redmine.at(person).count(TaskStatus::NEW)>0) {
		//		int count_new = redmine.at(person).count(TaskStatus::NEW);
		//		redmine.at(person).erase(TaskStatus::NEW);
		//		redmine.at(person).at(TaskStatus::IN_PROGRESS) += count_new;
		//		task_count -= count_new;
		//		if (task_count != 0) {

		//		}

		//}
	}

private:
	map<string, TasksInfo> redmine;
};

int main() {

	return 0;
}