#include"struct.hpp"
Time StringToTime(string str)
{
	char *cha = (char*)str.data();
	int year, month, day, hour, min;
	sscanf(cha, "%d/%d/%d %d:%d", year, month, day, hour, min);
	Time time;
	time.hour = hour;
	time.minute = min;
	return time;
}
User CreatUser(int id, string name)
{
	User u;
	u.id = id;
	u.name = name;
	return u;
}
void UserPlan(User u,string from,string to,string city[8],Time begin,Time end,string strategy)
{
	if (from == "北京") u.start = 0;
	else if (from == "上海") u.start = 1;
	else if (from == "广州") u.start = 2;
	else if (from == "厦门") u.start = 3;
	else if (from == "重庆") u.start = 4;
	else if (from == "拉萨") u.start = 5;
	else if (from == "乌鲁木齐") u.start = 6;
	else if (from == "武汉") u.start = 7;
	else if (from == "南京") u.start = 8;
	else if (from == "哈尔滨") u.start = 9;
	if (to == "北京") u.target = 0;
	else if (to == "上海") u.target = 1;
	else if (to == "广州") u.target = 2;
	else if (to == "厦门") u.target = 3;
	else if (to == "重庆") u.target = 4;
	else if (to == "拉萨") u.target = 5;
	else if (to == "乌鲁木齐") u.target = 6;
	else if (to == "武汉") u.target = 7;
	else if (to == "南京") u.target = 8;
	else if (to == "哈尔滨") u.target = 9;
	for (int k = 0; k < 8; k++)
	{
		if (city[k] == "北京") u.must_city[k] = 0;
		else if (city[k] == "上海") u.must_city[k] = 1;
		else if (city[k] == "广州") u.must_city[k] = 2;
		else if (city[k] == "厦门") u.must_city[k] = 3;
		else if (city[k] == "重庆") u.must_city[k] = 4;
		else if (city[k] == "拉萨") u.must_city[k] = 5;
		else if (city[k] == "乌鲁木齐") u.must_city[k] = 6;
		else if (city[k] == "武汉") u.must_city[k] = 7;
		else if (city[k] == "南京") u.must_city[k] = 8;
		else if (city[k] == "哈尔滨") u.must_city[k] = 9;
	}
	u.start_time = begin;
	u.ddl_time = end;
	if (strategy == "时间最少") u.strategy = time_first;
	else if (strategy == "费用最少") u.strategy = cost_first;
	else if (u.start_time.date != 0 && u.ddl_time.date != 0) u.strategy = time_limit;
}