#pragma once

#include <log/logger.h>

#define TGBM_LOG(TYPE, FMT_STR, ...) g_Logger.Log(LogLevelFromTGBMStr(#TYPE), FMT_STR __VA_OPT__(, ) __VA_ARGS__)
