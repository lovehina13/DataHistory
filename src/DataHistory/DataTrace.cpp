#include "DataHistory/DataTrace.h"
#include "DataHistory/DataUtils.h"

#include <sstream>

DataTrace::DataTrace(Timestamp timestamp, Id id, Action action, Values values, Reason reason)
    : _timestamp(std::move(timestamp)), _id(std::move(id)), _action(std::move(action)), _values(std::move(values)), _reason(std::move(reason)) {}

const DataTrace::Timestamp& DataTrace::timestamp() const { return _timestamp; }

const DataTrace::Id& DataTrace::id() const { return _id; }

const DataTrace::Action& DataTrace::action() const { return _action; }

const DataTrace::Values& DataTrace::values() const { return _values; }

const DataTrace::Reason& DataTrace::reason() const { return _reason; }

DataTrace::Names DataTrace::names() const {
    DataTrace::Names names;
    for (const auto& value : _values) {
        const auto& name = value.first;
        names.insert(name);
    }
    return names;
}

std::string DataTrace::trace() const {
    std::stringstream ss;
    ss << "Timestamp: " << _timestamp << " | ";
    ss << "Id: " << _id << " | ";
    ss << "Action: " << actionText() << " | ";
    ss << "Values: " << mapText(_values) << " | ";
    ss << "Reason: " << _reason;
    return ss.str();
}

std::string DataTrace::actionText() const { return (_action == Action::CREATE ? "CREATE" : _action == Action::UPDATE ? "UPDATE" : _action == Action::REMOVE ? "REMOVE" : "UNDEFINED"); }
