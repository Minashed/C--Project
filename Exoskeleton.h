#ifndef H_EXOSKELETON
#define H_EXOSKELETON

#include "Stimulation.h"

namespace fp{

	class Exoskeleton : public Stimulation{
	private:
		std::string exoName;
		unsigned short intensity;
		unsigned short duration;
	public:
		//Constructor
		Exoskeleton(std::string& name, usint intsty, usint secs);

		std::string getStim() const { return exoName; }

		//Pure Virtual function
		void display(ostream&) const;
	};


}

#endif H_EXOSKELETON
