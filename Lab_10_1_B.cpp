#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>

using namespace std;

enum Specialnist
{
	KN,  // Комп'ютерні науки -> програмування
	INF, // Інформатика -> чисельні методи
	ME,  // Математика та економіка -> педагогіка
	FI,  // Фізика та інформатика -> педагогіка
	TN   // Трудове навчання -> педагогіка
};

union ThirdGrade
{
	unsigned int programming;
	unsigned int numMethods;
	unsigned int pedagogy;
};

struct StudentB
{
	wstring prizv;
	unsigned int kurs;
	Specialnist specialnist;
	unsigned int physics;
	unsigned int math;
	ThirdGrade third;
};

wstring fitW(const wstring& s, size_t maxLen);
void Create(StudentB* students, const int N);
void Print(const StudentB* students, const int N);
unsigned int GetThirdGrade(const StudentB& st);
int CountVidminno(const StudentB* students, const int N);
double PercentPhysic_5(const StudentB* students, const int N);

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);

	int N;
	wcout << L"Введіть кількість студентів: ";
	wcin >> N;

	if (N <= 0)
	{
		wcout << L"Кількість студентів має бути більшою за 0." << endl;
		return 1;
	}

	StudentB* students = new StudentB[N];

	Create(students, N);
	Print(students, N);

	int vidminnyky = CountVidminno(students, N);
	double proc = PercentPhysic_5(students, N);

	wcout << L"Кількість студентів, які вчаться на «відмінно»: " << vidminnyky << endl;
	wcout << L"Процент студентів, які мають оцінку 5 з фізики: "
		<< fixed << setprecision(2) << proc << L"%" << endl;

	delete[] students;
	return 0;
}

wstring fitW(const wstring& s, size_t maxLen)
{
	if (s.size() <= maxLen)
	{
		return s;
	}
	if (maxLen >= 3)
	{
		return s.substr(0, maxLen - 3) + L"...";
	}
	return s.substr(0, maxLen);
}

unsigned int GetThirdGrade(const StudentB& st)
{
	switch (st.specialnist)
	{
	case KN:
		return st.third.programming;
	case INF:
		return st.third.numMethods;
	default:
		return st.third.pedagogy;
	}
}

void Create(StudentB* students, const int N)
{
	int specInput;
	unsigned int grade3;

	for (int i = 0; i < N; i++)
	{
		wcout << L"Студент №" << i + 1 << L":" << endl;
		wcin.ignore(10000, L'\n');

		wcout << L"  прізвище: ";
		getline(wcin, students[i].prizv);

		wcout << L"  курс: ";
		wcin >> students[i].kurs;

		wcout << L"  спеціальність (0 - КН, 1 - Інф, 2 - МЕ, 3 - ФІ, 4 - ТН): ";
		wcin >> specInput;
		if (specInput < KN || specInput > TN)
		{
			specInput = KN;
		}
		students[i].specialnist = static_cast<Specialnist>(specInput);

		wcout << L"  оцінка з фізики: ";
		wcin >> students[i].physics;

		wcout << L"  оцінка з математики: ";
		wcin >> students[i].math;

		switch (students[i].specialnist)
		{
		case KN:
			wcout << L"  оцінка з програмування: ";
			wcin >> grade3;
			students[i].third.programming = grade3;
			break;
		case INF:
			wcout << L"  оцінка з чисельних методів: ";
			wcin >> grade3;
			students[i].third.numMethods = grade3;
			break;
		default:
			wcout << L"  оцінка з педагогіки: ";
			wcin >> grade3;
			students[i].third.pedagogy = grade3;
			break;
		}

		wcout << endl;
	}
}

void Print(const StudentB* students, const int N)
{
	const wstring specialnistStr[] =
	{
		L"КН",
		L"Інформатика",
		L"Мат. та ек.",
		L"Фіз. та інф.",
		L"Труд. навч."
	};

	const int wNum = 3;
	const int wPrizv = 15;
	const int wKurs = 4;
	const int wSpec = 14;
	const int wPhys = 6;
	const int wMath = 10;
	const int wProg = 13;
	const int wNumM = 9;
	const int wPed = 10;

	auto printLine = [&](wchar_t ch)
		{
			wcout << L"+"
				<< wstring(wNum + 2, ch) << L"+"
				<< wstring(wPrizv + 2, ch) << L"+"
				<< wstring(wKurs + 2, ch) << L"+"
				<< wstring(wSpec + 2, ch) << L"+"
				<< wstring(wPhys + 2, ch) << L"+"
				<< wstring(wMath + 2, ch) << L"+"
				<< wstring(wProg + 2, ch) << L"+"
				<< wstring(wNumM + 2, ch) << L"+"
				<< wstring(wPed + 2, ch) << L"+\n";
		};

	printLine(L'=');
	wcout << L"| " << right << setw(wNum) << fitW(L"№", wNum)
		<< L" | " << left << setw(wPrizv) << fitW(L"прізвище", wPrizv)
		<< L" | " << right << setw(wKurs) << fitW(L"курс", wKurs)
		<< L" | " << left << setw(wSpec) << fitW(L"спеціальність", wSpec)
		<< L" | " << right << setw(wPhys) << fitW(L"фізика", wPhys)
		<< L" | " << right << setw(wMath) << fitW(L"математика", wMath)
		<< L" | " << right << setw(wProg) << fitW(L"програмування", wProg)
		<< L" | " << right << setw(wNumM) << fitW(L"чис. мет.", wNumM)
		<< L" | " << right << setw(wPed) << fitW(L"педагогіка", wPed)
		<< L" |\n";
	printLine(L'-');

	for (int i = 0; i < N; i++)
	{
		unsigned int g3 = GetThirdGrade(students[i]);
		wstring sProg = (students[i].specialnist == KN) ? to_wstring(g3) : L"";
		wstring sNumM = (students[i].specialnist == INF) ? to_wstring(g3) : L"";
		wstring sPed = (students[i].specialnist != KN && students[i].specialnist != INF) ? to_wstring(g3) : L"";

		wcout << L"| " << right << setw(wNum) << fitW(to_wstring(i + 1), wNum)
			<< L" | " << left << setw(wPrizv) << fitW(students[i].prizv, wPrizv)
			<< L" | " << right << setw(wKurs) << fitW(to_wstring(students[i].kurs), wKurs)
			<< L" | " << left << setw(wSpec) << fitW(specialnistStr[students[i].specialnist], wSpec)
			<< L" | " << right << setw(wPhys) << fitW(to_wstring(students[i].physics), wPhys)
			<< L" | " << right << setw(wMath) << fitW(to_wstring(students[i].math), wMath)
			<< L" | " << right << setw(wProg) << fitW(sProg, wProg)
			<< L" | " << right << setw(wNumM) << fitW(sNumM, wNumM)
			<< L" | " << right << setw(wPed) << fitW(sPed, wPed)
			<< L" |\n";
	}

	printLine(L'=');
	wcout << endl;
}

int CountVidminno(const StudentB* students, const int N)
{
	int count = 0;
	for (int i = 0; i < N; i++)
	{
		if (students[i].physics == 5 &&
			students[i].math == 5 &&
			GetThirdGrade(students[i]) == 5)
		{
			count++;
		}
	}
	return count;
}

double PercentPhysic_5(const StudentB* students, const int N)
{
	if (N <= 0)
	{
		return 0.0;
	}

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