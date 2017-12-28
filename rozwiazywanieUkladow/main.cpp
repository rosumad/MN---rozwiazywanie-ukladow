#include<iostream>
#include<math.h>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;

void funkcjaA(vector< vector<double> >& A, vector<double>& B, 
	int &n) {
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

bool funkcjaB(vector< vector<double> > A, vector< vector<double> >& L, 
	vector< vector<double> >& U, int n) {
	if (A[1][1] == 0.0) { // U[1][1] bedzie rowne A[1][1], a pozniej bedziemy przez nie dzielic, wiec nie moze byc rowne 0.
		cout << " Wartosc A[1][1] jest rowna 0, przerywam liczenie" << endl;
		return false;
	}
	
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
			if (U[i][i] == 0.0) {  //  Blad dzielenia przez 0.
				cout << " Wartosc U[" << i << "][" << i << "] jest rowna 0, przerywam liczenie" << endl;
				return false;
			}

			wynikSumy = 0.0;
			for (int k = 1; k <= i - 1; k++)
				wynikSumy += L[j][k] * U[k][i];

			L[j][i] = (A[j][i] - wynikSumy) / U[i][i];
		}
	}
	return true;
}

bool funkcjaC(vector<double> B, vector< vector<double> > L, 
	vector< vector<double> > U, vector<double>& X, 
	vector<double>& Y, int n) {
	vector<double> tempX(n + 1, 0.0);
	vector<double> tempY(n + 1, 0.0);
	double wynikSumy = 0.0;
	X = tempX;
	Y = tempY;

	Y[1] = B[1];
	for (int i = 2; i <= n; i++) {
		wynikSumy = 0.0;
		for (int k = 1; k <= i - 1; k++)
			wynikSumy += L[i][k] * Y[k];

		Y[i] = B[i] - wynikSumy;
	}

	if (U[n][n] == 0.0) {  //  Ten przypadek nie moze sie zdarzyc, bo w funkcji B sprawdzalismy juz czy U[n][n] nie jest rowne 0.
		cout << " Wartosc U[" << n << "][" << n << "] jest rowna 0, przerywam liczenie" << endl;
		return false;
	}
	X[n] = Y[n] / U[n][n];
	for (int i = n - 1; i >= 1; i--) {
		if (U[i][i] == 0.0) {  //  Ten przypadek nie moze sie zdarzyc, bo w funkcji B sprawdzalismy juz czy U[i][i] nie jest rowne 0.
			cout << " Wartosc U[" << i << "][" << i << "] jest rowna 0, przerywam liczenie" << endl;
			return false;
		}
		wynikSumy = 0.0;
		for (int k = i + 1; k <= n; k++)
			wynikSumy = U[i][k] * X[k];

		X[i] = (Y[i] - wynikSumy) / U[i][i];
	}

	return true;
}

void funkcjaD(vector< vector<double> > A, vector<double> B, 
	vector< vector<double> > L, vector< vector<double> > U, 
	vector<double> X, vector<double> Y, 
	int n) {
	cout << " Macierz A:" << endl;
	for (int p = 1; p <= n; p++) {
		for (int r = 1; r <= n; r++) {
			cout << right << setw(12) << A[p][r];
		}
		cout << endl;
	}
	cout << " Wektor B:" << endl;
	for (int p = 1; p <= n; p++)
		cout << right << setw(8) << B[p] << endl;

	cout << " Macierz L: " << endl;
	for (int p = 1; p <= n; p++) {
		for (int r = 1; r <= n; r++) {
			cout << right << setw(12) << L[p][r];
		}
		cout << endl;
	}

	cout << " Macierz U: " << endl;
	for (int p = 1; p <= n; p++) {
		for (int r = 1; r <= n; r++) {
			cout << right << setw(12) << U[p][r];
		}
		cout << endl;
	}

	cout << " Wektor Y:" << endl;
	for (int p = 1; p <= n; p++)
		cout << right << setw(8) << Y[p] << endl;

	cout << " Wektor X:" << endl;
	for (int p = 1; p <= n; p++)
		cout << right << setw(8) << X[p] << endl;
}

int main() {
	vector< vector<double> > A, L, U;  //  Dwuwymiarowe tablice dla macierzy A, L oraz U.
	vector<double> B, X, Y;  //  Jednowymiarowa tablica dla wektorow B, X oraz Y.
	int n;  //  rozmiar n macierzy A oraz wektora B.

	funkcjaA(A, B, n);
	bool dziel = funkcjaB(A, L, U, n);
	if (!dziel) 
		return 0;

	dziel = funkcjaC(B, L, U, X, Y, n);
	if (!dziel) 
		return 0;

	funkcjaD(A, B, L, U, X, Y, n);

	char x; cin >> x;
	return 1;
}