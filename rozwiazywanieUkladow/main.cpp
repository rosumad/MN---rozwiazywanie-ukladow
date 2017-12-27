#include<iostream>
#include<math.h>
#include<vector>
#include<fstream>
using namespace std;

void funkcjaA(vector< vector<double> >& macierzA, vector<double>& wektorB, int &n) {
	cout << "Podaj rozmiar macierzy n: ";
	cin >> n;
	
	vector< vector<double> > tempMacierzA(n + 1, vector<double>(n + 1));
	vector<double> tempWektorB(n + 1);
	ifstream plik("zestawy/zestaw1.txt", ios::in);

	for (int p = 1; p <= n; p++) {
		for (int r = 1; r <= n; r++)
			plik >> tempMacierzA[p][r];
	}

	for (int p = 1; p <= n; p++)
		plik >> tempWektorB[p];

	plik.close();
	macierzA = tempMacierzA;
	wektorB = tempWektorB;
}

void funkcjaB(vector< vector<double> >& macierzL, vector< vector<double> >& macierzU) {
	
}

int main() {
	vector< vector<double> > macierzA;
	vector<double> wektorB;
	int n;

	funkcjaA(macierzA, wektorB, n);



	for (int p = 1; p <= n; p++)
	{
		for (int r = 1; r <= n; r++)
			cout << macierzA[p][r] << " ";

		cout << endl;
	}

	for (int p = 1; p <= n; p++)
		cout << wektorB[p] << " ";

	int x;
	cin >> x;

}