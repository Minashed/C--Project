#ifndef TASK_H
#define TASK_H

#include "Stims.h"
#include "Exoskeleton.h"

#include <list>
#include <iterator>

namespace fp{

	class Task{


	private:
		std::string tName;
		std::list<Stimulation*> tasks;
	public:
		Task() { tName.clear(); tasks.clear(); }

		Task(std::string& name) { tName = name; tasks.clear(); }
		
		Task(const Task&);
		Task& operator=(const Task&);
		
		Task(Task&&);
		Task&& operator=(Task&&);

		Task& operator+=(Stimulation* );

		std::string get_name() { return tName; }

		Stimulation* operator[](unsigned short);

		void delStim(const std::string&);

		void dump(std::ostream& ostr) const;

		void execute(std::ostream&) const;

		~Task();
	};
}


#endif