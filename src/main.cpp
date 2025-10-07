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
    Config cfg;
    try {
        cfg = ConfigLoader::load_or_create(CONFIG_FILE);
    } catch (const std::exception& e) {
        g_Logger.Log(LogLevel::Error, "Config error: {}", e.what());
        return 1;
    }
    g_Logger.Log(LogLevel::Info, "Starting up");
    tgbm::bot bot{cfg.token};

    coro_main(bot).start_and_detach();
    bot.run();

    return 0;
}
