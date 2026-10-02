#ifndef JSON_STORE_H
#define JSON_STORE_H

#include <string>
#include <fstream>

class JsonStore {
public:
    static bool saveMagazine(const std::string& id, const std::string& author, const std::string& msg, const std::string& imgUrl) {
        std::ofstream file("wwwroot/magazine_data.json");
        if (!file.is_open()) return false;

        file << "{\n";
        file << "  \"id\": \"" << id << "\",\n";
        file << "  \"author\": \"" << author << "\",\n";
        file << "  \"message\": \"" << msg << "\",\n";
        file << "  \"imageUrl\": \"" << imgUrl << "\"\n";
        file << "}\n";

        file.close();
        return true;
    }
};

#endif // JSON_STORE_H