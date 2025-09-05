#pragma once

#include <log/logger.h>

#define TGBM_LOG(FMT_STR, ...) g_Logger.Log(LogLevelFromTGBMStr(FMT_STR), FMT_STR __VA_OPT__(, ) __VA_ARGS__)
