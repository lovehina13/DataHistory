#include "DataHistory/DataHistory.h"
#include "DataHistory/DataUtils.h"

#include <sstream>

DataHistory::DataHistory() = default;

void DataHistory::create(DataTrace::Id id, DataTrace::Values values, DataTrace::Reason reason) { log(id, DataTrace::Action::CREATE, values, reason); }

void DataHistory::update(DataTrace::Id id, DataTrace::Values values, DataTrace::Reason reason) { log(id, DataTrace::Action::UPDATE, values, reason); }

void DataHistory::remove(DataTrace::Id id, DataTrace::Reason reason) { log(id, DataTrace::Action::REMOVE, DataTrace::Values(), reason); }

std::string DataHistory::history() const { return history(ids(), names()); }

std::string DataHistory::history(const DataTrace::Ids& rIds) const { return history(rIds, names()); }

std::string DataHistory::history(const DataTrace::Names& rNames) const { return history(ids(), rNames); }

std::string DataHistory::history(const DataTrace::Ids& rIds, const DataTrace::Names& rNames) const {
    std::stringstream ss;
    ss << "==================================================" << std::endl;
    ss << "History for " << setText(rIds) << " and " << setText(rNames) << ":" << std::endl;
    std::map<DataTrace::Timestamp, std::string> rTraces;
    for (const auto& id : rIds) {
        if (_dataChanges.count(id) > 0) {
            const auto& dataTraces = _dataChanges.at(id);
            for (const auto& dataTrace : dataTraces) {
                const auto& action = dataTrace.action();
                if (action == DataTrace::Action::CREATE || action == DataTrace::Action::REMOVE) {
                    const auto& timestamp = dataTrace.timestamp();
                    const auto trace = dataTrace.trace();
                    rTraces[timestamp] = trace;
                } else if (action == DataTrace::Action::UPDATE) {
                    const auto names = dataTrace.names();
                    for (const auto& name : names) {
                        if (rNames.count(name) > 0) {
                            const auto& timestamp = dataTrace.timestamp();
                            const auto trace = dataTrace.trace();
                            rTraces[timestamp] = trace;
                            break;
                        }
                    }
                }
            }
        }
    }
    for (const auto& trace : rTraces) {
        ss << trace.second << std::endl;
    }
    return ss.str();
}

std::string DataHistory::snapshot(const DataTrace::Timestamp& rTimestamp) const {
    std::stringstream ss;
    ss << "==================================================" << std::endl;
    ss << "Snapshot at " << rTimestamp << ":" << std::endl;
    std::map<DataTrace::Id, DataTrace::Values> rValues;
    for (const auto& dataChanges : _dataChanges) {
        const auto& dataTraces = dataChanges.second;
        for (const auto& dataTrace : dataTraces) {
            const auto& timestamp = dataTrace.timestamp();
            if (timestamp <= rTimestamp) {
                const auto& action = dataTrace.action();
                if (action == DataTrace::Action::CREATE || action == DataTrace::Action::UPDATE) {
                    const auto& id = dataChanges.first;
                    if (rValues.count(id) == 0) {
                        rValues[id] = DataTrace::Values();
                    }
                    const auto& values = dataTrace.values();
                    for (const auto& value : values) {
                        rValues[id][value.first] = value.second;
                    }
                } else if (action == DataTrace::Action::REMOVE) {
                    const auto& id = dataChanges.first;
                    rValues.erase(id);
                }
            }
        }
    }
    for (const auto& value : rValues) {
        const auto& id = value.first;
        const auto& values = value.second;
        ss << id << ": " << mapText(values) << std::endl;
    }
    return ss.str();
}

void DataHistory::log(DataTrace::Id id, DataTrace::Action action, DataTrace::Values values, DataTrace::Reason reason) {
    DataTrace dataTrace(now(), id, action, values, reason);
    if (_dataChanges.count(id) == 0) {
        _dataChanges[id] = DataTraces();
    }
    _dataChanges[id].emplace_back(dataTrace);
}

DataTrace::Ids DataHistory::ids() const {
    DataTrace::Ids rIds;
    for (const auto& dataChanges : _dataChanges) {
        const auto& id = dataChanges.first;
        rIds.insert(id);
    }
    return rIds;
}

DataTrace::Names DataHistory::names() const {
    DataTrace::Names rNames;
    for (const auto& dataChanges : _dataChanges) {
        const auto& dataTraces = dataChanges.second;
        for (const auto& dataTrace : dataTraces) {
            const auto names = dataTrace.names();
            for (const auto& name : names) {
                rNames.insert(name);
            }
        }
    }
    return rNames;
}
