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
  camera.GetComponent<CameraComponent>().AspectRatio = 800.0f / 600.0f;
  scene.SetActiveCamera(camera);
  SetActiveScene(scene);
}

constexpr float cameraSpeed = 5;
bool firstMouse = true;
float lastX = 800 / 2;
float lastY = 600 / 2;

void World::Update(double dt) {

  auto &inputModule = Engine::Instance->ModuleStore.InputModule;
  auto &camera = *ActiveScene->ActiveCamera;
  auto &transform = camera.GetComponent<TransformComponent>();
  auto &cameraComponent = camera.GetComponent<CameraComponent>();

  if (firstMouse) {
    lastX = inputModule.MousePosition.x;
    lastY = inputModule.MousePosition.y;
    firstMouse = false;
  }

  float xOffset = inputModule.MousePosition.x - lastX;
  float yOffset = lastY - inputModule.MousePosition.y;

  xOffset = Math::DegToRad(xOffset);
  yOffset = Math::DegToRad(yOffset);
  xOffset *= cameraComponent.Sensitivity;
  yOffset *= cameraComponent.Sensitivity;

  lastX = inputModule.MousePosition.x;
  lastY = inputModule.MousePosition.y;

  const float maxPitch = Math::DegToRad(89.0f);

  transform.EulerRotation.y += xOffset;
  transform.EulerRotation.x += yOffset;
  transform.EulerRotation.x = std::clamp(transform.EulerRotation.x, -maxPitch, maxPitch);

  if (inputModule.IsKeyDown(Key::W)) {
    transform.Position += cameraSpeed * dt * transform.GetForward();
  }

  if (inputModule.IsKeyDown(Key::S)) {
    transform.Position -= cameraSpeed * dt * transform.GetForward();
  }

  if (inputModule.IsKeyDown(Key::A)) {
    transform.Position -= cameraSpeed * dt * transform.GetRight();
  }

  if (inputModule.IsKeyDown(Key::D)) {
    transform.Position += cameraSpeed * dt * transform.GetRight();
  }

  if (inputModule.IsKeyDown(Key::Space)) {
    transform.Position += cameraSpeed * dt * Vector3(0, 1, 0);
  }

  if (inputModule.IsKeyDown(Key::LeftShift)) {
    transform.Position -= cameraSpeed * dt * Vector3(0, 1, 0);
  }
}

void World::Stop() {}