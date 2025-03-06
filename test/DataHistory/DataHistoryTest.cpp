#include "BaseTest.h"

#include "DataHistory/DataHistory.h"
#include "DataHistory/DataUtils.h"

std::vector<std::string> stringList(const std::string& s) {
    std::vector<std::string> sList;
    std::stringstream ss(s);
    std::string line;
    while (std::getline(ss, line, '\n')) {
        sList.emplace_back(line);
    }
    return sList;
}

TEST_F(BaseTest, DataHistory_Constructor) {
    DataHistory obj;
    // TODO: Check something?
}

TEST_F(BaseTest, DataHistory_History) {
    DataHistory obj;
    obj.create(1, {{"name", "ABC"}, {"value", "10.0"}}, "Create item #1");
    obj.create(2, {{"name", "DEF"}, {"value", "20.0"}}, "Create item #2");
    obj.update(1, {{"name", "GHI"}}, "Update item #1 name");
    obj.update(2, {{"name", "JKL"}}, "Update item #2 name");
    obj.update(1, {{"value", "15.0"}}, "Update item #1 value");
    obj.update(2, {{"value", "25.0"}}, "Update item #2 value");
    obj.remove(1, "Remove item #1");
    obj.remove(2, "Remove item #2");
    std::string history1 = obj.history();
    std::string history2 = obj.history({1});
    std::string history3 = obj.history({"name"});
    std::string history4 = obj.history({1}, {"name"});
    EXPECT_EQ(stringList(history1).size(), 10);
    EXPECT_EQ(stringList(history2).size(), 6);
    EXPECT_EQ(stringList(history3).size(), 8);
    EXPECT_EQ(stringList(history4).size(), 5);
}

TEST_F(BaseTest, DataHistory_Snapshot) {
    DataHistory obj;
    obj.create(1, {{"name", "ABC"}, {"value", "10.0"}}, "Create item #1");
    obj.create(2, {{"name", "DEF"}, {"value", "20.0"}}, "Create item #2");
    std::string snapshot1 = obj.snapshot(now());
    obj.update(1, {{"name", "GHI"}}, "Update item #1 name");
    obj.update(2, {{"name", "JKL"}}, "Update item #2 name");
    std::string snapshot2 = obj.snapshot(now());
    obj.update(1, {{"value", "15.0"}}, "Update item #1 value");
    obj.update(2, {{"value", "25.0"}}, "Update item #2 value");
    std::string snapshot3 = obj.snapshot(now());
    obj.remove(1, "Remove item #1");
    obj.remove(2, "Remove item #2");
    std::string snapshot4 = obj.snapshot(now());
    EXPECT_EQ(stringList(snapshot1).size(), 4);
    EXPECT_EQ(stringList(snapshot2).size(), 4);
    EXPECT_EQ(stringList(snapshot3).size(), 4);
    EXPECT_EQ(stringList(snapshot4).size(), 2);
}
