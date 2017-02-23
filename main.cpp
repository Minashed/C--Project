#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "Profile.h"
#include "ARAIG_Sensors.h"
#include "Task.h"
#include "Exoskeleton.h"
#include "Stims.h"
#include "Stimulation.h"

int main(int argc, char** argv) {
	if (argc != 5) {
		std::cerr << "\n***Incorrect number of arguments***\n";
		return 1;
	}

	fp::usint input;
	bool continue_ = true;

	try {
		system("cls");
		fp::ARAIG_Sensors configuration(argv[1], argv[2]);
		std::ofstream output_file(argv[4], std::ofstream::out | std::ofstream::trunc);
		fp::Profile profile(argv[3], output_file, configuration);
		while (continue_)
		{
			system("cls");
			std::cout << "----------- ARAIG Control Menu -----------" << std::endl;
			std::cout << " 1 - Run Flight Plan" << std::endl;
			std::cout << " 2 - Generate Report" << std::endl;
			std::cout << " 3 - Exit" << std::endl;
			std::cout << "------------------------------------------" << std::endl;
			std::cout << " Choose an option: ";
			std::cin >> input;
			std::cout << std::endl;
			if (!std::cin.fail() && (input >= 0 && input <= 3)) {
				std::cin.ignore(50, '\n');
				switch (input) {
				case 1:
					system("cls");
					try {
						profile.run();
					}
					catch (const std::string& msg) {
						std::cerr << msg << std::endl;
					}
					std::cout << "\nPress any key to continue ... ";
					std::cin.get();
					break;
				case 2:
					system("cls");
					profile.generateReport();
					std::cout << "Report generated!" << std::endl;
					std::cout << "\nPress any key to continue ... ";
					std::cin.get();
					break;
				case 3:
					system("clear");
					continue_ = false;
					break;
				}
			}
		}
		output_file.close();
	}
	catch (const std::string& msg) {
		std::cerr << msg << std::endl;
	}
	return 0;
}
