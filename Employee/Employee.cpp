#include<iostream>
#include<iomanip>
using namespace std;

class Date {
public:
	/* 默认构造函数，以fullyear的形式给出年月日，默认值为1990年1月1日，同时设置日期分隔符为“-” */
	Date(int year = 1990, int month = 1, int day = 1);

	/* get、set方法 */
	// 设置日期，如果有非法的月或日，将其置为1
	void setDate(int year, int month, int day);
	void setYear(int year);
	int getYear();
	void setMonth(int month);
	int getMonth();
	void setDay(int month);
	int getDay();
	void setSeparator(char separator);

	/* 输出函数，请使用setfill(‘0’)和setw(2)。*/
	void printFullYear();      //以YYYY-MM-DD的形式打印，2011-01-08
	void printStandardYear(); //以YY-MM-DD的形式打印，比如11-01-08
	/* 计算当前日期与参数日期之间相差几个整年，仅考虑参数日期比当前日期晚的情况。注意参数为日期对象的引用。*/
	int fullYearsTo(Date& date);
	/* 计算当前日期与参数日期之间相差多少天(考虑闰年)，如果参数日期在当前日期之前，返回负数。注意参数为日期对象的引用。*/
	int daysTo(Date& date);
	/* 新增函数，可以被daysTo函数调用 */
	int getDayOfYear();  //计算当前日期是本年的第几天
	int getLeftDaysYear(); //计算当前日期距本年结束还有几天，不包括当前日期这天
	int fullYearDays(int ayear);/*计算参数这一年的总天数*/
private:
	int year;
	int month;
	int day;
	char separator;  // 日期分隔符
	/* 新增数据成员和函数成员 */
	/*声明静态常变量，每月的天数，在.cpp文件中定义并初始化 */
	static const int DAYS_PER_MONTH[12];
	/*根据年和月，判断参数日期是否合法。如果合法，返回day，否则返回-1。*/
	int checkDay(int day);
	bool isleapyear(int year);//断参数年是否是闰年。
};
const int Date::DAYS_PER_MONTH[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
class Employee {
public:
	//构造函数，使用“初始化列表”初始化数据成员
	Employee(string, string, Date&, Date&);
	//打印员工的信息。调用Date类的print函数，打印员工的生日和雇佣日期。
	void print();
	//计算员工在参数指定的日期时，满多少岁。请使用Date类的fullYearsTo函数
	int getAge(Date& date);
	//计算该员工在参数指定的日期时，工作满了多少年。
	int getYearsWorked(Date& date);
	//计算该员工在参数指定的日期时，工作了多少天。使用Date类的daysTo函数。
	int getDaysWorked(Date& date);
	~Employee();   //析构函数
private:
	string firstName;
	string lastName;
	Date birthDate;    //内嵌对象，出生日期
	Date hireDate;     //内嵌对象，雇用日期
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
// 以YYYY-MM-DD的形式打印，2011-01-08
void Date::printStandardYear() {
	cout << year << separator;
	cout << setw(2) << setfill('0') << month << separator;
	cout << setw(2) << setfill('0') << day;
}
// 以YY-MM-DD的形式打印，比如11-01-08
void Date::printStandardYear() {
	cout << setw(2) << setfill('0') << year % 100 << separator;
	cout << setw(2) << setfill('0') << month << separator;
	cout << setw(2) << setfill('0') << day;
}
// 计算当前日期与参数日期之间相差几个整年，仅考虑参数日期比当前日期晚的情况
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
/*判断是否为闰年*/
bool Date::isleapyear(int ayear) {
	if ((ayear % 4 == 0 && ayear % 100 != 0) || ayear % 400 == 0)
		return true;
	else
		return false;
}
/*计算参数这一年的总天数*/
int Date::fullYearDays(int ayear) {
	if (isleapyear(ayear))	return 366;
	else
		return 365;
}
/*计算参数这一年内到参数日期前有多少天*/
int Date::getDayOfYear() {
	int days = 0;
	switch (month) {
	case 12:days += 30;//11月的天数
	case 11:days += 31;//10月的天数
	case 10:days += 30;//9月的天数
	case 9:days += 31;//8月的天数
	case 8:days += 31;//7月的天数
	case 7:days += 30;//6月的天数
	case 6:days += 31;//5月的天数
	case 5:days += 30;//4月的天数
	case 4:days += 31;//3月的天数
	case 3:days += 28;//2月的天数
	case 2:days += 31;//1月的天数
	}
	days += day;
	if (month >= 2 && isleapyear(year))
		days += 1;
	return days;
}
/*计算参数这一天到今年结束剩下多少天*/
int Date::getLeftDaysYear() {
	return fullYearDays(year) - getDayOfYear();
}
/* 计算当前日期与参数日期之间相差多少天(考虑闰年)，如果参数日期在当前日期之前，返回负数。 */
int Date::daysTo(Date& date) {
	Date newdate(date.year, date.month, date.day);//参数日期赋值给newdate

	Date* startDate; // 开始日期
	Date* endDate; // 结束日期
	bool ascent = true; // 当前日期大于参数日期，则为真。默认为真。

	// 如果在同一年中
	if (this->year == date.year) {
		return newdate.getDayOfYear() - this->getDayOfYear();
	}

	//初始化开始和结束日期
	// 不在同一年中，且当前日期晚于参数日期
	if (this->year > date.year) {
		startDate = &newdate;
		endDate = this;
	}
	// 如果当前日期早
	else {
		startDate = this;
		endDate = &newdate;
		ascent = false;
	}

	// 先加上开始日期到该年结束的天数
	int offsetDays = startDate->getLeftDaysYear();

	// 再加上开始日期和结束日期之间的所有年的天数 （不包括起止年）
	for (int i = startDate->year + 1; i < endDate->year; i++)
		offsetDays += fullYearDays(i);

	// 再加上结束日期时，该年已经过的天数
	offsetDays += endDate->getDayOfYear();

	// 如果是升序，返回负数
	if (ascent)
		return 0 - offsetDays;
	// 如果是降序
	else
		return offsetDays;
}
/*根据年和月，判断参数日期是否合法。如果合法，返回day，否则返回-1。*/
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

//构造函数，使用“初始化列表”初始化数据成员
Employee::Employee(string first_name, string last_name, Date& birth_date, Date& hire_date):birthDate(), hireDate(){
	firstName = first_name;
	lastName = last_name;
	birthDate = birth_date;
	hireDate = hire_date;
}
//打印员工的信息。调用Date类的print函数，打印员工的生日和雇佣日期。
void Employee:: print() {
	cout << "BirthDate：" << printStandardYear(birth_date->year, birth_date->month, birth_date->day);
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
