#include "Stimulation.h"
#include "Stims.h"
#include "Exoskeleton.h"

namespace fp{
	//Two Constructors
	Stimulation::Stimulation(){
		type.clear();
	}

	Stimulation::Stimulation(const std::string& str){
		if (!str.empty()){
			type = str;
		}else{
			throw "The Stimulation type name has been corrupted in the file.";
		}
	}

	ostream& operator<<(std::ostream& os, const Stimulation& src){
		src.display(os);
		return os;
	}

	Stimulation* readFile(std::ifstream& in){
		if (in && in.is_open()){
			while (!in.eof()){
				std::string tmp;
				std::string t_; //hold type of object to create
				unsigned short inten;
				unsigned short dur_;

				std::getline(in, tmp, '\n');

				if (tmp[0] == 's' || tmp[0] == 'S'){
					std::string sName; //name of stim object -- ie. frontShoulder
					movement l_; //hold location type, will need convert() to turn string to enum
					unsigned short freq_;

					unsigned short pos1 = tmp.find(',', 0);
					t_ = tmp.substr(0, pos1);
					unsigned short pos2 = tmp.find(',', pos1);
					sName = tmp.substr(pos1, pos2);
					unsigned short pos3 = tmp.find(',', pos2);
					l_ = convert(tmp.substr(pos2, pos3)); //use convert function created to return an enum type
					unsigned short pos4 = tmp.find(',', pos3);
					inten = atoi(tmp.substr(pos3, pos4)); //use string to int to turn a parsed string into an integral number
					unsigned short pos5 = tmp.find(',', pos4);
					freq_ = atoi(tmp.substr(pos4, pos5));
					unsigned short pos6 = tmp.find('\n', pos5);
					dur_ = atoi(tmp.substr(pos5, pos6));


					return new Stims(t_, sName, l_, inten, freq_, dur_);
				}
				else if (tmp[0] == 'e' || tmp[0] == 'E')
				{
					std::string eName;

					pos1 = tmp.find(',', 0);
					t_ = tmp.substr(0, pos1);
					pos2 = tmp.find(',', pos1);
					eName = tmp.substr(pos1, pos2);
					pos3 = tmp.find(',', pos2);
					inten = atoi(tmp.substr(pos2, pos3));
					pos4 = tmp.find('\n', pos3);
					dur_ = atoi(tmp.substr(pos3, pos4));

					return new Exoskeleton(t_, eName, inten, dur_);
				}
				else
				{
					throw "The file has been corrupted";
					return nullptr;
				}
			}

			in.close();
		}
	}

	Type Stimulation::getType() const{
		return type;
	}

	enum Stimulation::convert(const std::string& str){
		if(str == "abs"){
			return abs;
		}else if (str == "front"){
			return front;
		}else if (str == "back"){
			return back;
		}else{
			return traps;
		}
	}

	Stims* clone() const  { return new Stims(*this); }

}