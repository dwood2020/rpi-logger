#pragma once
#include <string>


namespace csv {

    class ColumnBase {
    protected:
        std::string name;
        std::string value;

    public:
        ColumnBase(const std::string& name);
        virtual ~ColumnBase() = default;

        std::string getName(void);
        std::string valueAsString(void);
    };


    /**
     * Standard CSV Column class, used for logging.
    */
    class Column : public ColumnBase {
    public:
        Column(const std::string& name);
        virtual ~Column() = default;

        void logValue(int value);
        void logValue(unsigned int value);
        void logValue(float value);
        void logValue(const std::string& value);
        void logValue(bool value);
        void logNA(void);
    };


    class TimestampColumn : public ColumnBase {
    public:
        TimestampColumn(): ColumnBase("Timestamp") {}
        virtual ~TimestampColumn() = default;

        void update(void);

    private:
        std::string makeDateTimeString(void);
    };
}
