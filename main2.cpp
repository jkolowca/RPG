#include <iostream>
#include <array>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

unsigned int n, MLI;
double epsilon;
double**A, *B, **alfa, *beta;

unsigned int lit;
double* Xstary, *Xnowy;

void wczytaj(unsigned int n, double epsilon,unsigned int MLI) {
	
	//implementacja dynamicznej tablicy
	A = new double*[n];
	for (int i = 0; i < n; i++) {
		A[i] = new double[n];
	}
	B = new double[n];



	ifstream file;
	file.open("Zestaw1.txt");
	if (!file) return;

	//wczytanie wartosci macierzy A z pliku
	for (unsigned int i = 0; i < n; i++) {
		for (unsigned int j = 0; j < n; j++) {
			file >> A[i][j];
		}
	} 
	//wczytanie waroœci macierzy B z pliku
	for (unsigned int i = 0; i < n; i++) {
		file >> B[i];
	}
	return;
}




int stworz_alfa_beta() {
	alfa = new double*[n];
	for (unsigned int i = 0; i < n; i++) {
		alfa[i] = new double[n];
	}
	beta = new double[n];

	for (unsigned int i = 0; i < n; i++) {
		if (A[i][i] == 0) {
			cout << "dzielenie przez 0" << endl;
			return 0;
		}
		for (unsigned int j = 0; j < n; j++) {
			if (i == j) alfa[i][j] = 0;
			else {
				alfa[i][j] = -A[i][j] / A[i][i];
			}
		}
		beta[i] = B[i] / A[i][i];
	}
}

void rozwiaz_uklad() {
	lit = 0;
	Xstary = new double[n];
	Xnowy = new double[n];

	for (unsigned int i = 0; i < n; i++) {
		Xnowy[i] = beta[i];
	}
	double norma;
	while (lit < MLI && norma >= epsilon)
	{
		for (unsigned int i = 0; i < n; i++) {
			Xstary[i] = Xnowy[i];
		}

		lit++;
		double suma;

		//obliczenie kolejnej iteracji X
		for (unsigned int i = 0; i < n; i++) {
			suma = 0;
			for (unsigned int j = 0; j < n; j++) {
				suma += alfa[i][j] * Xstary[j];
			}
			Xnowy[i] = suma + beta[i];
		}
		//obliczenie normy
		double temp;
		norma = 0;
		for (unsigned int i = 0; i < n; i++) {
			temp = abs(Xnowy[i] - Xstary[i]);
			if (temp > norma) norma = temp;
		}

	} 
	cout << "wynik:\n";
	for (unsigned int i = 0; i < n; i++) {
		cout << Xstary[i] << "\t";
	}
	cout << endl;
	cout << "liczba iteracji:" << lit;
}

//d
void generuj_raport()
{

	ofstream file2;
	file2.open("Raport1.txt");
	if (!file2) return;

	file2 << "Macierz A: " << endl;
	for (unsigned int i = 0; i < n; i++) {
		for (unsigned int j = 0; j < n; j++) {
			file2 << A[i][j] << "\t";
		}
		file2 << endl;
	}
	file2 << endl;
	file2 << "Wektor B: " << endl;
	for (unsigned int i = 0; i < n; i++) {
		file2 << B[i] << "\t";
	}
	file2 << "\n\n\n";

	file2 << "Dok³adnoœæ epsilon wynosi: " << epsilon << endl;
	file2 << "Maksymalna liczba iteracji wynosi: " << MLI << endl<<endl;

	file2 << "Macierz alfa:" << endl;
	for (unsigned int i = 0; i < n; i++) {
		for (unsigned int j = 0; j < n; j++) {
			file2 << alfa[i][j] << "\t";
		}
		file2 << endl;
	}
	file2 << endl;
	file2 << "Wektor beta" << endl;
	for (unsigned int i = 0; i < n; i++) {
		file2 << beta[i] << "\t";
	}
	file2 << "\n\n\n";

	file2 << "Wektor ostatnio wykonanej iteracji: " << endl;
	for (unsigned int i = 0; i < n; i++) {
		file2 << Xnowy[i] << "\t";
	}
	file2 << "\n\n\n";

	file2 << "Wektor przedostatnio wykonanej iteracji: " << endl;
	for (unsigned int i = 0; i < n; i++) {
		file2 << Xstary[i] << "\t";
	}
	file2 << "\n\n\n";
	file2 << "liczba iteracji wynios³a: " << lit << endl;
}
int main()
{
	cout << "podaj rozmiar macierzy A i wektorow B i X" << endl;
	cin >> n;
	cout << "podaj dokladnosc epsilon i maksymaln¹ liczbe iteracji" << endl;
	cin >> epsilon;
	cin>>MLI;

	wczytaj(n, epsilon,  MLI);

	if (!stworz_alfa_beta()) {
		system("pause");
		return 1;
	}
	rozwiaz_uklad();
	generuj_raport();

	system("pause");
	return 0;
}





//void wypisz(double** macierz, double* wektor) {
//	for (unsigned int i = 0; i < n; i++) {
//		for (unsigned int j = 0; j < n; j++) {
//			cout << macierz[i][j] << "\t";
//		}
//		cout << endl;
//	}
//	cout << endl;
//	for (unsigned int i = 0; i < n; i++) {
//		cout << wektor[i] << "\t";
//	}
//	cout << "\n\n\n";
//}