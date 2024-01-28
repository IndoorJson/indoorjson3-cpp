/*
 * File Name: indoor_features.h
 *
 * Copyright (c) 2023 - 2024 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2024/1/6
 *
 */
#pragma once

#include <vector>

#include "cell.h"
#include "connection.h"
#include "layer.h"
#include "rlines.h"

namespace indoorjson3 {

struct IndoorFeatures : Feature {
  std::vector<CellPtr> cells;
  std::vector<ConnectionPtr> connections;
  std::vector<LayerPtr> layers;
  std::vector<RLinesPtr> rlineses;
};

DEFINE_PTR(IndoorFeatures)

}  // namespace indoorjson3
