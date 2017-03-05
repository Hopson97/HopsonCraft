#ifndef CONFIG_PARSER_H
#define CONFIG_PARSER_H

#include <istream>
#include <vector>
#include <string>
#include <stdexcept>

class ConfigParser
{
    public:
        // Create an empty parser
        ConfigParser();

        // Parse the istream, appending to the existing data.
        // The filename is used for error detection.
        void parse(std::string const& filename, std::istream&);

        // Check whether the current line is of a certain type, or that we have
        // reached the end of the file.
        bool atHeader() const;
        bool atKVP() const;
        bool atEnd() const;

        // Get the current line, assuming it is a header or KVP respectively.
        std::string getHeader();
        std::pair<std::string, std::string> getKVP();

        // Throw a parse error.
        [[noreturn]]
        void error(std::string);

    private:
        void parseLine(std::string line, std::string const& filename, int line_no);

        struct Line
        {
            std::string filename;
            int line_no;
            std::string data;
            std::string extra_data;
            bool is_header = false;
        };

        std::vector<Line> m_lines;
        size_t m_position;
};

struct ParseError : std::runtime_error
{
	ParseError(std::string err, std::string file, int line)
    : std::runtime_error(std::move(err)), m_file(std::move(file)), m_line(line)
	{}

	char const* what() const noexcept override;

    private:
        std::string m_file;
        int m_line;

        // This member is needed to implement what.
        mutable std::string m_err_msg;
};

#endif
