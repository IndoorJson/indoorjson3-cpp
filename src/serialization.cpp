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

using json = nlohmann::json;

namespace indoor_json3 {

// feature
void to_json(json &j, const Feature &obj) {
  if (!obj.id.empty()) j.push_back({"$id", obj.id});
  if (!obj.name.empty()) j.push_back({"name", obj.name});
  if (!obj.desc.empty()) j.push_back({"desc", obj.desc});
  if (!obj.ext_ref.empty()) j.push_back({"ext_ref", obj.ext_ref});
  if (obj.envelope != nullptr)
    j.push_back({"envelope", obj.envelope->toString()});
}

void from_json(const json &j, Feature &obj) {
  if (j.contains("$id")) j.at("$id").get_to(obj.id);
  if (j.contains("name")) j.at("name").get_to(obj.name);
  if (j.contains("description")) j.at("desc").get_to(obj.desc);
  if (j.contains("ext_ref")) j.at("ext_ref").get_to(obj.ext_ref);
  if (j.contains("envelope"))
    obj.envelope.reset(
        new geos::geom::Envelope(j.at("envelope").get<std::string>()));
}

// properties
void to_json(json &j, const Prop &obj) {}
void from_json(const json &j, Prop &obj) {}

// indoor features
void to_json(json &j, const IndoorFeatures &obj) {
  j = {{"cells", obj.cells},
       {"connections", obj.connections},
       {"layers", obj.layers},
       {"rlineses", obj.rlineses}};
  to_json(j, static_cast<const Feature &>(obj));
}
void from_json(const json &j, IndoorFeatures &obj) {
  j.at("cells").get_to(obj.cells);
  j.at("connections").get_to(obj.connections);
  j.at("layers").get_to(obj.layers);
  j.at("rlineses").get_to(obj.rlineses);
  from_json(j, static_cast<Feature &>(obj));
}

// cell
void to_json(json &j, const Cell &obj) {
  j = {{"space", obj.space}, {"point", obj.point}};
  to_json(j, static_cast<const Feature &>(obj));
}
void from_json(const json &j, Cell &obj) {
  j.at("space").get_to(obj.space);
  j.at("point").get_to(obj.point);
  from_json(j, static_cast<Feature &>(obj));
}

// connection
void to_json(json &j, const Connection &obj) {
  j = {{"fr", obj.fr},
       {"to", obj.to},
       {"bound", obj.bound},
       {"curve", obj.curve}};
  to_json(j, static_cast<const Feature &>(obj));
}
void from_json(const json &j, Connection &obj) {
  j.at("fr").get_to(obj.fr);
  j.at("to").get_to(obj.to);
  j.at("bound").get_to(obj.bound);
  j.at("curve").get_to(obj.curve);
  from_json(j, static_cast<Feature &>(obj));
}

// layer
void to_json(json &j, const Layer &obj) {
  j = {{"cells", obj.cells}};
  to_json(j, static_cast<const Feature &>(obj));
}
void from_json(const json &j, Layer &obj) {
  j.at("cells").get_to(obj.cells);
  from_json(j, static_cast<Feature &>(obj));
}

// representative lines
void to_json(json &j, const RLine &obj) {
  j = {{"fr", obj.fr},
       {"to", obj.to}};
}
void from_json(const json &j, RLine &obj) {
  j.at("fr").get_to(obj.fr);
  j.at("to").get_to(obj.to);
}
void to_json(json &j, const RLines &obj) {
  j = {{"cell", obj.cell},
       {"in", obj.in},
       {"out", obj.out},
       {"closure", obj.closure}
  };
  to_json(j, static_cast<const Feature &>(obj));
}
void from_json(const json &j, RLines &obj) {
  j.at("cell").get_to(obj.cell);
  j.at("in").get_to(obj.in);
  j.at("out").get_to(obj.out);
  j.at("closure").get_to(obj.closure);
  from_json(j, static_cast<Feature &>(obj));
}

}  // namespace indoor_json3