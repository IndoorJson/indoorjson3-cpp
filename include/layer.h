/*
 * File Name: layer.h
 *
 * Copyright (c) 2023 - 2024 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2024/1/6
 *
 */
#pragma once

#include <vector>
#include "feature.h"
#include "cell.h"
#include "ptr.h"

namespace indoorjson3 {

/*
 * If you need to create a thematic layer, then do this:
 *
 * indoorjson3::Layer thematic_layer;
 * thematic_layer.properties["theme"] = "Topographic";
 *
 */

struct Layer : Feature {
  std::vector<CellWPtr> cells;
};

DEFINE_PTR(Layer)

}  // namespace indoorjson3