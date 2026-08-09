#include "Engine.hpp"

#include <OpenGL.hpp>

#include "../../Modules/Renderer/Renderer.hpp"
#include "../OuterCore/Service.hpp"
#include "Core/Services/DirtyManager.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Physics/Physics.hpp"
#include "Modules/Profiling/Profiling.hpp"

namespace E {
Engine::Engine() : Window(800, 600, "Plus Ultra") {
    Running = true;
    Ins = this;
}

void Engine::Configure() {
    Window.SetIcon({"Assets/icon.png"});
    // Window.SetSize(1980, 1200);
    glfwSwapInterval(0);

    AddModule<Renderer>();
    AddModule<Input>();
    AddModule<Profiling>();
    AddModule<Physics>();

    Service::Add<ResourceManager>();
    Service::Add<EventBus>();
    Service::Add<DirtyManager>();
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

    GetModule<Input>().SetMouseMode(MouseMode::Disabled);
}


void Engine::Update() {
    Time = glfwGetTime();

    World.Update(DeltaTime);

    for (auto& module : Modules | std::views::values) {
        module->Update(DeltaTime);
    }

    for (auto& service : Service::GetAll()) {
        service->Update(DeltaTime);
    }

    if (GetModule<Input>().IsKeyHeld(Key::Escape)) {
        Running = false;
        Window.Close();
    }

    if (GetModule<Input>().IsKeyReleased(Key::Q)) {
        if (GetModule<Input>().GetMouseMode() == MouseMode::Disabled) {
            GetModule<Input>().SetMouseMode(MouseMode::Normal);
        }
        else {
            GetModule<Input>().SetMouseMode(MouseMode::Disabled);
        }
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

void Engine::Stop() {
    World.Stop();
    for (auto& module : Modules | std::views::values) {
        module->Stop();
    }

    for (auto& service : Service::GetAll()) {
        service->Stop();
    }

    glfwTerminate();
}

void Engine::Render() {
    for (auto& module : Modules | std::views::values) {
        module->Render();
    }

    for (auto& service : Service::GetAll()) {
        service->Render();
    }
}

void Engine::BeginFrame() {
    Window.PollEvents();

    World.BeginFrame(DeltaTime);
    for (auto& module : Modules | std::views::values) {
        module->BeginFrame(DeltaTime);
    }

    for (auto& service : Service::GetAll()) {
        service->BeginFrame(DeltaTime);
    }
}

void Engine::EndFrame() {
    const double currentFrame = Time;
    DeltaTime = currentFrame - LastFrame;
    LastFrame = currentFrame;
    Window.SwapBuffers();

    World.EndFrame(DeltaTime);
    for (auto& module : Modules | std::views::values) {
        module->EndFrame(DeltaTime);
    }

    for (auto& service : Service::GetAll()) {
        service->EndFrame();
    }
}
}
