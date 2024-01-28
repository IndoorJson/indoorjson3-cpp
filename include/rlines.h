/*
 * File Name: rlines.h
 *
 * Copyright (c) 2023 - 2024 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2024/1/6
 *
 */

#pragma once

#include <geos/geom/Geometry.h>

#include <map>
#include <vector>

#include "cell.h"
#include "connection.h"
#include "feature.h"

namespace indoorjson3 {

struct RLine {
  ConnectionWPtr fr;
  ConnectionWPtr to;
};

struct RLines : Feature {
  CellWPtr cell;
  std::vector<ConnectionWPtr> ins;
  std::vector<ConnectionWPtr> outs;
  std::vector<RLine> closure;
};

DEFINE_PTR(RLines)

}  // namespace indoorjson3