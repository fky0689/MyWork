#include<iostream>
#include<iomanip>
using namespace std;

class Date {
public:
	/* Ĭ�Ϲ��캯������fullyear����ʽ���������գ�Ĭ��ֵΪ1990��1��1�գ�ͬʱ�������ڷָ���Ϊ��-�� */
	Date(int year = 1990, int month = 1, int day = 1);

	/* get��set���� */
	// �������ڣ�����зǷ����»��գ�������Ϊ1
	void setDate(int year, int month, int day);
	void setYear(int year);
	int getYear();
	void setMonth(int month);
	int getMonth();
	void setDay(int month);
	int getDay();
	void setSeparator(char separator);

	/* �����������ʹ��setfill(��0��)��setw(2)��*/
	void printFullYear();      //��YYYY-MM-DD����ʽ��ӡ��2011-01-08
	void printStandardYear(); //��YY-MM-DD����ʽ��ӡ������11-01-08
	/* ���㵱ǰ�������������֮���������꣬�����ǲ������ڱȵ�ǰ������������ע�����Ϊ���ڶ�������á�*/
	int fullYearsTo(Date& date);
	/* ���㵱ǰ�������������֮����������(��������)��������������ڵ�ǰ����֮ǰ�����ظ�����ע�����Ϊ���ڶ�������á�*/
	int daysTo(Date& date);
	/* �������������Ա�daysTo�������� */
	int getDayOfYear();  //���㵱ǰ�����Ǳ���ĵڼ���
	int getLeftDaysYear(); //���㵱ǰ���ھ౾��������м��죬��������ǰ��������
	int fullYearDays(int ayear);/*���������һ���������*/
private:
	int year;
	int month;
	int day;
	char separator;  // ���ڷָ���
	/* �������ݳ�Ա�ͺ�����Ա */
	/*������̬��������ÿ�µ���������.cpp�ļ��ж��岢��ʼ�� */
	static const int DAYS_PER_MONTH[12];
	/*��������£��жϲ��������Ƿ�Ϸ�������Ϸ�������day�����򷵻�-1��*/
	int checkDay(int day);
	bool isleapyear(int year);//�ϲ������Ƿ������ꡣ
};
const int Date::DAYS_PER_MONTH[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
class Employee {
public:
	//���캯����ʹ�á���ʼ���б���ʼ�����ݳ�Ա
	Employee(string, string, Date&, Date&);
	//��ӡԱ������Ϣ������Date���print��������ӡԱ�������պ͹�Ӷ���ڡ�
	void print();
	//����Ա���ڲ���ָ��������ʱ���������ꡣ��ʹ��Date���fullYearsTo����
	int getAge(Date& date);
	//�����Ա���ڲ���ָ��������ʱ���������˶����ꡣ
	int getYearsWorked(Date& date);
	//�����Ա���ڲ���ָ��������ʱ�������˶����졣ʹ��Date���daysTo������
	int getDaysWorked(Date& date);
	~Employee();   //��������
private:
	string firstName;
	string lastName;
	Date birthDate;    //��Ƕ���󣬳�������
	Date hireDate;     //��Ƕ���󣬹�������
};

void Date::setDate(int ayear, int amonth, int aday) {
	year = ayear;
	if (amonth > 12)	month = 1;
	else
		month = amonth;
	if (aday > 31)	day = 1;
	else
		day = aday;
}
void Date::setYear(int ayear) {
	year = ayear;
}
int Date::getYear() {
	return year;
}
void Date::setMonth(int amonth) {
	month = amonth;
}
int Date::getMonth() {
	return month;
}
void Date::setDay(int aday) {
	day = aday;
}
int Date::getDay() {
	return day;
}
void Date::setSeparator(char sep) {
	separator = sep;
}
// ��YYYY-MM-DD����ʽ��ӡ��2011-01-08
void Date::printStandardYear() {
	cout << year << separator;
	cout << setw(2) << setfill('0') << month << separator;
	cout << setw(2) << setfill('0') << day;
}
// ��YY-MM-DD����ʽ��ӡ������11-01-08
void Date::printStandardYear() {
	cout << setw(2) << setfill('0') << year % 100 << separator;
	cout << setw(2) << setfill('0') << month << separator;
	cout << setw(2) << setfill('0') << day;
}
// ���㵱ǰ�������������֮���������꣬�����ǲ������ڱȵ�ǰ����������
int Date::fullYearsTo(Date& date) {
	int result = 0;
	if (date.month > month)
		result = date.year - year;
	else if (date.month == month) {
		if (date.day >= day)
			result = date.year - year;
		else
			result = date.year - year - 1;
	}
	else
		result = date.year - year - 1;
	return result;
}
/*�ж��Ƿ�Ϊ����*/
bool Date::isleapyear(int ayear) {
	if ((ayear % 4 == 0 && ayear % 100 != 0) || ayear % 400 == 0)
		return true;
	else
		return false;
}
/*���������һ���������*/
int Date::fullYearDays(int ayear) {
	if (isleapyear(ayear))	return 366;
	else
		return 365;
}
/*���������һ���ڵ���������ǰ�ж�����*/
int Date::getDayOfYear() {
	int days = 0;
	switch (month) {
	case 12:days += 30;//11�µ�����
	case 11:days += 31;//10�µ�����
	case 10:days += 30;//9�µ�����
	case 9:days += 31;//8�µ�����
	case 8:days += 31;//7�µ�����
	case 7:days += 30;//6�µ�����
	case 6:days += 31;//5�µ�����
	case 5:days += 30;//4�µ�����
	case 4:days += 31;//3�µ�����
	case 3:days += 28;//2�µ�����
	case 2:days += 31;//1�µ�����
	}
	days += day;
	if (month >= 2 && isleapyear(year))
		days += 1;
	return days;
}
/*���������һ�쵽�������ʣ�¶�����*/
int Date::getLeftDaysYear() {
	return fullYearDays(year) - getDayOfYear();
}
/* ���㵱ǰ�������������֮����������(��������)��������������ڵ�ǰ����֮ǰ�����ظ����� */
int Date::daysTo(Date& date) {
	Date newdate(date.year, date.month, date.day);//�������ڸ�ֵ��newdate

	Date* startDate; // ��ʼ����
	Date* endDate; // ��������
	bool ascent = true; // ��ǰ���ڴ��ڲ������ڣ���Ϊ�档Ĭ��Ϊ�档

	// �����ͬһ����
	if (this->year == date.year) {
		return newdate.getDayOfYear() - this->getDayOfYear();
	}

	//��ʼ����ʼ�ͽ�������
	// ����ͬһ���У��ҵ�ǰ�������ڲ�������
	if (this->year > date.year) {
		startDate = &newdate;
		endDate = this;
	}
	// �����ǰ������
	else {
		startDate = this;
		endDate = &newdate;
		ascent = false;
	}

	// �ȼ��Ͽ�ʼ���ڵ��������������
	int offsetDays = startDate->getLeftDaysYear();

	// �ټ��Ͽ�ʼ���ںͽ�������֮�������������� ����������ֹ�꣩
	for (int i = startDate->year + 1; i < endDate->year; i++)
		offsetDays += fullYearDays(i);

	// �ټ��Ͻ�������ʱ�������Ѿ���������
	offsetDays += endDate->getDayOfYear();

	// ��������򣬷��ظ���
	if (ascent)
		return 0 - offsetDays;
	// ����ǽ���
	else
		return offsetDays;
}
/*��������£��жϲ��������Ƿ�Ϸ�������Ϸ�������day�����򷵻�-1��*/
int Date::checkDay(int day) {
	if (month == 1 | month == 3 | month == 5 | month == 7 | month == 8 | month == 10 | month == 12) {
		if (day < 32)	return day;
		else return -1;
	}
	else if (month == 2) {
		if (isleapyear) {
			if (day <= 29)	return day;
			else return -1;
		}
		else {
			if (day <= 28)	return day;
			else return -1;
		}
	}
}

//���캯����ʹ�á���ʼ���б���ʼ�����ݳ�Ա
Employee::Employee(string first_name, string last_name, Date& birth_date, Date& hire_date):birthDate(), hireDate(){
	firstName = first_name;
	lastName = last_name;
	birthDate = birth_date;
	hireDate = hire_date;
}
//��ӡԱ������Ϣ������Date���print��������ӡԱ�������պ͹�Ӷ���ڡ�
void Employee:: print() {
	cout << "BirthDate��" << printStandardYear(birth_date->year, birth_date->month, birth_date->day);
}


void main() {
	Date birth(1969, 8, 11);
	Date hire(1998, 4, 1);
	Date today(2010, 4, 30);
	Employee manager("Bob", "Blue", birth, hire);
	cout << endl;
	manager.print();
	cout << endl;
	cout << manager.getAge(today) << endl;
	cout << manager.getDaysWorked(today) << endl;
}
