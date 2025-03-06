#pragma once

#include "DataHistory/DataTrace.h"

#include <sstream>
#include <string>

template <typename T> std::string setText(const T& items) {
    std::stringstream ss;
    ss << "{ ";
    size_t cpt = 0;
    for (const auto& item : items) {
        ss << item;
        ss << (++cpt < items.size() ? ", " : "");
    }
    ss << " }";
    return ss.str();
}

template <typename T> std::string mapText(const T& items) {
    std::stringstream ss;
    ss << "{ ";
    size_t cpt = 0;
    for (const auto& item : items) {
        ss << item.first << "=" << item.second;
        ss << (++cpt < items.size() ? ", " : "");
    }
    ss << " }";
    return ss.str();
}

DataTrace::Timestamp now();
