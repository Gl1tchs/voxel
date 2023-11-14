// Copyright (c) 2023 Berke Umut Biricik All Rights Reserved

#pragma once

#include <cstdint>

class UUID {
 public:
  UUID();
  UUID(uint64_t uuid);
  UUID(const UUID&) = default;

  operator uint64_t() const { return uuid_; }

 private:
  uint64_t uuid_;
};

namespace std {
template <typename T>
struct hash;

template <>
struct hash<UUID> {
  size_t operator()(const UUID& uuid) const { return (uint64_t)uuid; }
};

}  // namespace std
