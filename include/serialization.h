/*
 * File Name: serialization.h
 *
 * Copyright (c) 2023 - 2024 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2024/1/6
 *
 */

#pragma once

#include <geos/geom/Geometry.h>

#include <nlohmann/json.hpp>
#include <vector>

#include "indoor_features.h"
#include "id_lookup.h"

using json = nlohmann::ordered_json;

namespace indoor_json3 {

// feature
void to_json(json &j, const Feature &obj);
void from_json(const json &j, Feature &obj);

// indoor features
void to_json(json &j, const IndoorFeatures &obj);
void from_json(const json &j, IndoorFeatures &obj);

// cell
void to_json(json &j, const Cell &obj);
void from_json(const json &j, Cell &obj);

// connection
void to_json(json &j, const Connection &obj);
void from_json(const json &j, Connection &obj);

// layer
void to_json(json &j, const Layer &obj);
void from_json(const json &j, Layer &obj);

// representative lines
void to_json(json &j, const RLine &obj);
void from_json(const json &j, RLine &obj);
void to_json(json &j, const RLines &obj);
void from_json(const json &j, RLines &obj);

}  // namespace indoor_json3

#include <geos/io/WKTReader.h>
#include <geos/io/WKTWriter.h>

NLOHMANN_JSON_NAMESPACE_BEGIN

using ojson = nlohmann::ordered_json;

template <>
struct adl_serializer<geos::geom::Geometry::Ptr> {
  static void to_json(ojson &j, const geos::geom::Geometry::Ptr &geom) {
    geos::io::WKTWriter writer;
    std::string wkt_str = writer.write(geom.get());
    j = wkt_str;
  }

  static void from_json(const ojson &j, geos::geom::Geometry::Ptr &geom) {
    std::string wkt_str = j.get<std::string>();
    geos::io::WKTReader reader;
    geom = reader.read(wkt_str);
  }
};

template <typename T>
struct adl_serializer<std::shared_ptr<T>> {
  static void to_json(ojson &j, const std::shared_ptr<T> &ptr) {
    indoor_json3::to_json(j, *ptr.get());
  }

  static void from_json(const ojson &j, std::shared_ptr<T> &ptr) {
    ptr = std::make_shared<T>();
    indoor_json3::from_json(j, *ptr.get());

    indoor_json3::IdLookup<T>::Ins().Register(ptr->id, ptr, j);
  }
};

template <typename T>
struct adl_serializer<std::weak_ptr<T>> {
  static void to_json(ojson &j, const std::weak_ptr<T> &wptr) {
    if (auto feature = wptr.lock())
      j = feature->id;
    else
      j = nullptr;
  }

  static void from_json(const ojson &j, std::weak_ptr<T> &wptr) {}
};

NLOHMANN_JSON_NAMESPACE_END