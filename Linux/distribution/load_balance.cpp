#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <climits>
#include <set>
using namespace std;


/*
  一致性哈希算法
  对于集群管理, 当客户端发送请求与A服务器建立了session后, 
  客户端再发送请求时, 该请求可能被B服务器去处理了, 需要重新建立session
  1. 一致性哈希算法主要是为了解决同一个客户端的请求被同一台服务器进行处理
  2. 一致性哈希算法是一种环形哈希的结构, 集群中的服务器均匀的分布在哈希环上,
  当有节点宕机或增加新的节点时可能会导致节点分布不均匀的情况, 会影响负载均衡.
  通过在哈希环上添加虚拟节点来解决, 使整个哈希环更加散列, 更加均匀.
*/
set<string> s({"A", "B", "C", "D"});
const int len = 160;

class ConsistantHash {
  public:
    ConsistantHash() {
      size_t hash_code = 0;
      for (auto& e : s) {
        for (int i = 0; i < len; ++i) {
          hash_code = hashFunc(e + to_string(i));
          _hash_node.insert({hash_code, e});
        }
      }
    }
    string getIP(const string& cip) {
      size_t hash_code = hashFunc(cip);
      auto it = _hash_node.lower_bound(hash_code);
      if (it == _hash_node.end()) {
        return _hash_node.begin()->second;
      } else {
        return it->second;
      }
    }
    size_t hashFunc(const string& str) {
      return _hash_func(str);
    }
  private:
    map<size_t, string> _hash_node;
    hash<string> _hash_func;
};

int main() {
  ConsistantHash ch;
  cout << ch.getIP("192.168.163.15") << endl;
  cout << ch.getIP("192.168.163.15") << endl;
  //cout << ch.getIP("192.168.163.26") << endl;
  //cout << ch.getIP("192.168.163.33") << endl;
  //cout << ch.getIP("192.168.163.38") << endl;
  //cout << ch.getIP("192.168.163.45") << endl;
  //cout << ch.getIP("192.168.163.67") << endl;
  //cout << ch.getIP("192.168.163.88") << endl;
  //cout << ch.getIP("192.168.163.99") << endl;
  //cout << ch.getIP("192.168.163.129") << endl;
  //cout << ch.getIP("192.168.163.231") << endl;
  return 0;
}

#if 0
static map<string, int> m{{"A", 5}, {"B", 2}, {"C", 3}};

/*
  平滑加权轮询算法 --- nginx
  动态的改变最高权重
  arr[] = {A:5, B:1, C:1}

  1. 5 1 1 --- -2 1 1 --- A
  2. 3 2 2 --- -4 2 2 --- A
  3. 1 3 3 --- 1 -4 3 --- B
  4. 6 -3 4 --- -1 -3 4 --- A
  5. 4 -2 5 --- 4 -2 -2 --- C
  6. 9 -1 -1 --- 2 -1 -1 --- A
  7. 7 0 0 --- 0 0 0 --- A
  8. 5 1 1 ...
*/
class IPObj {
  public:
    IPObj(const string& ip, int weight)
      : _ip(ip)
      , _weight(weight)
      , _cur_weight(weight)
    {}
    string getIP() const {
      return _ip;
    }
    int getWeight() const {
      return _weight;
    }
    int getCurWeight() const {
      return _cur_weight;
    }
    void setCurWeight(int new_weight) {
      _cur_weight = new_weight;
    }
  private:
    string _ip;
    int _weight;
    int _cur_weight;
};
class SmoothWeight {
  public:
    SmoothWeight() {
      int size = m.size();
      _ipobjs.resize(size);
      int i = 0;
      for (auto& e : m) {
        _ipobjs[i++] = new IPObj(e.first, e.second);
        _sum_weight += e.second;
      }
    }
    string getIP() {
      int max_weight = INT_MIN;
      string ip;
      for (auto& e : _ipobjs) {
        if (e->getCurWeight() > max_weight) {
          max_weight = e->getCurWeight();
          ip = e->getIP();
        }
      }
      for (auto& e : _ipobjs) {
        if (e->getIP() == ip) {
          e->setCurWeight(e->getCurWeight()-_sum_weight+e->getWeight());
        } else {
          e->setCurWeight(e->getCurWeight()+e->getWeight());
        }
      }
      return ip;
    }
    ~SmoothWeight() {
      for (auto& e : _ipobjs) {
        delete e;
      }
    }
  private:
    vector<IPObj*> _ipobjs;
    int _sum_weight;
};

int main() {
  SmoothWeight sw;
  for (int i = 0; i < 12; ++i) {
    cout << sw.getIP() << " ";
  }
  cout << endl;
  return 0;
}
#endif

#if 0
/*
  加权随机算法与加权轮询算法
  arr[] = {A:5, B:2, C:3}

  加权随机算法: A-----B--C---
  加权轮询算法: AAAAABBCCC...
*/
class IPObj {
  public:
    IPObj(const string& ip, int weight)
      : _ip(ip)
      , _weight(weight)
    {}
    string getIP() const {
      return _ip;
    }
    int getWeight() const {
      return _weight;
    }
  private:
    string _ip;
    int _weight;
};

class WeightRand {
  public:
    WeightRand() {
      int size = m.size();
      _ipobjs.resize(size);
      int i = 0;
      for (auto& e : m) {
        _ipobjs[i++] = new IPObj(e.first, e.second);
      }
    }
    string getIP() {
      int sum_weight = 0;
      for (auto& e : _ipobjs) {
        sum_weight += e->getWeight();
      }
      int num = rand() % sum_weight+1;
      int curnum = 1;
      string ip;
      for (auto& e : _ipobjs) {
        if (num >= curnum && num < curnum + e->getWeight()) {
          ip = e->getIP();
          break;
        }
        curnum += e->getWeight();
      }
      return ip;
    }
    ~WeightRand() {
      for (auto& e : _ipobjs) {
        delete e;
      }
    }
  private:
    vector<IPObj*> _ipobjs;
};

class WeightRoundRobin {
  public:
    WeightRoundRobin() {
      int size = m.size();
      _ipobjs.resize(size);
      int i = 0;
      for (auto& e : m) {
        _ipobjs[i++] = new IPObj(e.first, e.second);
      }
    }
    string getIP() {
      int sum_weight = 0;
      for (auto& e : _ipobjs) {
        sum_weight += e->getWeight();
      }
      int curnum = 1; 
      string ip;
      for (auto& e : _ipobjs) {
        if (_cnt >= curnum && _cnt < curnum + e->getWeight()) {
          ip = e->getIP();
          break;
        }
        curnum += e->getWeight();
      }
      ++_cnt;
      if (_cnt > sum_weight) {
        _cnt = 1;
      }
      return ip;
    }
    ~WeightRoundRobin() {
      for (auto& e : _ipobjs) {
        delete e;
      }
    }
  private:
    vector<IPObj*> _ipobjs;
    int _cnt;
};

int main() {
  WeightRand wr;
  for (int i = 0; i < 12; ++i) {
    cout << wr.getIP() << " ";
  }
  cout << endl;
  WeightRoundRobin wrr;
  for (int i = 0; i < 12; ++i) {
    cout << wrr.getIP() << " ";
  }
  cout << endl;
  return 0;
}
#endif
