#ifndef HPP

#define HPP
#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
using namespace std;


typedef enum { train, aircraft, car }Traffic;				//动车/飞机/汽车
typedef enum { cost_first, time_first, time_limit }Strategy;//花费最少/时间最少/规定时间内费用最少
const int COST_MAX = INT32_MAX;					//COST上界
const int TIME_MAX = INT32_MAX;					//TIME上界
const int CITY_MAX = 20;						//最大城市个数
const int PATH_MAX = 100;						//路径最大长度
const int HOUR = 24;
const int MINUTE = 60;

class Path;
class Time//时间类
{
public:
	int date;
	int hour;
	int minute;
	Time()
	{
		date = hour = minute = 0;
	}
	Time(int d, int h, int m)
	{
		date = d;
		hour = h;
		minute = m;
	}
	Time(const Time& t)
	{
		date = t.date;
		hour = t.hour;
		minute = t.minute;
	}
	Time& operator=(const Time& t)
	{
		date = t.date;
		hour = t.hour;
		minute = t.minute;
		return *this;
	}
	const Time operator+(const Path& p);
	const Time operator+(const Time& t)
	{
		Time temp;
		temp.minute += t.minute;
		temp.hour = temp.hour + t.hour + minute / MINUTE;
		temp.minute %= MINUTE;
		temp.date = temp.date + t.date + hour / HOUR;
		temp.hour %= HOUR;
		return temp;
	}
	const Time operator+(int time_used)
	{
		Time temp(*this);
		temp.minute += time_used;
		temp.hour += temp.minute / MINUTE;
		temp.minute %= MINUTE;
		temp.date += temp.minute / HOUR;
		temp.hour %= HOUR;
		return temp;
	}
	const Time operator-(const Time& t)
	{
		int time_used;
		time_used = (minute - t.minute) + (hour - t.hour)*MINUTE + (date - t.date)*MINUTE*HOUR;
		Time temp;
		temp.minute = time_used;
		temp.hour = temp.minute / MINUTE;
		temp.minute %= MINUTE;
		temp.date = temp.minute / HOUR;
		temp.hour %= HOUR;
		return temp;
	}
	
};
const bool operator<(const Time& t1, const Time& t2)
{
	if (t1.date < t2.date)return true;
	else if (t1.date == t2.date&&t1.hour < t2.hour)return true;
	else if (t1.date == t2.date&&t1.hour == t2.hour&&t1.minute < t2.minute)return true;
	return false;
}
const bool operator<=(const Time& t1, const Time& t2)
{
	if (t1.date < t2.date)return true;
	else if (t1.date == t2.date&&t1.hour < t2.hour)return true;
	else if (t1.date == t2.date&&t1.hour == t2.hour&&t1.minute <= t2.minute)return true;
	return false;
}
class Path//路径Unit
{
public:
	int from;				//起始城市
	int to;					//到达城市
	Time begin_time;		//开始时间
	Time end_time;			//到达时间
	int time_used;			//所用时间/分钟
	int cost;				//费用
	Traffic traffic;		//交通方式
	string serial_number;	//列车班次、航班号
	Path() {};
	Path(const Path& p)
	{
		from = p.from;
		to = p.to;
		begin_time = p.begin_time;
		end_time = p.end_time;
		time_used = p.time_used;
		cost = p.cost;
		traffic = p.traffic;
		serial_number = p.serial_number;
	}
	Path& operator=(const Path& p)
	{
		this->from = p.from;
		this->to = p.from;
		this->begin_time = p.begin_time;
		this->time_used = p.time_used;
		this->cost = p.cost;
		this->traffic = p.traffic;
		this->serial_number = p.serial_number;
		return *this;
	}
};
const Time Time::operator+(const Path& p)
{
	Time t(*this);
	if (t.hour > p.begin_time.hour || t.hour == p.begin_time.hour&&t.minute > p.begin_time.minute)t.date++;
	t.hour = p.begin_time.hour;
	t.minute = p.begin_time.minute;
	t = t + p.time_used;
	return t;
}
class User//用户类
{
public:
	int id;					//用户ID
	string name;			//用户名
	int start;				//出发地
	int target;				//目的地
	int cur_site;			//当前位置
	Time start_time;		//开始时间
	Time ddl_time;			//截止时间
	vector<int> must_city;	//必经城市
	vector<Path> path;		//所用路径
	Strategy strategy;		//策略
	int time_expected;		//最大时间(minute)
	int cost_expected;		//最大费用(RMB)
};
class Schedule//存储航班及车次信息的矩阵的单元
{
public:
	Path path[PATH_MAX];
	int path_number;
};
class Road
{
public:
	Path path[PATH_MAX];
	int path_length;
	Time arrivel_time;
	int distance;
	Road()
	{
		path_length = 0;
		Time T(TIME_MAX, TIME_MAX, TIME_MAX);
		arrivel_time = T;
		distance = COST_MAX;
	};
	Road& operator=(const Road& r)
	{
		path_length = r.path_length;
		distance = r.distance;
		arrivel_time = r.arrivel_time;
		for (int i = 0; i < path_length; i++)
		{
			path[i] = r.path[i];
		}
		return *this;
	}
};

#endif