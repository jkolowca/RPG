#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>

#define X	16
#define Y	5


int main() {
	char solid[X*Y];
	std::fill_n(solid, X*Y, 'n');

	std::ifstream config("config.csv");
	if (!config) return 0;
	int t;
	char comma;
	while (config >> t>>comma) solid[t] = 'y';
	
	config.close();

	int x, y;
	std::string filename;
	std::cout << "Podaj nazwe pliku: ";
	std::cin >> filename;
	std::cout << "Podaj wymiary mapy: ";
	std::cin >> x >> y;
	
	std::ofstream ofile(filename + ".txt");
	
	ofile << 3 << "x" << x << "x" << y << std::endl
		<< "1:1" << std::endl;

	for (unsigned int i = 1; i < 4; i++) {
		std::ifstream ifile(filename + "_Warstwa Kafelków " + std::to_string(i)+".csv");
		if (!ifile) {
			std::cout << filename + "_Warstwa Kafelków " + std::to_string(i) + ".csv" << std::endl;
			return 1;
		}
		for (unsigned int i = 0; i < y; i++) {
			for (unsigned int j = 0; j < x-1; j++) {
				ifile >> t >> comma;
				if (t == -1) ofile << "0:0,n\t";
				else ofile << t % X << ":" << t / X << "," << solid[t] << "\t";
			}
			ifile >> t;
			if (t == -1) ofile << "0:0,n";
			else ofile << t % X << ":" << t / X << "," << solid[t];
			ofile << std::endl;
		}
		ofile << std::endl;
		ifile.close();
	}
	ofile.close();

	return 1;
}