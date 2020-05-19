#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>

#include "list.h"
//#include <list>

//template<typename T>
//using List = std::list<T>;

void BasicTest() {
    List<int> v;
    assert(v.size() == 0);

    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
    // 0123456789
    
    assert(v.back() == 9);

    for (int i = 0; i < 5; ++i) {
        v.pop_front();
    }
    // 56789
    
    assert(v.front() == 5);

    {
        std::ostringstream out;
        for (auto x: v) {
            out << x;
        }

        assert(v.size() == 5);
        assert(out.str() == "56789");
    }

    {
        std::ostringstream out;
        for (int i = 100000; i >= 0; --i) {
            v.push_front(i);
            v.pop_back();
        }
        // 01234
        for (auto x: v) {
            out << x;
        }
        assert(v.size() == 5);
        assert(out.str() == "01234");
    }

    List<int> vv = v;
    {
        std::ostringstream out;
        for (auto x: v) {
            out << x;
        }
        for (auto x: vv) {
            out << x;
        }
        assert(v.size() == 5);
        assert(vv.size() == 5);
        assert(out.str() == "0123401234");
    }

    {
        std::ostringstream out;
        for (int i = 0; i < 10; ++i) {
            v.push_back(5);
            v = vv = v;
        }
        for (auto x: v) {
            out << x;
        }
        for (auto x: vv) {
            out << x;
        }
        assert(v.size() == 15);
        assert(vv.size() == 15);
        assert(out.str() == "012345555555555012345555555555");
    }
    
    v.clear();
    List<int> vvv = std::move(v);
    v = std::move(vv);
    vv = std::move(vvv);

    v.pop_front();
    v.pop_back();
    assert(v.size() == 13);
    assert(vv.size() == 0);
    
    {
        std::ostringstream out;
        for (auto x: v) {
            out << x;
        }
        for (auto x: vv) {
            out << x;
        }
     
        assert(out.str() == "1234555555555");
    }
}

void TestIterators() {
    List<std::string> one(10, "abc");
    
    int count = 0;
    for (auto it = one.begin(); it != one.end(); ++it) {
        ++count;
        *it = (count % 2 ? "aaa" : "bbb");
    }
    
    {
        auto zero = one;
        one.clear();
        std::copy_if(zero.begin(), zero.end(), std::back_inserter(one), [](const std::string& x) { return x != "aaa"; });
    }
    
    assert(one.size() == 5);

    for (const auto& str: one) {
        assert(str == "bbb");
    }

    List<std::string> two;
    for (size_t i = 0; i < 5; ++i) {
        two.emplace_back("aaa");
    }
    auto it = two.cbegin();
    for (size_t i = 0; i < 5; ++i) {
        two.emplace_front("bbb");
    }
    
    for (size_t i = 0; i < 5; ++i) {
        two.emplace(it, "ccc");
    }
 
    two.reverse();
    two.unique();
    two.reverse();
    
    assert(two.front() == "bbb");
    assert(*++two.begin() == "ccc");
    assert(*++++two.cbegin() == "aaa");

    it = one.cbegin();
    for (int i = 0; i < 5; ++i) {
        ++it;
        one.erase(one.begin());
    }
    assert(one.empty());

    assert(it == one.end());

    // must become "bbb ccc aaa"
    std::copy(two.cbegin(), two.cend(), std::inserter(one, one.end()));
    assert(one.front() == "bbb");
    assert(*++one.cbegin() == "ccc");
    assert(one.back() == "aaa");

    // must become "aaa ccc bbb bbb ccc aaa"
    std::move(two.begin(), two.end(), std::front_inserter(one));
    assert(two.size() == 3);
    assert(two.front() == std::string());

    two.clear();
    assert(two.size() == 0);
    
    // once again, why not
    two.clear();
    std::copy(two.cbegin(), two.cend(), std::inserter(one, one.begin()));

    auto left = std::find(one.begin(), one.end(), "bbb");
    auto right = std::find(left, one.end(), "ccc");
    // must become "aaa ccc bbb aaa"
    one.erase(std::next(left), std::next(right));

    assert(one.size() == 4);
    // must become "bbb aaa aaa ccc"
    assert(std::next_permutation(one.begin(), one.end()));

    // "ccc aaa aaa bbb"
    one.reverse();
    assert(one.size() == 4);
    two = std::move(one);
    // "ccc aaa bbb"
    two.unique();

    // I'm crazy, why not doing it again
    one.clear();

    assert(two.front() == "ccc");
    assert(*++two.cbegin() == "aaa");
    assert(two.back() == "bbb");

    // And finally some performance checks
    {
        List<std::string> three(100000);
        auto pos = three.begin();
        for (int i = 0; i < 100000; ++i) {
            ++pos;
            three.insert(pos, "abacaba");

        }
        
        for (int i = 0; i < 100000; ++i)
            three.erase(three.begin());
        three.unique();
        assert(three.size() == 100000);
        for (auto& x : three) {
            x = "a";
        }
        three.unique();
        one = std::move(three);
        assert(one.size() == 1);
    }

    
}

struct VerySpecialType {
    int x = 0;
    explicit VerySpecialType(int x): x(x) {}
    VerySpecialType(const VerySpecialType&) = delete;
    VerySpecialType& operator=(const VerySpecialType&) = delete;

    VerySpecialType(VerySpecialType&&) = default;
    VerySpecialType& operator=(VerySpecialType&&) = default;
};

struct NeitherDefaultNorCopyConstructible {
    VerySpecialType x;

    NeitherDefaultNorCopyConstructible() = delete;
    NeitherDefaultNorCopyConstructible(const NeitherDefaultNorCopyConstructible&) = delete;
    NeitherDefaultNorCopyConstructible& operator=(const NeitherDefaultNorCopyConstructible&) = delete;

    NeitherDefaultNorCopyConstructible(VerySpecialType&& x): x(std::move(x)) {}
    NeitherDefaultNorCopyConstructible(NeitherDefaultNorCopyConstructible&&) = default;
    NeitherDefaultNorCopyConstructible& operator=(NeitherDefaultNorCopyConstructible&&) = default;
};

void TestNoRedundantCopies() {
    List<NeitherDefaultNorCopyConstructible> tst;

    tst.emplace_back(VerySpecialType(0));
    tst.emplace(tst.begin(), VerySpecialType(1));
    
    // now 1 0
    
    tst.push_back(VerySpecialType(2));
    // now 1 0 2

    tst.pop_front();
    // now 0 2

    *tst.begin() = VerySpecialType(3);
    // now 3 2

    auto lst = std::move(tst); // 3 2
    tst.push_front(VerySpecialType(4)); // 4

    assert(tst.size() == 1);
    assert(lst.size() == 2);

    std::reverse(lst.begin(), lst.end()); // 2 3

    assert(lst.front().x.x == 2);

}


int main() {
    BasicTest();
    TestIterators();
    TestNoRedundantCopies();
}
