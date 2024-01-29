/*
 * File Name: test_create.cpp
 *
 * Copyright (c) 2023 - 2024 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2024/1/6
 *
 */

#include <cell.h>
#include <connection.h>
#include <geos/io/WKTReader.h>
#include <glog/logging.h>
#include <indoor_features.h>
#include <serialization.h>

#include <memory>
#include <vector>

#include "test_entry.h"

using namespace indoorjson3;

TEST(INDOORJSON3, CREATE) {
  IndoorFeatures indoor_features;
  geos::io::WKTReader reader;

  CellPtr c1 = std::make_shared<Cell>();
  c1->id = "c1";
  c1->space = reader.read("POLYGON((0 0, 1 0, 1 1, 0 1, 0 0))");
  c1->node = reader.read("POINT(0.5 0.5)");
  c1->properties = json::parse(R"({"roomNumber": "1101"})");
  indoor_features.cells.emplace_back(c1);

  CellPtr c2 = std::make_shared<Cell>();
  c2->id = "c2";
  c2->space = reader.read("POLYGON((1 0, 2 0, 2 1, 1 1, 1 0))");
  c2->node = reader.read("POINT(1.5 0.5)");
  c2->properties = json::parse(R"({"roomNumber": "1102"})");
  indoor_features.cells.emplace_back(c2);

  CellPtr c3 = std::make_shared<Cell>();
  c3->id = "c3";
  c3->space = reader.read("POLYGON((0 1, 1 1, 1 2, 0 2, 0 1))");
  c3->node = reader.read("POINT(0.5 1.5)");
  c3->properties = json::parse(R"({"roomNumber": "1103"})");
  indoor_features.cells.emplace_back(c3);

  ConnectionPtr conn12 = std::make_shared<Connection>();
  conn12->id = "conn1-2";
  conn12->fr = c1;
  conn12->to = c2;
  conn12->bound = reader.read("LINESTRING (1 0, 1 1)");
  conn12->edge = reader.read("LINESTRING (0.5 0.5, 1.5 0.5)");
  conn12->properties = json::parse(
      R"({"type": "door", "开放时间": "全天", "오픈 시간": "하루 종일"})");
  indoor_features.connections.emplace_back(conn12);

  ConnectionPtr conn31 = std::make_shared<Connection>();
  conn31->id = "conn3-1";
  conn31->fr = c3;
  conn31->to = c1;
  conn31->bound = reader.read("LINESTRING (1 0, 1 1)");
  conn31->edge = reader.read("LINESTRING (0.5 0.5, 1.5 0.5)");
  conn31->properties = json::parse(R"({"type": "window"})");
  indoor_features.connections.emplace_back(conn31);

  LayerPtr layer = std::make_shared<Layer>();
  layer->id = "layer";
  layer->cells.emplace_back(c1);
  layer->cells.emplace_back(c2);
  indoor_features.layers.emplace_back(layer);

  RLinesPtr rlines = std::make_shared<RLines>();
  rlines->id = "rlines1";
  rlines->cell = c1;
  rlines->ins.emplace_back(conn31);
  rlines->outs.emplace_back(conn12);
  indoor_features.rlineses.emplace_back(rlines);

  indoor_features.properties = json::parse(
      R"({"name": "indoorjson3-cpp",
          "labels": ["indoorgml", "GIS"],
          "language": ["English", "中文", "한국어"],
          "author":{"name":"Kunlin Yu", "email":"yukunlin@syriusrobotics.com"}})");

  json j;
  to_json(j, indoor_features);
  LOG(INFO) << j.dump(2);

  EXPECT_EQ(1, 1);
}
