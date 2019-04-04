#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

unsigned int n, MLI;
	double epsilon;
	double**A, *B, **alfa, *beta;

void wypisz(double** macierz, double* wektor){
	for (unsigned int i = 0; i < n; i++){
		for (unsigned int j = 0; j < n; j++){
			cout << macierz[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
	for (unsigned int i = 0; i < n; i++){
		cout<<wektor[i]<<"\t";
	}
	cout << "\n\n\n";
}
void wczytaj(){
	n = 5;
	epsilon = 0.0001;
	MLI = 30;


	A = new double*[n];
	for (int i = 0; i < n; i++){
		A[i] = new double[n];
	}
	B = new double[n];



	ifstream file;
	file.open("input.txt");
	if (!file) return;


	for (unsigned int i = 0; i < n; i++){
		for (unsigned int j = 0; j < n; j++){
			file >> A[i][j];
		}
	}
	for (unsigned int i = 0; i < n; i++){
		file >> B[i];
	}
	return;
}
void generuj_raport();


int stworz_alfa_beta(){
	alfa = new double*[n];
	for (unsigned int i = 0; i < n; i++){
		alfa[i] = new double[n];
	}
	beta = new double[n];

	for (unsigned int i = 0; i < n; i++){
		if (A[i][i] == 0){
			cout << "dzielenie przez 0" << endl;
			return 0;
		}
		for (unsigned int j = 0; j < n; j++){
			if (i == j) alfa[i][j] = 0;
			else {
				alfa[i][j] = -A[i][j] / A[i][i];
			}
		}
		beta[i] = B[i] / A[i][i];
	}
}

void rozwiaz_uklad(){
	unsigned int lit = 0;
	double* Xstary, *Xnowy;
	Xstary = new double[n];
	Xnowy = new double[n];

	for (unsigned int i = 0; i < n; i++){
		Xnowy[i] = beta[i];
	}
	double norma;
	do{
		for (unsigned int i = 0; i < n; i++){
			Xstary[i] = Xnowy[i];
		}

		lit++;
		double suma;

		//obliczenie kolejnej iteracji X
		for (unsigned int i = 0; i < n; i++){
			suma = 0;
			for (unsigned int j = 0; j < n; j++){
				suma += alfa[i][j] * Xstary[j];
			}
			Xnowy[i] = suma + beta[i];
		}
		//obliczenie normy
		double temp;
		norma = 0;
		for (unsigned int i = 0; i < n; i++){
			temp = abs(Xnowy[i] - Xstary[i]);
			if (temp>norma) norma = temp;
		}

	} while (lit < MLI && norma >= epsilon);
	cout << "wynik:\n";
	for (unsigned int i = 0; i < n; i++){
		cout << Xstary[i] << "\t";
	}
	cout << endl;
	cout << "liczba iteracji:" << lit;
}


int main()
{
	
	wczytaj();
	wypisz(A,B);
	if (!stworz_alfa_beta()) {
		system("pause");
		return 1;
	}
	wypisz(alfa, beta);
	rozwiaz_uklad();

	system("pause");
	return 0;
}