#include "Column.h"

csv::Column::Column(const std::string& name): name(name) {
    value.reserve(32);
}

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
        this->value = false;
    }
}

std::string csv::Column::valueAsString(void) {
    return std::move(value);
}

std::string csv::Column::getName(void) {
    return std::move(name);
}
