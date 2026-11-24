#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Specialnist { RI, IK, PZ };

struct Student
{
	string prizv;
	unsigned int kurs;
	Specialnist specialnist;
	unsigned int physics;
	unsigned int math;
	unsigned int informatics;
};

void Create(Student* students, const int N);
void Print(const Student* students, const int N);
int CountVidminno(const Student* students, const int N);
double PercentPhysic_5(const Student* students, const int N);

int main()
{
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);

	int N;
	cout << "Введіть кількість студентів: ";
	cin >> N;

	if (N <= 0)
	{
		cout << "Кількість студентів має бути більшою за 0." << endl;
		return 1;
	}

	Student* students = new Student[N];

	Create(students, N);
	Print(students, N);

	int vidminnyky = CountVidminno(students, N);
	double proc = PercentPhysic_5(students, N);

	cout << "Кількість студентів, які вчаться на «відмінно»: " << vidminnyky << endl;
	cout << "Процент студентів, які мають оцінку 5 з фізики: "
		<< fixed << setprecision(2) << proc << "%" << endl;

	delete[] students;
	return 0;
}

void Create(Student* students, const int N)
{
	int specInput;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент №" << i + 1 << ":" << endl;
		cin.ignore(10000, '\n');

		cout << "  прізвище: ";
		getline(cin, students[i].prizv);

		cout << "  курс: ";
		cin >> students[i].kurs;

		cout << "  спеціальність (0 - РІ, 1 - ІК, 2 - ПЗ): ";
		cin >> specInput;
		if (specInput < RI || specInput > PZ)
		{
			specInput = RI;
		}
		students[i].specialnist = static_cast<Specialnist>(specInput);

		cout << "  оцінка з фізики: ";
		cin >> students[i].physics;

		cout << "  оцінка з математики: ";
		cin >> students[i].math;

		cout << "  оцінка з інформатики: ";
		cin >> students[i].informatics;

		cout << endl;
	}
}

void Print(const Student* students, const int N)
{
	const string specialnistStr[] = { "РІ", "ІК", "ПЗ" };

	cout << "==================================================================================" << endl;
	cout << "| №   | прізвище      | курс | спеціальність | фізика | математика | інформатика |" << endl;
	cout << "----------------------------------------------------------------------------------" << endl;

	for (int i = 0; i < N; i++)
	{
		cout << "| " << setw(3) << right << i + 1 << " "
			<< "| " << setw(15) << left << students[i].prizv
			<< "| " << setw(4) << right << students[i].kurs << " "
			<< "| " << setw(15) << left << specialnistStr[students[i].specialnist] << " | "
			<< setw(6) << right << students[i].physics << " | "
			<< setw(10) << right << students[i].math << " | "
			<< setw(11) << right << students[i].informatics << " |"
			<< endl;
	}

	cout << "==================================================================================" << endl;
	cout << endl;
}

int CountVidminno(const Student* students, const int N)
{
	int count = 0;
	for (int i = 0; i < N; i++)
	{
		if (students[i].physics == 5 &&
			students[i].math == 5 &&
			students[i].informatics == 5)
		{
			count++;
		}
	}
	return count;
}

double PercentPhysic_5(const Student* students, const int N)
{
	if (N <= 0)
		return 0.0;

	int k = 0;
	for (int i = 0; i < N; i++)
	{
		if (students[i].physics == 5)
		{
			k++;
		}
	}
	return 100.0 * k / N;
}