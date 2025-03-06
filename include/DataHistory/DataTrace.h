#pragma once

#include <map>
#include <set>
#include <string>

class DataTrace {
  public:
    enum class Action { UNDEFINED, CREATE, UPDATE, REMOVE };
    using Timestamp = size_t;
    using Id = size_t;
    using Ids = std::set<DataTrace::Id>;
    using Name = std::string;
    using Names = std::set<Name>;
    using Value = std::string;
    using Values = std::map<Name, Value>;
    using Reason = std::string;

    DataTrace(Timestamp timestamp, Id id, Action action, Values values, Reason reason);

    const Timestamp& timestamp() const;
    const Id& id() const;
    const Action& action() const;
    const Values& values() const;
    const Reason& reason() const;
    Names names() const;

    std::string trace() const;

  protected:
    std::string actionText() const;

  private:
    Timestamp _timestamp{};
    Id _id{};
    Action _action{};
    Values _values{};
    Reason _reason{};
};
