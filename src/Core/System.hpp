#pragma once

struct System {
   virtual ~System() {}

   virtual void Start() {}

   virtual void Update(double dt) {}

   virtual void Stop() {}

   virtual void BeginFrame(double dt) {}

   virtual void EndFrame(double dt) {}
};
