#ifndef H_STIMS
#define H_STIMS

#include "Stimulation.h"

namespace fp{
	class Stims : public Stimulation{
	private:
		std::string stimName;
		movement location;
		unsigned short  intensity;
		unsigned short  frequency;
		unsigned short  duration;
	public:
		//Constructor
		Stims();
		Stims(std::string& name, movement area, usint intsty, usint frqncy, usint secs);
		~Stims(){};
		//Pure Virtual Functions
		void display(ostream&)const;
		std::string getStim() const { return stimName; }
	};

}

#endif