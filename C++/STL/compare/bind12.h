#pragma once

// bind1st实现原理
template <class Compare, class T>
class MyBind1st {
  public:
    MyBind1st(Compare cmp, const T& val)
      : _cmp(cmp)
      , _val(val)
    {}
    bool operator()(const T& second) {
      return _cmp(_val, second);
    }
  private:
    Compare _cmp;
    T _val;
};
template <class Compare, class T>
MyBind1st<Compare, T> myBind1st(Compare cmp, const T& val) {
  return MyBind1st<Compare, T>(cmp, val);
}

// bind2nd的实现原理
template <class Compare, class T>
class MyBind2nd {
  public:
    MyBind2nd(Compare cmp, const T& val)
      : _cmp(cmp)
      , _val(val)
    {}
    bool operator()(const T& first) {
      return _cmp(first, _val);
    }
  private:
    Compare _cmp;
    T _val;
};
template <class Compare, class T>
MyBind2nd<Compare, T> myBind2nd(Compare cmp, const T& val) {
  return MyBind2nd<Compare, T>(cmp, val);
}

// std::find_if的实现原理
template <class Iterator, class Compare>
Iterator myFind_if(Iterator _begin, Iterator _last, Compare cmp) {
  for (; _begin < _last; ++_begin) {
    if (cmp(*_begin)) {
      return _begin;
    }
  }
  return _last;
}
