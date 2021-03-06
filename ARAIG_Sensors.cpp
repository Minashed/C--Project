#include "ARAIG_Sensors.h"

namespace fp{

	ARAIG_Sensors::ARAIG_Sensors(const char* stims_file, const char* task_file)
	{
		std::string tmp_line, _name, type, _intensity;
		unsigned short _count = 0, tot_lines = 0;
		size_t pos;
		std::ifstream s_file(stims_file, std::ios::in);
		std::ifstream t_file(task_file, std::ios::in);

		if (s_file.is_open()) {
			std::string loc, _frequency;
			movement _location;

			while (!s_file.eof())
			{
				std::getline(s_file, tmp_line);
				_count++;
			}
			_count--;

			_stims = new Stimulation*[_count];
			sSize = _count;
			s_file.clear();
			s_file.seekg(0, s_file.beg);
			_count = 0;

			while ((std::getline(s_file, tmp_line))) {
				pos = tmp_line.find(",");
				type = tmp_line.substr(0, pos);
				if (type == "stim") {
					pos++;
					tmp_line.erase(0, pos++);
					pos = tmp_line.find(",");
					_name = tmp_line.substr(0, pos);
					pos++;
					tmp_line.erase(0, pos++);
					pos = tmp_line.find(",");
					loc = tmp_line.substr(0, pos++);
					tmp_line.erase(0, pos++);
					if (loc == "abs") _location = abs;
					else if (loc == "front") _location = front;
					else if (loc == "back") _location = back;
					else if (loc == "traps") _location = traps;
					else throw std::string("Invalid stim location! Re-configure configuration file!");
					pos = tmp_line.find(",");
					_intensity = tmp_line.substr(0, pos);
					pos++;
					tmp_line.erase(0, pos++);
					pos = tmp_line.find(",");
					_frequency = tmp_line.substr(0, pos);
					pos++;
					tmp_line.erase(0, pos++);
					_stims[_count++] = new Stims(_name, _location, stoi(_intensity), stoi(_frequency), stoi(tmp_line));
				}
				else if (type == "exoskeleton") {
					pos++;
					tmp_line.erase(0, pos++);
					pos = tmp_line.find(",");
					_name = tmp_line.substr(0, pos);
					pos++;
					tmp_line.erase(0, pos++);
					pos = tmp_line.find(",");
					_intensity = tmp_line.substr(0, pos);
					pos++;
					tmp_line.erase(0, pos++);
					pos = tmp_line.find(",");
					_stims[_count++] = new Exoskeleton(_name, stoi(_intensity), stoi(tmp_line));
				}
				else
					throw std::string("Cannot create an object that is not a stim or exoskeleton!");
			}
			s_file.close();
		}
		else {
			throw std::string("Unable to open the Stimulations configuration file");
		}

		if (t_file.is_open()) {
			_count = 0;

			while (std::getline(t_file, tmp_line))
			{
				if (tmp_line.find("TASK") != std::string::npos)
					_count++;
			}

			_task = new Task[_count];
			tSize = _count;
			t_file.clear();
			t_file.seekg(0, t_file.beg);

			_count = 0;

			while (std::getline(t_file, tmp_line))
			{
				pos = tmp_line.find(",");
				if (pos != std::string::npos) {
					pos++;
					tmp_line.erase(0, pos);
					_task[_count++] = Task(tmp_line);
				}
				else {
					tmp_line = tmp_line.substr(0, (tmp_line.length() - 1));
					for (short int i = 0; i < sSize; i++)
					{
						if (_stims[i]->getStim() == tmp_line)
						{
							_task[_count - 1] += _stims[i];
							break;
						}
					}
				}
			}
			t_file.close();
		}
		else {
			throw std::string("Unable to open the Tasks configuration file");
		}
	}

	void ARAIG_Sensors::dump(std::ostream& ostr) const
	{
		for (unsigned short i = 0; i < sSize; i++)
		{
			_stims[i]->display(ostr);
		}
	}

	Task& ARAIG_Sensors::getTask(std::string& name)
	{
		for (unsigned short i = 0; i < tSize; i++)
		{
			if (_task[i].get_name() == name) {
				return _task[i];
				break;
			}
		}
		throw std::string("Task not found!");
	}

	ARAIG_Sensors::~ARAIG_Sensors()
	{
		delete[] _task;
		_task = nullptr;
		delete[] _stims;
		_stims = nullptr;
	}

}