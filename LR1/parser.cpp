#include <string>
#include <vector>
#include "parser.h"


using namespace std;

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
                        vector<string> elements = set_parser(sub_raw);
                        elements = sort(elements);
                        string str ="{ ";
                        for(int i =0; i<elements.size(); i++){
                            str+=elements[i]+", ";
                        }
                        str+="}";
                        buffer.push_back(str);
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
    // 2 случая

    for (int i = 0; i < buffer.size();i++) {
        for (int j = i+1; j < buffer.size() ; j++) {
            if (buffer[i].compare(buffer[j])==0){
                vector<string> err{"error"};
                return err;
            }
        }
    }
    buffer = sort(buffer);
    return buffer;
}

vector<string> sort(vector<string> arr) {
    for(int i = 0; i<arr.size(); i++){
        int num_min=i;
        for(int j=0; j<arr.size(); j++){
            if(arr[j]>arr[num_min]){
                num_min=j;
            }
        }
        swap(arr[i], arr[num_min]);
    }
    return arr;
}
