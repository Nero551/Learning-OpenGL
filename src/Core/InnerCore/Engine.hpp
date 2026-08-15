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
template <typename T>
concept ModuleType = std::derived_from<T, Module>;

/**
 * @brief Represents the program's main engine and game loop.
 *
 * There is only one Engine instance per program.
 * The Engine manages the main loop, frame scheduling, registered modules,
 * the active World, and the application's Window.
 *
 * The Engine is neither copyable nor movable.
 */
struct Engine {
    Window Window;
    World World;

    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    Engine(Engine&&) = delete;
    Engine& operator=(Engine&&) = delete;

    /**
     * @brief Performs global initialization and creates the engine.
     *
     * Calls PreInit() before constructing the Engine instance.
     *
     * @return The newly created Engine instance.
     */
    static Engine Create();

    /**
     * @brief Returns the global engine instance.
     *
     * @return Reference to the current Engine instance.
     */
    static Engine& Get();

    /**
     * @brief Runs the engine's main loop.
     *
     * The loop continues until Shutdown() is called. Once the running
     * state becomes false, the main loop exits and Stop() is called to
     * perform engine cleanup.
     */
    void Run();

    /**
     * @brief Requests the engine to shut down.
     *
     * Sets the running state to false, causing the main loop to exit.
     * Cleanup is performed by Stop() after the main loop terminates.
     *
     * @note This method does not perform cleanup directly.
     */
    void Shutdown();

    /**
     * @brief Returns the total elapsed engine time.
     *
     * @return Elapsed engine time in seconds.
     */
    double GetTime() const;

    /**
     * @brief Retrieves a registered module by its type.
     *
     * @tparam T Type of the module to retrieve.
     * @return Reference to the requested module.
     *
     * @note The engine crashes if the requested module is not registered.
     */
    template <ModuleType T> T& GetModule() {
        auto module = Modules.find(typeid(T));
        if (module == Modules.end()) {
            U::Logger::Fatal(std::format("Module {} not found", typeid(T).name()));
        }
        return static_cast<T&>(*module->second);
    }

private:
    /** @brief Pointer to the global Engine instance. */
    inline static U::CheckedPtr<Engine> Instance = nullptr;

    /** @brief Collection of modules registered with the engine. */
    std::unordered_map<std::type_index, std::unique_ptr<Module>> Modules;

    /** @brief Time at which the previous frame began, in seconds. */
    double LastFrame = 0;

    /** @brief Whether the engine's main loop is currently running. */
    bool Running = false;

    /** @brief Total elapsed engine time in seconds. */
    double Time = 0;

    /** @brief Duration of the previous frame in seconds. */
    double DeltaTime = 0;

    /** @brief Fixed timestep used by FixedUpdate(), in seconds. */
    double FixedDeltaTime = 1.0 / 60.0;

    /**
     * @brief Configures the engine after global initialization.
     *
     * Initializes the engine's modules and other runtime systems.
     */
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

    /**
     * @brief Performs global initialization required before creating an Engine.
     *
     * Initializes systems that must exist before an Engine instance is
     * constructed, such as GLFW.
     *
     * @note Must be called before creating an Engine instance.
     */
    static void PreInit();

    /**
     * @brief Constructs the Engine instance.
     * Registers the newly constructed object as the global Engine instance.
     */
    Engine();

    /**
     * @brief Start step
     *
     * called at the beginning of the main loop. executes services,modules & world's Start method
     */
    void Start();

    /**
     * @brief Stop & cleanup step.
     *
     * Called after the main loop exits to clean up engine services,
     * modules & world. runs their Stop method as well.
     *
     * @note This is the cleanup stage of the shutdown sequence.
     * Shutdown() only requests that the engine stop running.
     */
    void Stop();

    /**
    * @brief Beginning of frame step
    *
    * executes services,modules & world's BeginFrame method using the current
    * frame's DeltaTime.
    */
    void BeginFrame();

    /**
     * @brief End of frame step
     *
     * executes services,modules & world's EndFrame method using the current
     * frame's DeltaTime.
     */
    void EndFrame();

    /**
     * @brief Update step
     *
     * executes services,modules & world's Update method using the current
     * frame's DeltaTime.
     */
    void Update();

    /**
     * @brief Fixed step
     * executes services,modules & world's FixedUpdate method with deterministic timestep processing
     * using FixedDeltaTime.
     */
    void FixedUpdate();

    /**
     * @brief Render step.
     * calls services,modules & world's render method.
     */
    void Render();
};
}
