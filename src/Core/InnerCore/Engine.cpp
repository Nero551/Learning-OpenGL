#include "Engine.hpp"

#include <OpenGL.hpp>

#include "../../Modules/Renderer/Renderer.hpp"
#include "../OuterCore/Service.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Physics/Physics.hpp"
#include "Modules/Profiling/Profiling.hpp"

namespace E {
Engine::Engine() : Window(800, 600, "Nova") {
    if (Instance) {
        U::Logger::Fatal("Only one Engine may exist.");
    }
    Instance = this;
}

Engine& Engine::Get() {
    return *Instance;
}

double Engine::GetTime() const {
    return Time;
}

void Engine::Shutdown() {
    Running = false;
}

void Engine::Configure() {
    Window.SetIcon({"Assets/icon.png"});
    // Window.SetSize(1980, 1200);
    glfwSwapInterval(1);

    AddModule<Renderer>();
    AddModule<Input>();
    AddModule<Profiling>();
    AddModule<Physics>();

    Service::Add<ResourceManager>();
    Service::Add<EventBus>();
}

void Engine::Run() {
    double accumulator = 0;
    Running = true;

    Start();
    while (Running) {
        BeginFrame();

        accumulator += DeltaTime;
        accumulator = std::min(accumulator, 0.25);

        while (accumulator >= FixedDeltaTime) {
            FixedUpdate();
            accumulator -= FixedDeltaTime;
        }

        Update();
        Render();
        EndFrame();
    }
    Stop();
}

void Engine::Start() {
    Configure();

    World.Start();

    for (auto& module : Modules | std::views::values) {
        module->Start();
    }

    for (auto& service : Service::GetAll()) {
        service->Start();
    }
}

void Engine::BeginFrame() {
    Time = glfwGetTime();
    Window.PollEvents();

    World.BeginFrame(DeltaTime);
    for (auto& module : Modules | std::views::values) {
        module->BeginFrame(DeltaTime);
    }

    for (auto& service : Service::GetAll()) {
        service->BeginFrame(DeltaTime);
    }
}

void Engine::FixedUpdate() {
    World.FixedUpdate(FixedDeltaTime);
    for (auto& module : Modules | std::views::values) {
        module->FixedUpdate(FixedDeltaTime);
    }

    for (auto& service : Service::GetAll()) {
        service->FixedUpdate(FixedDeltaTime);
    }
}

void Engine::Update() {
    World.Update(DeltaTime);

    for (auto& module : Modules | std::views::values) {
        module->Update(DeltaTime);
    }

    for (auto& service : Service::GetAll()) {
        service->Update(DeltaTime);
    }
}

void Engine::Render() {
    for (auto& module : Modules | std::views::values) {
        module->Render();
    }

    for (auto& service : Service::GetAll()) {
        service->Render();
    }
}

void Engine::EndFrame() {
    Window.SwapBuffers();

    const double currentFrame = Time;
    DeltaTime = currentFrame - LastFrame;
    LastFrame = currentFrame;

    World.EndFrame(DeltaTime);
    for (auto& module : Modules | std::views::values) {
        module->EndFrame(DeltaTime);
    }

    for (auto& service : Service::GetAll()) {
        service->EndFrame();
    }
}

void Engine::Stop() {
    World.Stop();
    for (auto& module : Modules | std::views::values) {
        module->Stop();
    }

    for (auto& service : Service::GetAll()) {
        service->Stop();
    }

    Service::DestroyServices();

    if (Instance == this) {
        Instance.Reset();
    }
}
} // namespace E
