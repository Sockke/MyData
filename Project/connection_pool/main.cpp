#include "connection_pool.h"
#include "sql_connection.h"
#include <vector>
#include <algorithm>

/*
  clock()单位是时钟计时单元, 是C/C++的一种计时单位
  CLOCKS_PER_SEC是每秒中有多少个时钟计时单元

  dur(clock())  / CLOCKS_PER_SEC 才是真正的时间

  只不过在windows下, clock()返回的单位数值与毫秒数值相同罢了
*/

#define N 10000

int main() {
  std::vector<std::thread> tlist(4);
  clock_t begin = clock();

  for (int i = 0; i < 4; ++i) {
    tlist[i] = std::thread([]()->void{
        ConnectionPool* connPool = ConnectionPool::getPool();
        for (int i = 0; i < N / 4; ++i) {
          std::shared_ptr<Connection> conn(connPool->getConn());
          char sql[1024] = {0};
          sprintf(sql, "insert into user(name, age, gender) values('%s', %d, '%s');",
              "sock", 18, "male");
          conn->DML(sql);
          /*
          Connection conn;
          conn.connect("127.0.0.1", "root", "034917", "chat", 3306);
          char sql[1024] = {0};
          sprintf(sql, "insert into user(name, age, gender) values('%s', %d, '%s');",
              "sock", 18, "male");
          conn.DML(sql);
          */
        }
    });
  }
  std::for_each(tlist.begin(), tlist.end(), std::mem_fn(&std::thread::join));

  clock_t end = clock();
  cout << (double)(end - begin) / CLOCKS_PER_SEC << "s" << endl;
  return 0;
}

#if 0
int main() {
  clock_t begin = clock();
  ConnectionPool* connPool = ConnectionPool::getPool();

  for (int i = 0; i < N; ++i) {
    std::shared_ptr<Connection> conn(connPool->getConn());
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name, age, gender) values('%s', %d, '%s');",
        "sock", 18, "male");
    conn->DML(sql);
    /*
    Connection conn;
    conn.connect("127.0.0.1", "root", "034917", "chat", 3306);
    char sql[1024] = {0};
    sprintf(sql, "insert into user(name, age, gender) values('%s', %d, '%s');",
        "sock", 18, "male");
    conn.DML(sql);
    */
  }
  clock_t end = clock();
  cout << (double)(end - begin) / CLOCKS_PER_SEC << "s" << endl;
  return 0;
}
#endif
