#include "World.hpp"
#include "Engine.hpp"
#include "Modules/Input/Keys.hpp"
#include "Modules/Renderer/Entities/Camera.hpp"

#include <cmath>

Scene &World::CreateScene(const std::string &name) {
  std::unique_ptr<Scene> &scene = Scenes.emplace_back(std::make_unique<Scene>(name));
  return *scene;
}

void World::SetActiveScene(Scene &scene) { ActiveScene = &scene; }

void World::Start() {
  Scene &scene = CreateScene("First Scene");

  Camera &camera = scene.CreateEntity<Camera>();
  camera.cameraComponent.AspectRatio = 800.0f / 600.0f;
  scene.SetActiveCamera(camera);
  SetActiveScene(scene);

  // TODO- camera will be an entity inside the scene
}

constexpr float cameraSpeed = 5;
bool firstMouse = true;
float lastX = 800 / 2;
float lastY = 600 / 2;

void World::Update(double dt) {

  auto &camera = *ActiveScene->ActiveCamera;
  auto &transform = camera.transformComponent;
  auto &inputModule = Engine::Instance->ModuleStore.InputModule;

  if (firstMouse) {
    lastX = inputModule.MousePosition.x;
    lastY = inputModule.MousePosition.y;
    firstMouse = false;
  }

  float xOffset = inputModule.MousePosition.x - lastX;
  float yOffset = lastY - inputModule.MousePosition.y;

  xOffset *= camera.cameraComponent.Sensitivity;
  yOffset *= camera.cameraComponent.Sensitivity;
  xOffset = Math::DegToRad(xOffset);
  yOffset = Math::DegToRad(yOffset);

  lastX = inputModule.MousePosition.x;
  lastY = inputModule.MousePosition.y;

  const float maxPitch = Math::DegToRad(89.0f);

  transform.EulerRotation.y += xOffset;
  transform.EulerRotation.x += yOffset;
  transform.EulerRotation.x = transform.EulerRotation.x > maxPitch ? maxPitch : transform.EulerRotation.x;
  transform.EulerRotation.x = transform.EulerRotation.x < -maxPitch ? -maxPitch : transform.EulerRotation.x;

  Vector3 direction;
  direction.x = std::cos(transform.EulerRotation.y) * std::cos(transform.EulerRotation.x);
  direction.y = std::sin(transform.EulerRotation.x);
  direction.z = std::sin(transform.EulerRotation.y) * std::cos(transform.EulerRotation.x);

  transform.Forward = direction.Normalized();

  if (inputModule.IsKeyDown(Key::W)) {
    transform.Position += cameraSpeed * dt * transform.Forward;
  }

  if (inputModule.IsKeyDown(Key::S)) {
    transform.Position -= cameraSpeed * dt * transform.Forward;
  }

  if (inputModule.IsKeyDown(Key::A)) {
    transform.Position += cameraSpeed * dt * transform.GetRight();
  }

  if (inputModule.IsKeyDown(Key::D)) {
    transform.Position -= cameraSpeed * dt * transform.GetRight();
  }

  if (inputModule.IsKeyDown(Key::Space)) {
    transform.Position += cameraSpeed * dt * Vector3(0, 1, 0);
  }

  if (inputModule.IsKeyDown(Key::LeftShift)) {
    transform.Position -= cameraSpeed * dt * Vector3(0, 1, 0);
  }
}

void World::Stop() {}