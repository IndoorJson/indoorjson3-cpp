/*
 * File Name: ptr.h
 *
 * Copyright (c) 2023 - 2024 Syrius Robotics
 *
 * Author: Kunlin Yu <yukunlin@syriusrobotics.com>
 * Create Date: 2024/1/6
 *
 */
#pragma once

#include <memory>

#define DEFINE_PTR(type)                   \
  using type##Ptr = std::shared_ptr<type>; \
  using type##WPtr = std::weak_ptr<type>;

#define FORWARD_DEC_WPTR(type) \
  struct type;                 \
  using type##WPtr = std::weak_ptr<type>;
