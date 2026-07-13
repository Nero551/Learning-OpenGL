# Framework Overview

## Architecture

The engine is organized into a simple hierarchy:

```text
Main
└── Engine
    ├── Modules
    │   ├── Systems
    │   └── ...
    └── World
        └── Scenes
            └── Entities
                └── Components
```

## Main

The application's entry point.

Its only responsibility is to create and run the `Engine`.

---

## Engine

The central object of the framework.

It owns and updates:

* The **World**
* All **Modules**

The engine is responsible for driving the application's lifecycle (startup, update loop, rendering, shutdown).

---

## Modules

Modules are large, self-contained parts of the engine.

Examples include:

* Renderer
* Input
* Physics
* Audio
* Networking

Each module owns one or more **Systems**.
The module handles the lifecycle of all related **Systems**.

It can also contain **Resources**, premade **Entities** & **Components**

---

## Systems

Systems contain behavior and logic.

They perform work every frame, either independently or by operating on entities and their components.

Examples include:

* Camera System
* Animation System

---

## World

The world owns every scene in the application.

It is responsible for creating, storing, and switching between scenes.

---

## Scenes

A scene represents a collection of entities.

Each scene owns:

* Entities
* Scene-specific state (such as the active camera)

A scene can also contain logic. such as setting up and spawning
its entities, etc.

---

## Entities

Entities are lightweight objects.

An entity is simply:

* A unique ID
* A collection of components

Entities contain no game logic.

---

## Components

Components are pure data blocks.

They describe an entity's properties without containing behavior.

Examples include:

* TransformComponent
* MeshComponent
* MaterialComponent
* CameraComponent
* LightComponent

Systems read and modify component data to produce behavior.

---

## Design Philosophy

The framework follows a data-oriented, component-based architecture:

* **Modules** organize major engine features.
* **Systems** implement behavior.
* **Worlds** manage scenes.
* **Scenes** manage entities.
* **Entities** group components.
* **Components** store data only.

This separation keeps data independent of behavior while making systems reusable and easy to extend.