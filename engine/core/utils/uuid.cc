// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#include "core/utils/uuid.h"

#include <random>
#include <unordered_map>

static std::random_device random_device;
static std::mt19937_64 engine(random_device());
static std::uniform_int_distribution<uint64_t> uniform_distribution;

UUID::UUID() : uuid_(uniform_distribution(engine)) {}

UUID::UUID(uint64_t uuid) : uuid_(uuid) {}
