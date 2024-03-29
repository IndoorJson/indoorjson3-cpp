/*
 * File Name: connection.h
 *
 * Copyright (c) 2023 - 2024 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2024/1/6
 *
 */

#pragma once

#include <geos/geom/Geometry.h>

#include "ptr.h"
#include "feature.h"
#include "cell.h"

namespace indoorjson3 {

struct Connection : Feature {
  CellWPtr fr;
  CellWPtr to;
  geos::geom::Geometry::Ptr bound;
  geos::geom::Geometry::Ptr edge;
};

DEFINE_PTR(Connection)

}  // namespace indoorjson3