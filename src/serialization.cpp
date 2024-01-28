/*
 * File Name: serialization.cpp
 *
 * Copyright (c) 2023 - 2024 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2024/1/6
 *
 */

#include <serialization.h>

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

namespace indoorjson3 {

// feature
void to_json(json &j, const Feature &obj) {
  j = json::object();
  if (!obj.id.empty()) j.push_back({"$id", obj.id});
  if (!obj.name.empty()) j.push_back({"name", obj.name});
  if (!obj.desc.empty()) j.push_back({"desc", obj.desc});
  if (!obj.ext_ref.empty()) j.push_back({"ext_ref", obj.ext_ref});
  if (!obj.properties.empty()) j.push_back({"properties", obj.properties});
  if (obj.envelope != nullptr)
    j.push_back({"envelope", obj.envelope->toString()});
}

void from_json(const json &j, Feature &obj) {
  if (j.contains("$id")) j.at("$id").get_to(obj.id);
  if (j.contains("name")) j.at("name").get_to(obj.name);
  if (j.contains("description")) j.at("desc").get_to(obj.desc);
  if (j.contains("ext_ref")) j.at("ext_ref").get_to(obj.ext_ref);
  if (j.contains("properties")) j.at("properties").get_to(obj.properties);
  if (j.contains("envelope"))
    obj.envelope.reset(
        new geos::geom::Envelope(j.at("envelope").get<std::string>()));
}

// indoor features
void to_json(json &j, const IndoorFeatures &obj) {
  to_json(j, static_cast<const Feature &>(obj));
  j.update({{"cells", obj.cells},
            {"connections", obj.connections},
            {"layers", obj.layers},
            {"rlineses", obj.rlineses}});
}
void HandleWeakRef(IndoorFeatures &indoor_features);
void from_json(const json &j, IndoorFeatures &obj) {
  from_json(j, static_cast<Feature &>(obj));
  j.at("cells").get_to(obj.cells);
  j.at("connections").get_to(obj.connections);
  j.at("layers").get_to(obj.layers);
  j.at("rlineses").get_to(obj.rlineses);

  HandleWeakRef(obj);
}

// cell
void to_json(json &j, const Cell &obj) {
  to_json(j, static_cast<const Feature &>(obj));
  j.update({{"space", obj.space}, {"node", obj.node}});
}
void from_json(const json &j, Cell &obj) {
  from_json(j, static_cast<Feature &>(obj));
  j.at("space").get_to(obj.space);
  j.at("node").get_to(obj.node);
}

// connection
void to_json(json &j, const Connection &obj) {
  to_json(j, static_cast<const Feature &>(obj));
  j.update({{"fr", obj.fr},
            {"to", obj.to},
            {"bound", obj.bound},
            {"edge", obj.edge}});
}
void from_json(const json &j, Connection &obj) {
  from_json(j, static_cast<Feature &>(obj));
  j.at("fr").get_to(obj.fr);
  j.at("to").get_to(obj.to);
  j.at("bound").get_to(obj.bound);
  j.at("edge").get_to(obj.edge);
}

// layer
void to_json(json &j, const Layer &obj) {
  to_json(j, static_cast<const Feature &>(obj));
  j.update({{"cells", obj.cells}});
}
void from_json(const json &j, Layer &obj) {
  from_json(j, static_cast<Feature &>(obj));
  j.at("cells").get_to(obj.cells);
}

// representative lines
void to_json(json &j, const RLine &obj) {
  j = {{"fr", obj.fr}, {"to", obj.to}};
}
void from_json(const json &j, RLine &obj) {
  j.at("fr").get_to(obj.fr);
  j.at("to").get_to(obj.to);
}
void to_json(json &j, const RLines &obj) {
  to_json(j, static_cast<const Feature &>(obj));
  j.update({{"cell", obj.cell},
            {"ins", obj.ins},
            {"outs", obj.outs},
            {"closure", obj.closure}});
}
void from_json(const json &j, RLines &obj) {
  from_json(j, static_cast<Feature &>(obj));
  j.at("cell").get_to(obj.cell);
  j.at("ins").get_to(obj.ins);
  j.at("outs").get_to(obj.outs);
  j.at("closure").get_to(obj.closure);
}

template <typename T>
std::vector<std::weak_ptr<T>> LookupVectorWeakPtr(json j) {
  std::vector<std::weak_ptr<T>> results;
  for (json j : j) {
    if (j.is_null()) continue;
    auto ptr = IdLookup<T>::Ins().Id2Ptr(j["$ref"].get<std::string>());
    results.push_back(ptr);
  }
  return results;
}

template <typename T>
std::weak_ptr<T> LookupWeakPtr(json j) {
  if (j.is_null()) return std::weak_ptr<T>();
  return IdLookup<T>::Ins().Id2Ptr(j["$ref"].get<std::string>());
}

void HandleWeakRef(IndoorFeatures &indoor_features) {
  for (ConnectionPtr connection : indoor_features.connections) {
    json j = IdLookup<Connection>::Ins().Feature2Json(connection);
    connection->fr = LookupWeakPtr<Cell>(j.at("fr"));
    connection->to = LookupWeakPtr<Cell>(j.at("to"));
  }

  for (LayerPtr layer : indoor_features.layers) {
    json j = IdLookup<Layer>::Ins().Feature2Json(layer);
    layer->cells = LookupVectorWeakPtr<Cell>(j.at("cells"));
  }

  for (RLinesPtr rlines : indoor_features.rlineses) {
    json j = IdLookup<RLines>::Ins().Feature2Json(rlines);
    rlines->cell = LookupWeakPtr<Cell>(j.at("cell"));
    rlines->ins = LookupVectorWeakPtr<Connection>(j.at("ins"));
    rlines->outs = LookupVectorWeakPtr<Connection>(j.at("outs"));
  }

  IdLookupClearAll();
}

}  // namespace indoorjson3
