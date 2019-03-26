#include<iostream>
#include<cstdlib>
#include<vector>
#include<string>
using namespace std;
class Time//时间类
{
private:
	int hour;
	int minute;
};
class User//用户类
{
private:
	int id;//用户ID
	string name;//用户名
	int start;//出发地
	int target;//目的地
	int cur_site;//当前位置
	Time start_time;//开始时间
	Time ddl_time;//截止时间
	vector<int> through_city;//必经城市
	vector<int> path;//所用路径
	int strategy;//策略
};