/*
 * File Name: test_create.cpp
 *
 * Copyright (c) 2023 - 2024 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2024/1/6
 *
 */

#include <geos/io/WKTReader.h>
#include <glog/logging.h>
#include <indoorjson3.h>
#include <serialization.h>

#include "test_entry.h"

using namespace indoor_json3;
using nlohmann::json;

TEST(INDOORJSON3, CREATE) {
  indoor_json3::IndoorFeatures indoor_features;
  geos::io::WKTReader reader;

  CellPtr c1;
  c1.reset(new Cell());
  c1->id = "c1";
  c1->space = reader.read("POLYGON((0 0, 1 0, 1 1, 0 1, 0 0))");
  c1->point = reader.read("POINT(0.5 0.5)");
  indoor_features.cells.emplace_back(c1);

  CellPtr c2;
  c2.reset(new Cell());
  c2->id = "c2";
  c2->space = reader.read("POLYGON((1 0, 2 0, 2 1, 1 1, 1 0))");
  c2->point = reader.read("POINT(1.5 0.5)");
  indoor_features.cells.emplace_back(c2);

  ConnectionPtr conn;
  conn.reset(new Connection());
  conn->id = "conn1-2";
  conn->fr = c1;
  conn->to = c2;
  conn->bound = reader.read("LINESTRING (1 0, 1 1)");
  conn->curve = reader.read("LINESTRING (0.5 0.5, 1.5 0.5)");
  indoor_features.connections.emplace_back(conn);

  LayerPtr layer;
  layer.reset(new Layer());
  layer->id = "layer";
  layer->cells.emplace_back(c1);
  layer->cells.emplace_back(c2);
  indoor_features.layers.emplace_back(layer);

  json j;
  to_json(j, indoor_features);
  LOG(INFO) << j.dump(2);

  EXPECT_EQ(1, 1);
}