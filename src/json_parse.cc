#include <typeinfo>
#include <iostream>
#include <string>
#include <nlohmann/json.hpp>

struct JsonParse
{
    std::string device_id;
    int drive_status;
    double ele;
    double hea;
    double lat;
    double lon;
    bool pos_valid;
    double spd;
    std::string vehicle_num;
    int vehicle_type;
    int vip_status;
    int tag;
};


template<class LambdaFunc>
void recursion(const nlohmann::json& j, LambdaFunc func) {
    for(auto iter = j.begin(); iter != j.end(); ++iter) {
        if (iter->is_structured()) recursion(*iter, func);
        else func(iter);
    }
}

int main() {
    std::cout << "\033[1;33mThis is the example of parsing json from string\033[0m\n"; 
    std::string str("{\"data\":{\"device_id\":\"京A1234\",\"drive_status\":2,\"ele\":18.6,\"hea\":91.8375,\"lat\":31.2824641,\"lon\":121.1649303,\"pos_valid\":true,\"spd\":0.144,\"vehicle_num\":\"京A1234\",\"vehicle_type\":10,\"vip_status\":0},\"tag\":2101}");
    std::cout << "\n\033[1;31mMessage to be parsed:\033[0m\n" << str << std::endl;

    /* Parse string into json format with nlohmann::json::parse() */
    nlohmann::json json = nlohmann::json::parse(str);
    std::cout << "\n\033[1;31mJson format:\033[0m\n" << json.dump(4) << std::endl;

    std::cout << "\n\033[1;31mJson[\"data\"]:\033[0m\n" << json["data"] << std::endl;
    std::cout << "\n\033[1;31mJson.at(\"data\"):\033[0m\n" << json.at("data") << std::endl;
    
    std::cout << "\n\033[1;31mJson[\"data\"][\"device_id\"]:\033[0m\n" << json["data"]["device_id"] << std::endl;
    std::cout << "\n\033[1;31mJson.at(\"data\").at(\"device_id\"):\033[0m\n" << json.at("data").at("device_id") << std::endl;

    /* Looking for value using find(), find() can only search 
    through first layer of the json. Therefore, "lat" would
    NOT be found in this case*/
    std::cout << "\n\033[1;31mFind velue by given key \"lat\":\033[0m\n";
    auto iterator = json.find("lat");
    if (iterator == json.end()) {
        std::cout << "\033[1;33mkey not found\033[0m\n"; 
    } else {
        std::cout << *iterator << std::endl;
    }

    /* Check existance of a key using contains(), contains() 
    can only search through first layer of the json. Therefore, 
    "lat" would NOT be found in this case*/
    std::cout << "\n\033[1;31mCheck if \"lat\" exists:\033[0m\n";
    if (json.contains("lat")) 
        std::cout << "\033[1;33mfound\033[0m\n";
    else 
        std::cout << "\033[1;33mnot found\033[0m\n";

    /* Using recursion to find particular key */
    std::cout << "\n\033[1;31mDo recursion through nesty json:\033[0m\n";
    recursion(json, [](nlohmann::json::const_iterator iter){
        std::cout << iter.key() << ": " << *iter << std::endl;
    });

    JsonParse jp;
    /*******************************************************/
    /* Data decoding from json */
    jp.device_id = json["data"]["device_id"].get<std::string>();
    jp.drive_status = json["data"]["drive_status"].get<int>();

}