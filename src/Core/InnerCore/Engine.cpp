#include "Engine.hpp"

#include <OpenGL.hpp>

#include "../OuterCore/ServiceStore.hpp"
#include "../../Modules/Renderer/Renderer.hpp"
#include "Core/Services/ResourceManager.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Profiling/Profiling.hpp"

Engine::Engine() : Window(1000, 800, "Plus Ultra") {
    Running = true;
}

CheckedPtr<Engine> Engine::Ins;

void Engine::AddModules() {
    AddModule<Renderer>();
    AddModule<Input>();
    AddModule<Profiling>();
}


void Engine::AddServices() {
    ServiceStore::Ins->Add<ResourceManager>();
    ServiceStore::Ins->Add<EventBus>();
}


void Engine::Start() {
    // glfwSwapInterval(0);
    AddServices();
    AddModules();

    World.Start();

    for (auto& module : Modules | std::views::values) {
        module->Start();
    }

    GetModule<Input>().SetMouseMode(MouseMode::Disabled);
}


void Engine::Update() {
    Time = glfwGetTime();

    ServiceStore::Ins->Get<EventBus>().EmptyFireQueue();

    World.Update(DeltaTime);

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

    for (auto& module : Modules | std::views::values) {
        module->Update(DeltaTime);
    }
}

void Engine::FixedUpdate() {
    World.FixedUpdate(FixedDeltaTime);
    for (auto& module : Modules | std::views::values) {
        module->FixedUpdate(FixedDeltaTime);
    }
}

void Engine::Stop() {
    World.Stop();
    for (auto& module : Modules | std::views::values) {
        module->Stop();
    }

    glfwTerminate();
}

void Engine::Render() {
    for (auto& module : Modules | std::views::values) {
        module->Render();
    }
}

void Engine::BeginFrame() {
    Window.PollEvents();
    glClearColor(0.025, 0.0125, 0.025, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    World.BeginFrame(DeltaTime);
    for (auto& module : Modules | std::views::values) {
        module->BeginFrame(DeltaTime);
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
}
