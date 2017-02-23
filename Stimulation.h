#ifndef H_STIMULATION
#define	H_STIMULATION
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

namespace fp{
	enum movement { abs, front, back, traps }; // May need to change the name
	typedef unsigned short usint;
	
	class Stimulation{
	private:
		//Name of defined stimulation
		std::string type;
	
	protected:
		Stimulation(const std::string& input) { type = input; }

	public:
		virtual void display(ostream&) const = 0;

		virtual std::string getStim() const = 0;
		
		std::string getType() const;  
	};

Stimulation* readFile(ifstream&);

ostream& operator<<(ostream&, const Stimulation&);

}


#endif