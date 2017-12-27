#include<iostream>
#include<math.h>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;

void funkcjaA(vector< vector<double> >& A, vector<double>& B, int &n) {
	cout << "Podaj rozmiar macierzy n: ";
	cin >> n;
	
	vector< vector<double> > tempA(n + 1, vector<double>(n + 1));
	vector<double> tempB(n + 1);
	A = tempA;
	B = tempB;
	ifstream plik("zestaw1.txt", ios::in);

	for (int p = 1; p <= n; p++) {
		for (int r = 1; r <= n; r++)
			plik >> A[p][r];
	}

	for (int p = 1; p <= n; p++)
		plik >> B[p];

	plik.close();
}

bool funkcjaB(vector< vector<double> > A, vector< vector<double> >& L, vector< vector<double> >& U, int n) {
	if (A[1][1] == 0.0)  // U[1][1] bedzie rowne A[1][1], a pozniej bedziemy przez nie dzielic, wiec nie moze byc rowne 0.
		return false;
	
	vector< vector<double> > tempL(n + 1, vector<double>(n + 1, 0.0));  //  Tworzenie oraz zerowanie macierzy L i U
	vector< vector<double> > tempU(n + 1, vector<double>(n + 1, 0.0));
	double wynikSumy = 0.0;
	L = tempL;
	U = tempU;

	for (int i = 1; i <= n; i++)  //  Wypelnienie przekatnej macierzy L jedynkami
		L[i][i] = 1.0;

	for (int j = 1; j <= n; j++) {
		U[1][j] = A[1][j];
	}

	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j++) {
			wynikSumy = 0.0;
			for (int k = 1; k <= i - 1; k++)
				wynikSumy += L[i][k] * U[k][j];

			U[i][j] = A[i][j] - wynikSumy;
		}

		for (int j = i + 1; j <= n; j++) {
			if (U[i][i] == 0.0)  //  Blad dzielenia przez 0, brak sensu dalszego liczenia.
				return false;

			wynikSumy = 0.0;
			for (int k = 1; k <= i - 1; k++)
				wynikSumy += L[j][k] * U[k][i];

			L[j][i] = (A[j][i] - wynikSumy) / U[i][i];
		}
	}
	return true;
}

void funkcjaD(vector< vector<double> > A, vector<double> B, vector< vector<double> > L, vector< vector<double> > U, int n) {
	cout << " Macierz A:" << endl;
	for (int p = 1; p <= n; p++) {
		for (int r = 1; r <= n; r++) {
			cout << right << setw(8) << A[p][r];
		}
		cout << endl;
	}
	cout << " Wektor B:" << endl;
	for (int p = 1; p <= n; p++)
		cout << right << setw(8) << B[p] << endl;

	cout << " Macierz L: " << endl;
	for (int p = 1; p <= n; p++) {
		for (int r = 1; r <= n; r++) {
			cout << right << setw(8) << L[p][r];
		}
		cout << endl;
	}

	cout << " Macierz U: " << endl;
	for (int p = 1; p <= n; p++) {
		for (int r = 1; r <= n; r++) {
			cout << right << setw(8) << U[p][r];
		}
		cout << endl;
	}
}

int main() {
	vector< vector<double> > A, L, U;  //  Dwuwymiarowe tablice dla macierzy A, L oraz U.
	vector<double> B;  //  Jednowymiarowa tablica dla wektora B.
	int n;  //  rozmiar n macierzy A oraz wektora B.

	funkcjaA(A, B, n);
	bool dziel = funkcjaB(A, L, U, n);
	if (dziel)
		cout << "TAK";
	else
		cout << "NIE";
	funkcjaD(A, B, L, U, n);
	int x;
	cin >> x;

}