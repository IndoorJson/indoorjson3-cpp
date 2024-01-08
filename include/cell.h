/*
 * File Name: cell.h
 *
 * Copyright (c) 2023 - 2024 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2024/1/6
 *
 */

#pragma once

#include <geos/geom/Geometry.h>

#include "feature.h"

namespace indoor_json3 {

struct Cell : Feature {
  geos::geom::Geometry::Ptr space;
  geos::geom::Geometry::Ptr node;
};

DEFINE_PTR(Cell)

}  // namespace indoor_json3