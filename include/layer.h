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

#include "feature.h"
#include "cell.h"

namespace indoor_json3 {

struct Layer : Feature {
  std::vector<CellWPtr> cells;
};

DEFINE_PTR(Layer)

}  // namespace indoor_json3