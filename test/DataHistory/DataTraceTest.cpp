#include "BaseTest.h"

#include "DataHistory/DataTrace.h"

const DataTrace::Timestamp timestamp{1000};
const DataTrace::Id id{1};
const DataTrace::Action action{DataTrace::Action::CREATE};
const DataTrace::Values values{{"value", "10.0"}};
const DataTrace::Reason reason{"reason"};
const DataTrace::Names names{"value"};

TEST_F(BaseTest, DataTrace_Constructor) {
    DataTrace obj(timestamp, id, action, values, reason);
    EXPECT_EQ(obj.timestamp(), timestamp);
    EXPECT_EQ(obj.id(), id);
    EXPECT_EQ(obj.action(), action);
    EXPECT_EQ(obj.values(), values);
    EXPECT_EQ(obj.reason(), reason);
}

TEST_F(BaseTest, DataTrace_Getters) {
    DataTrace obj(timestamp, id, action, values, reason);
    EXPECT_EQ(obj.timestamp(), timestamp);
    EXPECT_EQ(obj.id(), id);
    EXPECT_EQ(obj.action(), action);
    EXPECT_EQ(obj.values(), values);
    EXPECT_EQ(obj.reason(), reason);
    EXPECT_EQ(obj.names(), names);
}

TEST_F(BaseTest, DataTrace_Trace) {
    DataTrace obj(timestamp, id, action, values, reason);
    std::string trace = obj.trace();
    std::string expected = "Timestamp: 1000 | Id: 1 | Action: CREATE | Values: { value=10.0 } | Reason: reason";
    EXPECT_EQ(trace, expected);
}
