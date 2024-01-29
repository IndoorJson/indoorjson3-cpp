/*
 * File Name: json.h
 *
 * Copyright (c) 2023 - 2024 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2024/1/29
 *
 */
#pragma once

#ifdef USE_NLOHMANN_FROM_GEOS
  #include <geos/vend/include_nlohmann_json.hpp>
  namespace nlohmann = geos_nlohmann;
  #define NLOHMANN_JSON_NAMESPACE_BEGIN namespace geos_nlohmann {
  #define NLOHMANN_JSON_NAMESPACE_END   }  // namespace geos_nlohmann
#else
  #include <nlohmann/json.hpp>
#endif
