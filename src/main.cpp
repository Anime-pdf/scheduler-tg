#include <config/json.hpp>
#include <log/logger.h>

#include <tgbm/bot.hpp>
#include <tgbm/logger.hpp>

dd::task<void> coro_main(tgbm::bot& bot) {
    co_foreach(tgbm::api::Update u, bot.updates()) {
        tgbm::api::Message* m = u.get_message();

        if (!m || !m->text)
            continue;

        co_await bot.api.sendMessage({
            .chat_id = m->chat->id,
            .text = *m->text,
        });
    }
}

#define CONFIG_FILE "config.json"

int main() {
    CConfig Config;
    if (!Config.ConfigFileExists(CONFIG_FILE)) {
        switch (Config.CreateTemplateConfig(CONFIG_FILE)) {
            case SUCCESS:
                g_Logger.Log(LogLevel::Info, "'{}' not found, created a template", CONFIG_FILE);
                return 0;
            case ERROR_OPENING_FILE:
                g_Logger.Log(LogLevel::Info, "Can't open '{}' for writing", CONFIG_FILE);
                return 1;
            default:
                g_Logger.Log(LogLevel::Info, "Unknown error");
                return 69;
        }
    }

    if (Config.LoadFromFile(CONFIG_FILE) == ERROR_OPENING_FILE) {
        g_Logger.Log(LogLevel::Info, "Can't open '{}' for reading", CONFIG_FILE);
        return 1;
    }

    g_Logger.Log(LogLevel::Info, "Starting up");

    tgbm::bot bot{Config.Values().m_Token};

    coro_main(bot).start_and_detach();
    bot.run();

    return 0;
}
