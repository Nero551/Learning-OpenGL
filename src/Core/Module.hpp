#pragma once

struct Module {
  virtual void Start() {}
  virtual void Update(double dt) {}
  virtual void Stop() {}
  virtual void Render() {}
  virtual ~Module() {}
};