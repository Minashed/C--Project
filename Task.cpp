#include "Task.h"

namespace fp{

	//Copy Constructor
	Task::Task(const Task& source){
		tName = source.tName;
		tasks = std::list<Stimulation*>(source.tasks);
	}

	//Copy Assignment Operator
	Task& Task::operator=(const Task& source){
		if (this != &source) {
			tName = source.tName;
			tasks = std::list<Stimulation*>(source.tasks);
		} else {
			tName.clear();
			tasks.clear();
		}
		return *this;
	}

	//Move Constructor
	Task::Task(Task&& source){
		tName = source.tName;
		tasks = std::list<Stimulation*>(source.tasks);
		source.tName.clear();
		source.tasks.clear();
	}

	//Move Assignment Operator
	Task&& Task::operator=(Task&& source){
		if (this != &source) {
			tName = source.tName;
			tasks = std::list<Stimulation*>(source.tasks);
			source.tName.clear();
			source.tasks.clear();
		} else {
			tName.clear();
			tasks.clear();
		}
		return std::move(*this);
	}

	//Member Functions
	Task& Task::operator+=(Stimulation* src){
		tasks.push_back(src);
		return *this;
	}

	Stimulation* Task::operator[](usint i){
		if (tasks.size() > i){
			std::list<Stimulation*>::iterator it = tasks.begin();
			std::advance(it, i);
			return *it;
		}else
			throw std::string("Stimulation requested is not it Task");
	}

	void Task::delStim(const std::string& name_){
		for (std::list<Stimulation*>::iterator it = tasks.begin(); it != tasks.end(); it++)
		{
			if ((*it)->getStim() == name_) {
				tasks.erase(it);
				break;
			}
		}
	}

	void Task::dump(std::ostream& os) const{
		os << "TASK - " << tName << std::endl;
		for (std::list<Stimulation*>::const_iterator i = tasks.begin(); i != tasks.end(); i++) {
			os << "       ";
			os << (*i)->getStim() << std::endl;
		}
	}

	void Task::execute(std::ostream& os) const{
		os << "TASK: " << tName << std::endl;
		for (std::list<Stimulation*>::const_iterator i = tasks.begin(); i != tasks.end(); i++) {
			(*i)->display(os);
		}
	}

	Task::~Task(){
		for (size_t x = 0; x < tasks.size(); x++) {
			tasks.front() = nullptr;
			tasks.pop_front();
		}
	}
}