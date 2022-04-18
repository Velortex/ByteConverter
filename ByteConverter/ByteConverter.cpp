// ByteConverter.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>


int main(int argument_count, char** argument_array)
{

	if (argument_count < 1)
		return -1;

	if (std::filesystem::exists(argument_array[1]) == false)
	{
		printf("[-] file [%s] does not exist", argument_array[1]);
		return -1;
	}

	std::string inputName = argument_array[1];
	std::size_t found = inputName.find(".");

	std::string outputString = inputName.substr(0, found);
	outputString.append(".bin");

	std::ifstream file_buffer_str(argument_array[1], std::ios::binary);
	std::vector<std::uint8_t>file_buffer(std::istreambuf_iterator<char>(file_buffer_str), {});

	std::ofstream myfile;
	myfile.open(outputString);

	int test = 1;

	for (size_t i = 0; i < file_buffer.size(); i++)
	{
		std::stringstream ss;
		ss << std::hex;
		ss << std::setw(2) << std::setfill('0') << (int)file_buffer.data()[i];

		char finalstr[2] = "";

		for (int i = 0; i < 2; i++) {

			// convert str[i] to uppercase
			finalstr[i] = toupper(ss.str().at(i));
		}

		myfile << "0x";
		myfile << finalstr;

		if (test == 16) {
			myfile << ",";
			myfile << "\n";
			test = 1;
		}
		else
		{
			if (i < file_buffer.size() - 1)
				myfile << ", ";
			test++;
		}
	}
	myfile.close();

}
