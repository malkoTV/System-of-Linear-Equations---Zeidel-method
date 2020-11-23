#include<iostream>
#include<iomanip>
using namespace std;

#define E 0.0001 //precision
#define N 4
#define M 5
#define P 6 //number of digits

double** origin;

void table(double** arr, int n, int m, int precision);
void printRes(double* arr, int n);

//вектор нев'язки
void r(double** arr, double* res, int n, int m)
{
	cout << "Vector:\n";
	for(int i = 0; i < n; i++)
	{
		double v = 0;
		for(int j = 0; j < n; j++)
		{
			v += (origin[i][j] * res[j]);
		}
		v = origin[i][m - 1] - v;
		printf("r[%d] = %fl\n", i, v);
	}
	cout << endl;
} 

void printRes(double* arr, int n)
{
	cout << "\nResult:\n";
	for(int i = 0; i < n; i++)
	{
		printf("res[%d] = %lf\n", i, arr[i]);
	}
	cout << endl;
}

void line(int count)
{
	for (int i = 0; i < count; i++)
	{
		cout << "\xCD";
	}
}

void table(double** arr, int n, int m, int precision)
{
	cout << setprecision(precision);
	precision *= 2;
	cout << "\xC9";
	for (int i = 0; i < n; i++)
	{
		line(precision);
		cout << "\xCB";
		if (i == n - 1)
		{
			cout << "\xCB";
		}
	}
	line(precision);
	cout << "\xBB" << endl;

	for (int i = 0; i < n; i++)
	{
		cout << "\xBA";
		for (int j = 0; j < m; j++)
		{
			if (j == m - 2)
			{
				cout << setw(precision - 1) << arr[i][j] << " \xBA\xBA";
			}
			else
			{
				cout << setw(precision - 1) << arr[i][j] << " \xBA";
			}
		}
		cout << endl;

		if (i < (n - 1))
		{
			cout << "\xCC";
			for (int k = 0; k < n; k++)
			{
				line(precision);
				cout << "\xCE";
				if (k == n - 1)
				{
					cout << "\xCE";
				}
			}
			line(precision);
			cout << "\xB9" << endl;
		}
		else
		{
			cout << "\xC8";
			for (int k = 0; k < n; k++)
			{
				line(precision);
				cout << "\xCA";
				if (k == n - 1)
				{
					cout << "\xCA";
				}
			}
			line(precision);
			cout << "\xBC" << endl;
		}

	}
}

void init(double** arr, int n, int m, int num)
{
	int k = num - 11;
	double a = 0.2 * k;
	double b = 0.2 * k;

	arr[0][0] = 8.30;
	arr[0][1] = 2.62 + a;
	arr[0][2] = 4.10;
	arr[0][3] = 1.90;
	arr[0][4] = -10.65 + b;

	arr[1][0] = 3.92;
	arr[1][1] = 8.45;
	arr[1][2] = 8.78 - a;
	arr[1][3] = 2.46;
	arr[1][4] = 12.21;

	arr[2][0] = 3.77;
	arr[2][1] = 7.21 + a;
	arr[2][2] = 8.04;
	arr[2][3] = 2.28;
	arr[2][4] = 15.45 - b;

	arr[3][0] = 2.21;
	arr[3][1] = 3.65 - a;
	arr[3][2] = 1.69;
	arr[3][3] = 6.99;
	arr[3][4] = -8.35;
}

void initD(double** arr, int n, int m)
{
	arr[0][0] = 1;
	arr[0][1] = 0.17;
	arr[0][2] = 0.27;
	arr[0][3] = 0.18;
	arr[0][4] = -1.79;

	arr[1][0] = 0;
	arr[1][1] = 1;
	arr[1][2] = 0.67;
	arr[1][3] = 0.25;
	arr[1][4] = 0.99;

	arr[2][0] = 0;
	arr[2][1] = 0;
	arr[2][2] = 1;
	arr[2][3] = -0.17;
	arr[2][4] = 6.67;

	arr[3][0] = 0;
	arr[3][1] = 0;
	arr[3][2] = -0.18;
	arr[3][3] = 1;
	arr[3][4] = -1.74;
}

double** createArr(int n, int m)
{
	double** arr = new double* [n];
	for (int i = 0; i < n; i++)
	{
		*(arr + i) = new double[m];
	}
	return arr;
}

//ітерації
void iteration(double** arr, int n, int m, double* res, int& iter, double eps = E)
{
	if (iter <= 3)
	{
		cout << "Iteration " << iter << "\t";
		printRes(res, n);
		r(arr, res, n, m);
	}
	iter++;

	double* delta = new double[n];
	for (int i = 0; i < n; i++)
	{
		delta[i] = res[i];
	}
	
	for (int i = 0; i < n; i++)
	{
		res[i] = 0;
		for (int j = 0; j < n; j++)
		{
			if(j != i)
			{
				double temp = arr[i][j] * res[j];
				res[i] -= temp;
			}
		}
		res[i] += arr[i][m - 1];
	}

	double temp = 0;
	for (int i = 0; i < n; i++)
	{
		delta[i] = delta[i] - res[i];
		temp += pow(delta[i], 2);
	}

	if (sqrt(temp) <= eps)
	{
		cout << "Iteration " << iter << ": \t";
		printRes(res, n);
		r(arr, res, n, m);
		return;
	}
	else
	{
		iteration(arr, n, m, res, iter, eps);
	}
}

//перевірка на те чи є матриця з діагональною перевагою
bool diagonalDominating(double** a, int size)
{
	bool flag = true;

	for (int i = 0; i < size; i++) 
	{
		double sum = 0;
		
		for (int j = 0; j < size; j++) 
		{
			if (i != j) 
			{
				sum += abs(a[i][j]);
			}
		}
		
		if (abs(a[i][i]) < sum) 
		{
			flag = false;
			break;
		}
	}

	return flag;
}

//метод Зейделя
void zeidel(double** arr, int n, int m, double* res, double eps = E)
{
	cout << "Iteration law\n";
	table(arr, N, M, P);
	
	for(int i = 0; i < n; i++)
	{
		res[i] = arr[i][m - 1];
	}

	if(diagonalDominating(arr, n))
	{
		cout << "Diagonal dominating YES"<< endl;
	}
	else
	{
		cout << "Diagonal dominating NO" << endl;
	}
	
	int i = 1;	//ітерації
	iteration(arr, n, m, res, i, eps);
}

int main()
{
	double** arr = createArr(N, M);
	initD(arr, N, M);	
	
	//зберегли вихідну систему для обчислення вектора нев'язки
	origin = createArr(N, M);
	init(origin, N, M, 15);

	cout << "Original matrix" << endl;
	table(origin, N, M, P);
	cout << endl;

	double* solution = new double[N];
	zeidel(arr, N, M, solution);

	cout << endl << "System solution" << endl;
	printRes(solution, N);
	
	system("pause");
	return 0;
}