#include "Engine.hpp"

#include <OpenGL.hpp>
#include <ranges>

#include "../OuterCore/ServiceStore.hpp"
#include "../../Modules/Renderer/Renderer.hpp"
#include "Modules/Input/Input.hpp"
#include "Modules/Profiling/Profiling.hpp"

Engine::Engine() : Window(1000, 800, "Plus Ultra") { Running = true; }

SafePtr<Engine> Engine::Ins;

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
    ServiceStore services;
    ServiceStore::Ins = &services;
    AddServices();

    // glfwSwapInterval(0);
    AddModules();

    for (auto& module : Modules | std::views::values) { module->Start(); }

    World.Start();

    GetModule<Input>().SetMouseMode(MouseMode::Disabled);
}


void Engine::Update() {
    Time = glfwGetTime();
    World.Update(DeltaTime);

    if (GetModule<Input>().IsKeyHeld(Key::Escape)) {
        Running = false;
        Window.Close();
    }

    if (GetModule<Input>().IsKeyReleased(Key::Q)) {
        if (GetModule<Input>().GetMouseMode() == MouseMode::Disabled) {
            GetModule<Input>().SetMouseMode(MouseMode::Normal);
        }
        else { GetModule<Input>().SetMouseMode(MouseMode::Disabled); }
    }

    for (auto& module : Modules | std::views::values) { module->Update(DeltaTime); }
}

void Engine::Stop() {
    World.Stop();
    for (auto& module : Modules | std::views::values) { module->Stop(); }

    glfwTerminate();
}

void Engine::Render() { for (auto& module : Modules | std::views::values) { module->Render(); } }

void Engine::BeginFrame() {
    Window.PollEvents();
    glClearColor(0.025, 0.0125, 0.025, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    World.BeginFrame(DeltaTime);
    for (auto& module : Modules | std::views::values) { module->BeginFrame(DeltaTime); }
}

void Engine::EndFrame() {
    const float currentFrame = Time;
    DeltaTime = currentFrame - LastFrame;
    LastFrame = currentFrame;
    Window.SwapBuffers();

    World.EndFrame(DeltaTime);
    for (auto& module : Modules | std::views::values) { module->EndFrame(DeltaTime); }
}
