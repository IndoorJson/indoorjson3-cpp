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

namespace indoor_json3 {

struct Connection : Feature {
  CellWPtr fr;
  CellWPtr to;
  geos::geom::Geometry::Ptr bound;
  geos::geom::Geometry::Ptr curve;
};

DEFINE_PTR(Connection)

}  // namespace indoor_json3