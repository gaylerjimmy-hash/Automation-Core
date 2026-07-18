#include "automation_core/Protocol/Parser.h"

#include <array>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace automation_core {
namespace {

std::vector<std::string> split_lines(const std::string& payload) {
    std::vector<std::string> lines;
    std::istringstream stream(payload);
    std::string line;

    while (std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        lines.push_back(std::move(line));
    }

    return lines;
}

ParseResult failure(ParseError error, std::string detail) {
    return {std::nullopt, error, std::move(detail)};
}

} // namespace

ParseResult Parser::parse(const Frame& frame) const {
    if (frame.payload.empty()) {
        return failure(ParseError::EmptyFrame, "Frame payload is empty.");
    }

    const auto lines = split_lines(frame.payload);

    if (lines.empty() || lines.front().empty()) {
        return failure(ParseError::EmptyFrame, "Message type is missing.");
    }

    if (lines.front() != "HELLO") {
        return failure(
            ParseError::UnknownMessageType,
            "Unsupported message type: " + lines.front()
        );
    }

    const std::array<std::string, 6> required_fields{
        "MSG", "TYPE", "ID", "FW", "PROTO", "SESSION"
    };

    const std::unordered_set<std::string> allowed_fields{
        required_fields.begin(), required_fields.end()
    };

    std::unordered_map<std::string, std::string> fields;
    bool found_end = false;

    for (std::size_t index = 1; index < lines.size(); ++index) {
        const std::string& line = lines[index];

        if (line == "END") {
            found_end = true;

            for (std::size_t trailing = index + 1;
                 trailing < lines.size();
                 ++trailing) {
                if (!lines[trailing].empty()) {
                    return failure(
                        ParseError::TrailingData,
                        "Data appears after END."
                    );
                }
            }

            break;
        }

        if (line.empty()) {
            return failure(
                ParseError::MalformedField,
                "Blank lines are not allowed inside a message."
            );
        }

        const auto separator = line.find('=');

        if (separator == std::string::npos ||
            separator == 0 ||
            separator == line.size() - 1 ||
            line.find('=', separator + 1) != std::string::npos) {
            return failure(
                ParseError::MalformedField,
                "Malformed field: " + line
            );
        }

        const std::string key = line.substr(0, separator);
        const std::string value = line.substr(separator + 1);

        if (allowed_fields.find(key) == allowed_fields.end()) {
            return failure(
                ParseError::UnknownField,
                "Unknown field: " + key
            );
        }

        if (value.empty()) {
            return failure(
                ParseError::EmptyValue,
                "Field has an empty value: " + key
            );
        }

        if (!fields.emplace(key, value).second) {
            return failure(
                ParseError::DuplicateField,
                "Duplicate field: " + key
            );
        }
    }

    if (!found_end) {
        return failure(
            ParseError::MissingTerminator,
            "Message is missing END."
        );
    }

    for (const auto& key : required_fields) {
        if (fields.find(key) == fields.end()) {
            return failure(
                ParseError::MissingField,
                "Missing required field: " + key
            );
        }
    }

    HelloMessage hello{
        fields.at("MSG"),
        fields.at("TYPE"),
        fields.at("ID"),
        fields.at("FW"),
        fields.at("PROTO"),
        fields.at("SESSION")
    };

    return {
        Message{std::move(hello)},
        ParseError::None,
        {}
    };
}

} // namespace automation_core
