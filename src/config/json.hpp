#ifndef CONFIG_JSON_HPP
#define CONFIG_JSON_HPP

#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <string>
#include <nlohmann/json.hpp>

namespace fs = std::filesystem;

struct Config {
    std::string token;

    void validate() const {
        if (token.empty() || token == "NONE") {
            throw std::runtime_error("Invalid token in config");
        }
    }

    static Config defaults() {
        return Config{
            .token = "NONE"
        };
    }
};

NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Config, token)

class ConfigLoader {
public:
    static Config load_or_create(const fs::path &path) {
        if (!fs::exists(path)) {
            create_default(path);
            throw std::runtime_error(
                "Config file created at '" + path.string() +
                "'. Please edit it and restart."
            );
        }

        return load(path);
    }

    static Config load(const fs::path &path) {
        std::ifstream file(path);
        if (!file) {
            throw std::runtime_error("Cannot open config file: " + path.string());
        }

        nlohmann::json j;
        try {
            file >> j;
        } catch (const nlohmann::json::exception &e) {
            throw std::runtime_error("Invalid JSON in config: " + std::string(e.what()));
        }

        Config cfg = j.get<Config>();

        if (auto *env_token = std::getenv("BOT_TOKEN")) {
            cfg.token = env_token;
        }

        cfg.validate();
        return cfg;
    }

    static void create_default(const fs::path &path) {
        std::ofstream file(path);
        if (!file) {
            throw std::runtime_error("Cannot create config file: " + path.string());
        }

        nlohmann::json j = Config::defaults();
        file << j.dump(4) << '\n';
    }
};

#endif // CONFIG_JSON_HPP
