#include "BaseTest.h"

#include "DataHistory/DataUtils.h"

TEST_F(BaseTest, DataUtils_SetText) {
    std::set<int> set = {1, 2, 3};
    std::string text = setText(set);
    std::string expected = "{ 1, 2, 3 }";
    EXPECT_EQ(text, expected);
}

TEST_F(BaseTest, DataUtils_MapText) {
    std::map<int, int> map = {{1, 10}, {2, 20}, {3, 30}};
    std::string text = mapText(map);
    std::string expected = "{ 1=10, 2=20, 3=30 }";
    EXPECT_EQ(text, expected);
}

TEST_F(BaseTest, DataUtils_Now) {
    DataTrace::Timestamp timestamp = now();
    EXPECT_GT(timestamp, 0);
}
