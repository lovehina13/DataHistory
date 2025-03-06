#pragma once

#include "DataHistory/DataTrace.h"

#include <map>
#include <set>
#include <vector>

class DataHistory {
  public:
    using DataTraces = std::vector<DataTrace>;
    using DataChanges = std::map<DataTrace::Id, DataTraces>;

    DataHistory();

    void create(DataTrace::Id id, DataTrace::Values values, DataTrace::Reason reason);
    void update(DataTrace::Id id, DataTrace::Values values, DataTrace::Reason reason);
    void remove(DataTrace::Id id, DataTrace::Reason reason);

    std::string history() const;
    std::string history(const DataTrace::Ids& ids) const;
    std::string history(const DataTrace::Names& names) const;
    std::string history(const DataTrace::Ids& ids, const DataTrace::Names& names) const;

    std::string snapshot(const DataTrace::Timestamp& timestamp) const;

  protected:
    DataTrace::Ids ids() const;
    DataTrace::Names names() const;

    void log(DataTrace::Id id, DataTrace::Action action, DataTrace::Values values, DataTrace::Reason reason);

  private:
    DataChanges _dataChanges{};
};
