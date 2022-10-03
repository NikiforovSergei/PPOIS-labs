#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*!
 * \brief parses an input string to a shape of a multiset {elem1, elem2, ..., elemN}
 *        (can include sets)
 * \param raw - input string of shape {elem1, elem2, ..., elemN}
 * \return vector of elements of multiset
 */
vector<string> set_parser(string raw){
    vector<string> buffer;
    if (raw[0] == '{'){
        for (int element = 1; element < raw.size(); element++){
            if (element== raw.size()-1 && raw[element] == '}')
                break;
            if (raw[element] == '{' or (raw[element] >= '0' and raw[element] <= '9' and raw[element+1] == '{')){
                for (int idx = element; idx < raw.size(); idx++){
                    if (raw[idx + 1] == '}'){
                        string sub_raw = raw.substr(element, idx + 2 - element);
                        buffer.push_back(sub_raw);
                        element = idx + 1;
                        break;
                    }
                }
            }
            else if (raw[element] != ',' and raw[element] != ' '){
                if (raw[element + 1] != ',' and raw[element+1] != ' ' and raw[element+1] != '}'){
                    string elem;
                    for (int idx = element; idx < raw.size(); idx++){
                        if (raw[idx + 1] != ',' and raw[idx+1] != ' ' and raw[idx+1] != '}'){
                            elem.push_back(raw[idx]);
                        }
                        else {
                            elem.push_back(raw[idx]);
                            element = idx + 1;
                            break;
                        }
                    }
                    buffer.push_back(elem);
                }
                else{
                    string new_str;
                    new_str.push_back(raw[element]);
                    buffer.push_back(new_str);
                }
            }
        }
    }
    return buffer;
}
