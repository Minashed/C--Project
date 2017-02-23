#ifndef H_ARAIG
#define H_ARAIG

#include <fstream>
#include <memory>
#include "Task.h"


namespace fp{

	class ARAIG_Sensors{

	private:
		Task* _task;
		Stimulation** _stims;
		usint tSize, sSize;

	public:
		ARAIG_Sensors(const char* stims_file, const char* task_file);
		void dump(std::ostream& ostr) const;
		Task& getTask(std::string& name);
		usint get_tasks_size() { return tSize; }
		~ARAIG_Sensors();

	};



}
#endif