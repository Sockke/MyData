#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <memory>
#include <cstring>
using std::cout;
using std::endl;

struct Info {
  Info(const std::string name, int age)
    : _name(name)
      , _age(age) {}
  std::string _name;
  int _age;
};


class BinFile {
  public:
    BinFile(const std::string& fname) : _fname(fname) {}
    void writeFile(const std::list<Info>& infos) {
      std::ofstream ofs(_fname);
      if (!ofs.is_open()) {
        perror("file open error");
        exit(-1);
      }
      for (const auto& e : infos) {
        ofs << e._name << " " << e._age << endl;
      }
      ofs.close();
    }
    void readFile(std::list<Info>& infos) {
      std::ifstream ifs(_fname);
      if (!ifs.is_open()) {
        perror("file open error");
        exit(-1);
      }
      // 对feof的封装, 依然是先读后判断
      while (!ifs.eof()) {
        std::string name;
        int age = 0;
        ifs >> name;
        ifs >> age;
        if (!ifs.eof()) {
          infos.push_back(Info(name, age));
        }
      }
      ifs.close();
    }
  private:
    std::string _fname;
};

void show(const std::list<Info>& infos) {
  for (const auto e : infos) {
    cout << e._name << ":" << e._age << endl;
  }
}

int main() {
  //std::list<std::unique_ptr<Info>> infos;
  //infos.push_back(std::unique_ptr<Info>(new Info("sock", 19)));
  //infos.push_back(std::unique_ptr<Info>(new Info("laoma", 21)));
  //infos.push_back(std::unique_ptr<Info>(new Info("liuchen", 19)));
  //infos.push_back(std::unique_ptr<Info>(new Info("liuwei", 20)));
  std::list<Info> infos;
  //infos.push_back(Info("sock", 19));
  //infos.push_back(Info("laoma", 21));
  //infos.push_back(Info("liuchen", 19));
  //infos.push_back(Info("liuwei", 20));
  BinFile fp("tmp.txt");
  //fp.writeFile(infos);
  fp.readFile(infos);
  show(infos);
  return 0;
}
