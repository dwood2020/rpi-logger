#pragma once
#include <filesystem>
#include <initializer_list>
#include <memory>
#include <vector>
#include "Column.h"


namespace csv {

    /**
     * CSV write handler.
    */
    class Writer {
    private:
        std::vector<std::shared_ptr<Column>> columns;
        std::filesystem::path basePath;
        std::string filename = "out";
        std::string fileExtension = "csv";
        std::filesystem::path fullPath;
        char delimiter = ';';
        int writtenLines = 0;

    public:
        Writer(std::initializer_list<std::shared_ptr<Column>> columns, std::string_view outputDir);
        virtual ~Writer() = default;

        void setFilename(const std::string& filename);
        void setFileExtension(const std::string& fileExtension);
        void setDelimiter(char delimiter);

        void initialize(void);
        void writeLine(void);

    private:
        void findFullPath(void);
        void writeFirstLine(void);
        void writeLineToFile(const std::string& line);
    };
}
