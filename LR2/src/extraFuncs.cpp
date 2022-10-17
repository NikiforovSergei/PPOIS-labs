#include <vector>
#include <string>

/**
 * @brief delete all chars in str from left side
 * 
 * @param str 
 * @param chars for deleting
 * @return std::string& 
 */
std::string& leftTrim(std::string& str, const std::string chars)
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

/**
 * @brief split string line using delimiter
 * 
 * @param line 
 * @param delimiter 
 * @return std::vector<std::string> 
 */
std::vector<std::string> split(std::string line, std::string delimiter)
{
    leftTrim(line, " ");
    size_t pos = 0;
    std::vector<std::string> entityDescription;
    while ( (pos = line.find(delimiter)) != std::string::npos)
    {
        entityDescription.push_back(line.substr(0, pos));
        line.erase(0, pos + delimiter.length());
    }
    if (!line.empty())
        entityDescription.push_back(line);

    return entityDescription;
}