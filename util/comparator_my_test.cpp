//
// Created by liuping on 2019/2/28.
//

#include "util/testharness.h"
#include "include/leveldb/comparator.h"

namespace leveldb {

struct TestComparator {
    const leveldb::Comparator *comp_;

    TestComparator() {
        comp_ = leveldb::BytewiseComparator();
    }
};

TEST(TestComparator, FindShortestSeparator) {
    std::string s1 = "helloabc";
    std::string l1 = "hellocbc";
    comp_->FindShortestSeparator(&s1, Slice(l1));
    ASSERT_EQ(s1, "hellob");
}

TEST(TestComparator, FindShortSuccessor) {
    std::string k1 = "bbc";
    comp_->FindShortSuccessor(&k1);
    ASSERT_EQ("b", k1);
}

}
int main(int argc, char** argv) {
    return leveldb::test::RunAllTests();
}