/*
 * File Name: test_create.cpp
 *
 * Copyright (c) 2023 - 2024 IndoorJson
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2024/1/6
 *
 */
#include <glog/logging.h>
#include <indoor_features.h>
#include <indoorjson3.h>
#include <serialization.h>

#include <fstream>
#include <iosfwd>
#include <iterator>
#include <memory>
#include <string>
#include <vector>

#include "test_entry.h"

using namespace indoorjson3;

TEST(INDOORJSON3, DESERIALIZATION) {
  std::string file_path = TEST_RESOURCES "/sample.json";
  LOG(INFO) << file_path;

  std::ifstream fin(file_path);

  ASSERT_TRUE(fin.is_open());

  std::string content((std::istreambuf_iterator<char>(fin)),
                      std::istreambuf_iterator<char>());

  fin.close();

  try {
    json j = json::parse(content);
    LOG(INFO) << "parse to json dom";

    auto indoor_features = j.get<IndoorFeatures>();

    LOG(INFO) << indoor_features.cells[0]->id;
    EXPECT_EQ(indoor_features.cells[0]->id, "c1");
    LOG(INFO) << indoor_features.properties.dump(2);

    json j2 = indoor_features;
    LOG(INFO) << j2.dump(2);
    std::string json_deserialized = j2.dump(2);
    EXPECT_EQ(content, json_deserialized);

  } catch (json::exception &e) {
    LOG(ERROR) << "parse error: " << e.what();
  }
}
