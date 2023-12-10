#include "Writer.h"
#include <exception>
#include <fstream>
#include <sstream>


csv::Writer::Writer(std::initializer_list<std::shared_ptr<Column>> columns, std::string_view outputDir): columns(columns), basePath(outputDir) {
    if (!std::filesystem::exists(basePath)) {
        throw std::invalid_argument("Directory does not exist");
    }
}

void csv::Writer::setFilename(const std::string& filename) {
    this->filename = filename;
}

void csv::Writer::setFileExtension(const std::string& fileExtension) {
    this->fileExtension = fileExtension;
}

void csv::Writer::setDelimiter(char delimiter) {
    this->delimiter = delimiter;
}

void csv::Writer::initialize(void) {
    findFullPath();
    std::ofstream ofs(fullPath, std::ios::out |  std::ios::trunc);
    ofs.close();
    writeFirstLine();
}

void csv::Writer::writeLine(void) {
    std::stringstream ss;
    for (unsigned int i = 0; i < columns.size() - 1; i++) {
        ss << columns[i]->valueAsString() << " " << delimiter;
    }
    ss << columns.back()->valueAsString() << " \n";
    writeLineToFile(ss.str());
}

void csv::Writer::findFullPath(void) {
    std::filesystem::path fullPath = basePath;
    fullPath.concat(filename);
    fullPath.concat("." + fileExtension);
    std::filesystem::path fullPathExt = fullPath;
    int i = 1;
    while (std::filesystem::exists(fullPathExt)) {
        fullPathExt = fullPath;
        fullPathExt.concat("#" + std::to_string(i));
        fullPathExt.concat("." + fileExtension);
    }
    this->fullPath = fullPathExt;
}

void csv::Writer::writeFirstLine(void) {
    std::stringstream ss;
    for (unsigned int i = 0; i < columns.size() - 1; i++) {
        ss << columns[i]->getName() << " " << delimiter;
    }
    ss << columns.back()->getName() << " \n";
    writeLineToFile(ss.str());
}

void csv::Writer::writeLineToFile(const std::string& line) {
    std::ofstream ofs(fullPath, std::ios::out |  std::ios::app);
    if (ofs.is_open()) {
        ofs << line;
        ofs.close();
    }
}
