module;

export module Module;

export struct Module {
  virtual void Start() {}
  virtual void Update(double dt) {}
  virtual void Stop() {}
  virtual ~Module() {}
};