#include "DataHistory/DataUtils.h"

#include <chrono>

DataTrace::Timestamp now() {
    auto now = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch());
    auto timestamp = static_cast<size_t>(duration.count());
    return timestamp;
}
