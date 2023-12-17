#include "Column.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>


csv::ColumnBase::ColumnBase(const std::string& name): name(name) {
    value.reserve(32);
}

std::string csv::ColumnBase::getName(void) {
    return name;
}

std::string csv::ColumnBase::valueAsString(void) {
    return value;
}


csv::Column::Column(const std::string& name): ColumnBase(name) {}

void csv::Column::logValue(int value) {
    this->value = std::to_string(value);
}

void csv::Column::logValue(unsigned int value) {
    this->value = std::to_string(value);
}

void csv::Column::logValue(float value) {
    this->value = std::to_string(value);
}

void csv::Column::logValue(const std::string& value) {
    this->value = value;
}

void csv::Column::logValue(bool value) {
    if (value) {
        this->value = "true";
    }
    else {
        this->value = "false";
    }
}


void csv::TimestampColumn::update(void) {
    value = makeDateTimeString();
}

std::string csv::TimestampColumn::makeDateTimeString(void) {
    std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct std::tm* tm = std::localtime(&tt);

    std::stringstream ss;
    ss << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
