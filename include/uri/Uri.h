#include <map>
#include <string>

/**
 * @brief A Uri is a resource identified. It looks like '/game/{gameId}'
 * purpose of this class is to represent and parse URIs
 * Each string between the '/'s is called a component. in this case 'game' is a
 * static component, and gameId is a dynamic component.
 *
 */
struct Component {
    std::string name;
    bool isDynamic;
};

std::ostream &operator<<(std::ostream &os, const Component &component);

class Uri {
  private:
    std::string m_uri;
    std::vector<Component> components;

  public:
    /**
     * @brief Creates a uri from a string + verb.
     *  The string should be formatted as /games/{gameId} (no trailing
     * backslash) Components surrounded by {} are considered dynamic (i.e
     * gameId), while normal components are considered static (i.e. the game)
     *
     */
    Uri(const std::string &format);

    /**
     * @brief Default constructor to make this easier to work with. Leaves the
     * object in an undefined state.
     *
     */
    Uri();

    /**
     * @brief Parses the dynamic components of a uri, returning a map of
     * component name -> component value.
     * Assumes that we can parse the given uri.
     */
    std::unique_ptr<std::map<std::string, std::string>>
    parseDynamicComponents(const std::string &uri);

    /**
     * @brief Uris can also contain filters (for example /games?sort=AllTime)
     * This parses out the filters and returns them as a map from name->string
     *
     * @param uri
     * @return std::unique_ptr<std::map<std::string, std::string>>
     */
    std::unique_ptr<std::map<std::string, std::string>>
    parseFilters(const std::string &uri);

    /**
     * @brief Constructs target using the given dynamic components and filters.
     * For the sake of consistency, filters are guarunteed to be added
     * in alphabetical order.
     */
    std::unique_ptr<std::string>
    buildTarget(std::map<std::string, std::string> &dynamicComponents,
                std::map<std::string, std::string> &filters);

    /**
     * @brief Determines whether the given string can be parsed as this URI.
     *
     */
    bool canParse(const std::string &uri);
};
