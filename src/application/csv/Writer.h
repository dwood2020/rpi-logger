/*
 * Copyright (C) 2024  David Woodward
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once
#include <filesystem>
#include <functional>
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
        std::vector<std::shared_ptr<ColumnBase>> columns;
        std::filesystem::path basePath;
        std::string filename = "out";
        std::string fileExtension = ".csv";
        std::filesystem::path fullPath;
        char delimiter = ';';
        int writtenLines = 0;

    public:
        static constexpr int maxLinesPerFile = 100000;

        Writer(std::initializer_list<std::shared_ptr<ColumnBase>> columns, const std::filesystem::path& outputDir);
        Writer(const std::filesystem::path& outputDir);
        virtual ~Writer() = default;

        void setFilename(const std::string& filename);
        void setDelimiter(char delimiter);
        void addColumn(std::shared_ptr<Column> column);

        void initialize(void);
        void writeLine(void);

    private:
        void findFullPath(void);
        void writeLine(std::function<std::string(std::shared_ptr<ColumnBase>)> func);
        void writeLineToFile(const std::string& line);
    };
}
