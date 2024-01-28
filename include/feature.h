/*
 * File Name: feature.h
 *
 * Copyright (c) 2023 - 2024 Syrius Robotics
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2024/1/6
 *
 */
#pragma once

#include <geos/geom/Envelope.h>
#include <geos/geom/Point.h>
#include <nlohmann/json.hpp>

#include <string>

#include "ptr.h"

namespace indoorjson3 {

struct Feature {
  std::string id;
  std::string name;
  std::string desc;
  std::string ext_ref;
  geos::geom::Envelope::Ptr envelope;
  nlohmann::ordered_json properties;
};

DEFINE_PTR(Feature)

}  // namespace indoorjson3
