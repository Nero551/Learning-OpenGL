#pragma once

struct Resource {
  Resource() = default;
  Resource(const Resource &) = delete;
  Resource &operator=(const Resource &) = delete;

  Resource(Resource &&) = default;
  Resource &operator=(Resource &&) = default;

  virtual ~Resource() = default;
};