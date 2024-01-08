/*
 * File Name: id_lookup.cpp
 *
 * Copyright (c) 2023 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2023/12/20
 *
 */

#include <id_lookup.h>

#include <indoor_features.h>
#include <cell.h>
#include <connection.h>
#include <layer.h>
#include <rlines.h>

namespace indoor_json3 {

template <>
IdLookup<Cell>* IdLookup<Cell>::instance_ = nullptr;
template <>
IdLookup<Connection>* IdLookup<Connection>::instance_ = nullptr;
template <>
IdLookup<Layer>* IdLookup<Layer>::instance_ = nullptr;
template <>
IdLookup<RLines>* IdLookup<RLines>::instance_ = nullptr;

void IdLookupClearAll() {
  IdLookup<Cell>::Ins().Clear();
  IdLookup<Connection>::Ins().Clear();
  IdLookup<Layer>::Ins().Clear();
  IdLookup<RLines>::Ins().Clear();
}

}  // namespace indoor_json