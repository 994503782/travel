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
	if (from == "����") u.start = 0;
	else if (from == "�Ϻ�") u.start = 1;
	else if (from == "����") u.start = 2;
	else if (from == "����") u.start = 3;
	else if (from == "����") u.start = 4;
	else if (from == "����") u.start = 5;
	else if (from == "��³ľ��") u.start = 6;
	else if (from == "�人") u.start = 7;
	else if (from == "�Ͼ�") u.start = 8;
	else if (from == "������") u.start = 9;
	if (to == "����") u.target = 0;
	else if (to == "�Ϻ�") u.target = 1;
	else if (to == "����") u.target = 2;
	else if (to == "����") u.target = 3;
	else if (to == "����") u.target = 4;
	else if (to == "����") u.target = 5;
	else if (to == "��³ľ��") u.target = 6;
	else if (to == "�人") u.target = 7;
	else if (to == "�Ͼ�") u.target = 8;
	else if (to == "������") u.target = 9;
	for (int k = 0; k < 8; k++)
	{
		if (city[k] == "����") u.must_city[k] = 0;
		else if (city[k] == "�Ϻ�") u.must_city[k] = 1;
		else if (city[k] == "����") u.must_city[k] = 2;
		else if (city[k] == "����") u.must_city[k] = 3;
		else if (city[k] == "����") u.must_city[k] = 4;
		else if (city[k] == "����") u.must_city[k] = 5;
		else if (city[k] == "��³ľ��") u.must_city[k] = 6;
		else if (city[k] == "�人") u.must_city[k] = 7;
		else if (city[k] == "�Ͼ�") u.must_city[k] = 8;
		else if (city[k] == "������") u.must_city[k] = 9;
	}
	u.start_time = begin;
	u.ddl_time = end;
	if (strategy == "ʱ������") u.strategy = time_first;
	else if (strategy == "��������") u.strategy = cost_first;
	else if (u.start_time.date != 0 && u.ddl_time.date != 0) u.strategy = time_limit;
}