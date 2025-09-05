#ifndef CONFIG_JSON_HPP
#define CONFIG_JSON_HPP

#include <fstream>
#include <nlohmann/json.hpp>

struct SConfig {
    std::string m_Token = "NONE";
};

void to_json(nlohmann::json& j, const SConfig& c) {
    j = nlohmann::json{
                {"token", c.m_Token},
            };
}

void from_json(const nlohmann::json& j, SConfig& c) {
    j.at("token").get_to(c.m_Token);
}

enum EConfigResultCode {
    // common
    SUCCESS = 0,
    ERROR_OPENING_FILE,

    // create
    FILE_EXISTS,

    // load
    FILE_NOT_EXISTS,
};

class CConfig final {
    SConfig m_Config;

public:
    CConfig() = default;

    bool ConfigFileExists(const char *pPath) {
        return std::filesystem::exists(pPath);
    }

    EConfigResultCode CreateTemplateConfig(const char *pPath) {
        if (ConfigFileExists(pPath)) {
            return FILE_EXISTS;
        }

        std::ofstream FileStream(pPath);
        if (!FileStream.is_open()) {
            return ERROR_OPENING_FILE;
        }

        FileStream << nlohmann::json(m_Config).dump(4);
        return SUCCESS;
    }

    EConfigResultCode LoadFromFile(const char *pPath) {
        if (!ConfigFileExists(pPath)) {
            return FILE_NOT_EXISTS;
        }

        std::ifstream FileStream(pPath);
        if (!FileStream.is_open()) {
            return ERROR_OPENING_FILE;
        }

        nlohmann::json Data = nlohmann::json::parse(FileStream);
        m_Config = Data.template get<SConfig>();

        return SUCCESS;
    }

    [[nodiscard]] SConfig Values() const { return m_Config; }
};

#endif // CONFIG_JSON_HPP
