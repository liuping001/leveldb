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

    std::string s2 = "helloabc";
    std::string l2 = "hellobef";
    comp_->FindShortestSeparator(&s2, Slice(l2));
    ASSERT_EQ(s2, "helloabc");

    std::string s3 = "helloebc";
    std::string l3 = "helloaef";
    comp_->FindShortestSeparator(&s3, Slice(l3));
    ASSERT_EQ(s3, "helloebc");
}

TEST(TestComparator, FindShortSuccessor) {
    std::string k1 = "bbc";
    comp_->FindShortSuccessor(&k1);
    ASSERT_EQ("c", k1);


    std::string k2 = "abc";
    k2[0] = char(0xff);
    comp_->FindShortSuccessor(&k2);
    ASSERT_EQ(k2.size(), 2);
    ASSERT_EQ(k2[0], char(0xff));
    ASSERT_EQ(k2[1], 'c');
}

}
int main(int argc, char** argv) {
    return leveldb::test::RunAllTests();
}