#include"struct.hpp"
/****************************************************
运用Dijkstra算法  
输入：
各城市间路径的邻接矩阵，源点，目的地，策略，flag(判断是否有解)，开始时间
输出：
返回所求得策略的vector，若无法满足，则将flag置为false
要求：
邻接矩阵单个节点包括：
1.交通方式
2.航班号/车次
3.出发时间（24小时制，便于运算）
4.到达时间
5.费用
*****************************************************/
void algorithm(Schedule** shift, int from, int to, Strategy strategy, vector<Path> &path, bool flag, Time begin, Time limit)//得到的路径会连接到path的尾部
{
	//int(*GetPath)(Schedule** shift, int from, int to, Time begin, vector<Path> &path);
	switch (strategy)
	{
	case cost_first:
		flag = (bool)dijkstra_cost_first(shift, from, to, begin, path);
		break;
	case time_first:
		flag = (bool)dijkstra_time_first(shift, from, to, begin, path);
		break;
	case time_limit:
		flag = (bool)DFS_time_limit(shift, from, to, begin, limit, path);
		break;
	default:break;
	}
}

int dijkstra_cost_first(Schedule** shift, int from, int to, Time begin, vector<Path> &path)
{
	Road road[CITY_MAX];//用于存储源点到其余各点的路径
	vector<int> distance(CITY_MAX, COST_MAX);//存有距离的向量,此处距离为旅行费用，初始为最大值COST_MAX
	int determined[CITY_MAX] = { 0 };//标志最短路径是否已经确定

	for (int i = 0; i < CITY_MAX; i++)//初始化从源点到点i的初始距离
	{
		road[i].path_length = 0;//路径长度初始为0

		for (int j = 0; j < shift[from][i].path_number; j++)//遍历各条路径，选择COST最少的替换
		{
			if (shift[from][i].path[j].cost < distance[i])
			{
				road[i].path[0] = shift[from][i].path[j];//加入路径表中
				
				road[i].path_length = 1;//路径长度置1
				if (begin <= road[i].path[0].begin_time);
				else road[i].path[0].begin_time.date++;//若今天无法出发，则date+1
				distance[i] = shift[from][i].path[j].cost;//存在路径时修改距离
			}
		}
		if (road[i].path_length == 1)road[i].arrivel_time = begin + road[i].path[0];//初始化到达时间
	}
	determined[from] = 1;//固定源点
	int city;
	Path p;
	for (int n = 0; n < CITY_MAX-1; n++)
	{
		city = 0;
		while (determined[city])city++;
		for (int i = 0; i < CITY_MAX; i++)
		{
			if (!determined[i] && distance[i] < distance[city])city = i;//找到该轮确定最小距离的点
		}
		determined[city] = 1;
		if (city == to)break;//若已经找到最短路径，则结束循环
		for (int i = 0; i < CITY_MAX; i++)//检测从city到i的路径
		{
			p.cost = COST_MAX;//每次都要把cost置为最大值
			for (int j = 0; j < shift[city][i].path_number; j++)//找出COST最小的路径，存在p中
			{
				if (shift[city][i].path[j].cost < p.cost)
				{
					p = shift[city][i].path[j];
				}
			}
			if (shift[city][i].path_number != 0)//存在路径时进入
			{
				if (road[city].distance + p.cost < road[i].distance)//若能够缩短距离，先复制from-city的路径，再将city-i的路径加入，并更新distance
				{
					road[i] = road[city];//from-city
					road[i].distance = road[city].distance + p.cost;//更新最短距离
					road[i].path_length++;//路径长度+1
					road[i].path[road[i].path_length - 1] = p;//city-i
					road[i].path[road[i].path_length - 1].begin_time.date = road[city].arrivel_time.date;//统一日期
					if (road[i].path[road[i].path_length - 1].begin_time < road[city].arrivel_time)road[i].path[road[i].path_length - 1].begin_time.date++;//若当日无法出发，则日期+1
					road[i].path[road[i].path_length - 1].end_time = road[i].path[road[i].path_length - 1].begin_time + road[i].path[road[i].path_length - 1].time_used;//算出到达时间
					road[i].arrivel_time = road[i].path[road[i].path_length - 1].end_time;
					distance[i] = road[i].distance;//更新distance
				}
			}
		}
	}
	for (int i = 0; i < road[to].path_length; i++)
	{
		path.push_back(road[to].path[i]);//将所得的解连接在path的尾部
	}
	return road[to].path_length;
}
int dijkstra_time_first(Schedule** shift, int from, int to, Time begin, vector<Path> &path)
{
	Road road[CITY_MAX];//用于存储源点到其余各点的路径
	Time T(TIME_MAX, TIME_MAX, TIME_MAX);//时间的上界
	vector<Time> distance(CITY_MAX, T);//存有距离的向量,此处距离为到达该城市的最早时间，初始为最大值T
	int determined[CITY_MAX] = { 0 };//标志最短路径是否已经确定

	for (int i = 0; i < CITY_MAX; i++)//初始化从源点到点i的初始距离
	{
		road[i].path_length = 0;//路径长度初始为0

		for (int j = 0; j < shift[from][i].path_number; j++)//遍历各条路径，选择TIME最少的替换
		{

			if (begin + shift[from][i].path[j] < distance[i])
			{
				road[i].path[0] = shift[from][i].path[j];//加入路径表中
				road[i].path[0].begin_time.date = begin.date;//统一日期
				if (begin <= road[i].path[0].begin_time);
				else road[i].path[0].begin_time.date++;//若今天无法出发，则date+1
				road[i].path_length = 1;//路径长度置1
				distance[i] = begin + shift[from][i].path[j];//存在路径时修改距离
			}
		}
		if (road[i].path_length == 1)road[i].arrivel_time = distance[i];//初始化到达时间
	}
	determined[from] = 1;//固定源点
	int city;
	Path p;
	for (int n = 0; n < CITY_MAX - 1; n++)
	{
		city = 0;
		while (determined[city])city++;
		for (int i = 0; i < CITY_MAX; i++)
		{
			if (!determined[i] && distance[i] < distance[city])city = i;//找到该轮确定最小时间的点
		}
		determined[city] = 1;
		if (city == to)break;//若已经找到最短路径，则结束循环
		for (int i = 0; i < CITY_MAX; i++)//检测从city到i的路径
		{
			p.end_time = T;//每次都要把到达时间置为最大值
			for (int j = 0; j < shift[city][i].path_number; j++)//找出用时最小的路径，存在p中
			{
				if (road[city].arrivel_time + shift[city][i].path[j] < p.end_time)
				{
					p = shift[city][i].path[j];
				}
			}
			if (shift[city][i].path_number != 0)//存在路径时进入
			{
				if (road[city].arrivel_time + p < road[i].arrivel_time)//若能够缩短时间，先复制from-city的路径，再将city-i的路径加入，并更新distance
				{
					road[i] = road[city];
					road[i].path_length++;//路径长度+1
					road[i].path[road[i].path_length - 1] = p;//city-i
					road[i].path[road[i].path_length - 1].begin_time.date = road[city].arrivel_time.date;//统一日期
					if (road[i].path[road[i].path_length - 1].begin_time < road[city].arrivel_time)road[i].path[road[i].path_length - 1].begin_time.date++;//若当天不能出发，日期+1
					road[i].path[road[i].path_length - 1].end_time = road[i].path[road[i].path_length - 1].begin_time + road[i].path[road[i].path_length - 1].time_used;//算出到达时间
					road[i].arrivel_time = road[i].path[road[i].path_length - 1].end_time;
					distance[i] = road[i].arrivel_time;//更新distance
				}
			}
		}
	}
	for (int i = 0; i < road[to].path_length; i++)
	{
		path.push_back(road[to].path[i]);//将所得的解连接在path的尾部
	}
	return road[to].path_length;
}
int DFS_time_limit(Schedule** shift, int from, int to, Time begin, Time limit, vector<Path> &path)//限定时间内花费最少策略，采用DFS搜索
{
	Road road;//用于存储源点到目的地的路径
	Road road_best;//用于存储最佳的路径
	int arrival[CITY_MAX] = { 0 };//用于标志城市是否已经到达过
	arrival[from] = 1;//起始城市置为已到达
	DFS_find_road(shift, arrival, to, begin, limit, road, road_best, from);
	for (int i = 0; i < road_best.path_length; i++)
	{
		path.push_back(road_best.path[i]);//将所得的解连接在path的尾部
	}
	return road_best.path_length;
}
void DFS_find_road(Schedule** shift, int arrival[], int to, Time& begin, Time& limit, Road &road, Road &road_best, int now)//now代表现在所在城市
{
	if (to == now)//找到一条路径时
	{
		if (road.arrivel_time < limit && road.distance < road_best.distance)//若满足给定的条件
		{
			road_best = road;
		}
		return;
	}
	for (int i = 0; i < CITY_MAX; i++)//检测从now到i城市的所有路径
	{
		if (arrival[i])continue;//若该城市已经过一次，则跳过
		for (int j = 0; j < shift[now][i].path_number; j++)
		{
			road.path[road.path_length] = shift[now][i].path[j];//路径加入
			road.path[road.path_length].begin_time.date = road.arrivel_time.date;//统一日期
			if (road.path[road.path_length].begin_time < road.arrivel_time)//若是当天无法出发
			{
				road.path[road.path_length].begin_time.date++;
			}
			road.arrivel_time = road.arrivel_time + road.path[road.path_length];//更新到达时间
			road.distance += road.path[road.path_length].cost;
			road.path_length++;
			DFS_find_road(shift, arrival, to, begin, limit, road, road_best, i);//road更新完毕，进入下一层递归
		}
	}
}