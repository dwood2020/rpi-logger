#pragma once
#include <string>


namespace csv {

    /**
     * CSV Column class.
    */
    class Column {
    private:
        std::string name;
        std::string value;

    public:
        Column(const std::string& name);
        virtual ~Column() = default;

        void logValue(int value);
        void logValue(unsigned int value);
        void logValue(float value);
        void logValue(const std::string& value);
        void logValue(bool value);

        std::string getName(void);
        std::string valueAsString(void);
    };

}
