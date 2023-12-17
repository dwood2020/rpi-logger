#include "Writer.h"
#include <chrono>
#include <exception>
#include <fstream>
#include <sstream>


csv::Writer::Writer(std::initializer_list<std::shared_ptr<ColumnBase>> columns, const std::filesystem::path& outputDir): 
basePath(outputDir) {
    if (!std::filesystem::exists(basePath)) {
        throw std::invalid_argument("Directory does not exist");
    }

    this->columns.push_back(std::make_shared<TimestampColumn>());
    this->columns.insert(this->columns.end(), columns);
}

csv::Writer::Writer(const std::filesystem::path& outputDir): Writer({}, outputDir) {}

void csv::Writer::setFilename(const std::string& filename) {
    this->filename = filename;
}

void csv::Writer::setFileExtension(const std::string& fileExtension) {
    this->fileExtension = fileExtension;
}

void csv::Writer::setDelimiter(char delimiter) {
    this->delimiter = delimiter;
}

void csv::Writer::addColumn(std::shared_ptr<Column> column) {
    columns.push_back(column);
}

void csv::Writer::initialize(void) {
    findFullPath();
    std::ofstream ofs(fullPath, std::ios::out |  std::ios::trunc);
    ofs.close();
    writeLine([](std::shared_ptr<ColumnBase> col) {
        return col->getName();
    });
}

void csv::Writer::writeLine(void) {
    std::dynamic_pointer_cast<csv::TimestampColumn>(columns[0])->update();

    writeLine([](std::shared_ptr<ColumnBase> col) {
        return col->valueAsString();
    });
}


void csv::Writer::findFullPath(void) {
    std::filesystem::path fullPath = basePath;
    fullPath = fullPath / std::filesystem::path(filename);
    std::filesystem::path fullPathExt = fullPath;
    fullPathExt.concat(fileExtension);
    int i = 0;
    while (std::filesystem::exists(fullPathExt)) {
        i++;
        fullPathExt = fullPath;
        fullPathExt.concat("#" + std::to_string(i));
        fullPathExt.concat(fileExtension);
    }
    this->fullPath = fullPathExt;
}

void csv::Writer::writeLine(std::function<std::string(std::shared_ptr<ColumnBase>)> func) {
    std::stringstream ss;
    for (unsigned int i = 0; i < columns.size() - 1; i++) {
        ss << func(columns[i]) << delimiter << " ";
    }
    ss << func(columns.back()) << " \n";
    writeLineToFile(ss.str());
}

void csv::Writer::writeLineToFile(const std::string& line) {
    std::ofstream ofs(fullPath, std::ios::out |  std::ios::app);
    if (ofs.is_open()) {
        ofs << line;
        ofs.close();
    }
}
