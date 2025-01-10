#include "Uri.h"
#include <cassert>
#include <iostream>
#include <regex>
#include <sstream>
#include <string>

std::ostream &operator<<(std::ostream &os, const Component &component) {
    os << "{ name: \"" << component.name
       << "\", isDynamic: " << (component.isDynamic ? "true" : "false") << " }";
    return os;
}

std::vector<Component> parseFormat(const std::string &format) {
    std::vector<Component> components;
    std::regex segmentRegex(R"(/(\{?(\w+)\}?))"); // Regex to match each segment
    std::sregex_iterator it(format.begin(), format.end(), segmentRegex);
    std::sregex_iterator end;

    while (it != end) {
        std::smatch match = *it;
        std::string segment = match[1];
        std::string name = match[2];

        // Determine if the segment is dynamic (wrapped in `{}`)
        bool is_dynamic = segment.front() == '{' && segment.back() == '}';

        // Add the component to the result
        components.push_back({name, is_dynamic});

        ++it;
    }

    return components;
}

struct ParsedUri {
    std::vector<std::string> path_segments;
    std::map<std::string, std::string> query_params;
};

ParsedUri parseUri(const std::string &uri) {
    ParsedUri result;

    // Split the URI into path and query parts
    size_t query_start = uri.find('?');
    std::string path = uri.substr(0, query_start);
    std::string query =
        query_start != std::string::npos ? uri.substr(query_start + 1) : "";

    // Parse path segments
    std::regex pathRegex(R"(/([^/?]+))"); // Match path segments between slashes
    auto path_begin = std::sregex_iterator(path.begin(), path.end(), pathRegex);
    auto path_end = std::sregex_iterator();
    for (auto it = path_begin; it != path_end; ++it) {
        result.path_segments.push_back((*it)[1].str());
    }

    // Parse query parameters
    std::regex queryRegex(R"(([^&=]+)=([^&=]+))"); // Match key=value pairs
    auto query_begin =
        std::sregex_iterator(query.begin(), query.end(), queryRegex);
    auto query_end = std::sregex_iterator();
    for (auto it = query_begin; it != query_end; ++it) {
        std::string key = (*it)[1].str();
        std::string value = (*it)[2].str();
        result.query_params[key] = value;
    }

    return result;
}

Uri::Uri() { Uri("/"); }

Uri::Uri(const std::string &uri) {
    m_uri = uri;
    components = parseFormat(uri);
}

bool Uri::canParse(const std::string &uri) {
    ParsedUri parsedUri = parseUri(uri);

    if (components.size() != parsedUri.path_segments.size()) {
        return false;
    }

    for (size_t i = 0; i < components.size(); i++) {
        if (components[i].isDynamic) {
            continue;
        }
        if (components[i].name != parsedUri.path_segments[i]) {
            return false;
        }
    }

    return true;
}

std::unique_ptr<std::map<std::string, std::string>>
Uri::parseDynamicComponents(const std::string &uri) {
    ParsedUri parsedUri = parseUri(uri);
    std::unique_ptr<std::map<std::string, std::string>> dynamicComponents =
        std::make_unique<std::map<std::string, std::string>>();

    for (size_t i = 0; i < components.size(); i++) {
        if (components[i].isDynamic) {
            dynamicComponents->insert(
                {components[i].name, parsedUri.path_segments[i]});
        }
    }

    return dynamicComponents;
}

std::unique_ptr<std::map<std::string, std::string>>
Uri::parseFilters(const std::string &uri) {
    ParsedUri parsedUri = parseUri(uri);
    std::unique_ptr<std::map<std::string, std::string>> filters =
        std::make_unique<std::map<std::string, std::string>>();

    filters->insert(parsedUri.query_params.begin(),
                    parsedUri.query_params.end());

    return filters;
}

std::unique_ptr<std::string>
Uri::buildTarget(std::map<std::string, std::string> &dynamicComponents,
                 std::map<std::string, std::string> &filters) {

    std::vector<std::string> formattedComponents;

    for (Component &component : components) {
        // Static components can just be filled in by their name
        if (!component.isDynamic) {
            formattedComponents.push_back(component.name);
        } else {
            // Dynamic components are replaced by their value in
            // dynamicComponents
            assert(dynamicComponents.find(component.name) !=
                   dynamicComponents.end());
            formattedComponents.push_back(dynamicComponents[component.name]);
        }
    }

    // Format the components
    std::stringstream target;

    for (std::string &component : formattedComponents) {
        target << "/" << component;
    }

    // If no filters, we can just output the target directly
    if (filters.size() != 0) {
        // If there are filters first add a '?'
        target << "?";

        // Then for each filter format it as name=value
        bool firstFilter = true;
        for (auto it : filters) {
            // Add an & between filters (i.e. before all but the first filter)
            if (!firstFilter) {
                target << "&";
            }
            firstFilter = false;

            target << it.first << "=" << it.second;
        }
    }

    return std::make_unique<std::string>(target.str());
}
