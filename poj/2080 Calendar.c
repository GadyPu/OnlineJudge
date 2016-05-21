#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const char *Week[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const int Begin = 2000;
const int Days[2][12] = {
	{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};
int IsLeapYear(int year)
{
	if (( 0 == year % 4 && 0 != year % 100 ) || 0 == year % 400)
		return 1;
	return 0;
}
int CalcWeeks(int year,int month, int day)
{
	int week = 0, y = 0, c = 0, m = 0, d = 0;
	if (month == 1 || month == 2)
	{
		c = (year - 1) / 100;
		y = (year - 1) % 100;
		m = month + 12;
		d = day;
	}
	else
	{
		c = year / 100;
		y = year % 100;
		m = month;
		d = day;
	}
	week = y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1; 
	week = week >= 0 ? (week % 7) : (week % 7 + 7); 
	if (7 == week)
		return 0;
	return week;
}
void Calendar(int n, int *year, int *month, int *day)
{
	int temp, i = 0, cur = 0;
	while (cur <= n)
	{
		if (IsLeapYear(Begin + i))
			cur += 366;
		else
			cur += 365;
		i++;
	}
	--i;
	cur -= (IsLeapYear(Begin + i)) ? 366 : 365;
	*year = i;
	int RestDays = n - cur;
	cur = 0;
	temp = IsLeapYear(*year + Begin);
	for (i = 0; i <= 12; i++)
	{
		if (cur <= RestDays)
			cur += Days[temp][i];
		else
			break;
	}
	*month = i;
	*day = Days[temp][--i] - (cur - RestDays) + 1;
	*year += Begin;
}
int main()
{
	int n,year, month, day;
	while (scanf("%d", &n) != EOF && -1!=n)
	{
		int real;
		Calendar(n, &year, &month, &day);
		real = CalcWeeks(year, month, day);
		printf("%04d-%02d-%02d %s\n", year, month, day, Week[real]);
	}
	return 0;
}
