/*
 * File Name: factory.h
 *
 * Copyright (c) 2023 - 2024 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2024/1/7
 *
 */

#pragma once

#include <geos/geom/Factory.h>
#include <geos/geom/Geometry.h>

#include "indoor_features.h"

namespace indoor_json3 {

class Factory {
 private:
  geos::geom::GeometryFactory::Ptr factory_;

 public:
  Factory() { factory_ = geos::geom::GeometryFactory::create(); }

  CellPtr createCell(const std::string& space_wkt);
  CellPtr createCell(const std::string& space_wkt,
                     const std::string& point_wkt);
  CellPtr createCell(const geos::geom::Geometry::Ptr& space);
  CellPtr createCell(const geos::geom::Geometry::Ptr& space,
                     const geos::geom::Geometry::Ptr& point);

  ConnectionPtr createConnection(const CellPtr& c_fr, const CellPtr& c_to);

  LayerPtr createLayer(const std::vector<CellPtr> cells);

  RLinesPtr createRLines();
};

}  // namespace indoor_json3