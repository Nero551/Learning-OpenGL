#pragma once
#include "Module.hpp"
#include "Window.hpp"
#include "World.hpp"
#include "Utilities/CheckedPtr.hpp"

/**
 * @namespace E
 * @brief Root namespace containing all Nova engine functionality.
 */
namespace E {
template <typename T>concept ModuleType = std::derived_from<T, Module>;

/**
 * @brief Represents the program's main loop, there is only 1 engine per program (singleton).
 * manages scheduling (FixedUpdate, Update,Render) and
 * stores modules, world & window
 */
struct Engine {
    Window Window;
    World World;

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    /** @brief runs PreInit() and creates an engine object */
    static Engine Create();

    /**
    * @brief Returns the global engine instance.
    */
    static Engine& Get();
    void Run();

    double GetTime() const;

    /**
    * @brief Retrieves a registered module by its type.
    *
    @tparam T Type of the module to retrieve.
    * @return Reference to the requested module.
    *
    * @note The engine terminates if the requested module is not registered.
    */
    template <ModuleType T> T& GetModule() {
        auto module = Modules.find(typeid(T));
        if (module == Modules.end()) {
            U::Logger::Fatal(std::format("Module {} not found", typeid(T).name()));
        }
        return static_cast<T&>(*module->second);
    }

private:
    inline static U::CheckedPtr<Engine> Instance = nullptr;
    std::unordered_map<std::type_index, std::unique_ptr<Module>> Modules;
    double LastFrame = 0;
    bool Running = false;

    /** Total elapsed engine time in seconds. */
    double Time = 0;

    /** Duration of the previous frame in seconds. */
    double DeltaTime = 0;

    /** Fixed timestep used by FixedUpdate, in seconds. */
    double FixedDeltaTime = 1.0 / 60.0;

    void Configure();

    /**
    * @brief Creates and registers a module.
    *
    * @tparam T Type of the module to create.
    * @return Reference to the newly registered module.
    */
    template <ModuleType T> T& AddModule() {
        auto module = std::make_unique<T>();
        Modules.emplace(typeid(T), std::move(module));
        return static_cast<T&>(*Modules.find(typeid(T))->second);
    }

    /** @brief Runs before the creation of the engine. MUST be called before creating an engine instance
    * includes things such as glfwInit()
    */
    static void PreInit();
    Engine();

    void Start();

    void Stop();

    void BeginFrame();

    void EndFrame();

    void Update();

    void FixedUpdate();

    void Render();
};
}
