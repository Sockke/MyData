#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

/*
  柜台问题:
  给定一组柜台, 每个柜台有指定的服务时间, 给定一组人,
  求这一组人怎么排队才能时柜台总的服务时间最短
*/

int main() {
  vector<int> service_time{3, 2, 4};
  int N = 15;
  int size = service_time.size();
  // 最优子结构为最短的服务时间
  // 排序
  sort(service_time.begin(), service_time.end());
  // 选择
  vector<int> people(size, 0); // 目前每个柜台的排队人数为0
  int min_time = 0;
  // 排队时看看, 排在哪整体花费的时间最短
  while (N--) {
    int i = 0;
    int cur_time = service_time[i] * (people[i] + 1);
    for (i = 1; i < size; ++i) {
      int cur_time_next = service_time[i] * (people[i] + 1);
      // 在其他柜台上排队更节省时间
      if (cur_time_next < cur_time) { 
        ++people[i];
        min_time = cur_time_next;
        break;
      }
    }
    // 在其他柜台上排队不节省时间
    if (i == size) {
      ++people[0];
      min_time = cur_time;
    }
  }
  cout << min_time << endl;
  return 0;
}
