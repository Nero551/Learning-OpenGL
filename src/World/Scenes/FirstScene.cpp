#include "FirstScene.hpp"

#include "Modules/Input/Input.hpp"
#include "Modules/Input/Keys.hpp"
#include "Modules/Renderer/Entities/Cube.hpp"
#include "Modules/Renderer/Entities/Light.hpp"
#include "../../Modules/Renderer/Primitives/Primitives.hpp"
#include "Modules/Renderer/Uniforms/Vector3Uniform.hpp"

unsigned int lightId;

void FirstScene::Initialize() {
   {
      auto &resourceManager = Engine::Ins->ResourceManager;
      Camera &camera = CreateEntity<Camera>();
      camera.GetComponent<CameraComponent>().AspectRatio = Engine::Ins->Window.Width / Engine::Ins->Window.Height;
      ActiveCamera = &camera;

      auto &mesh = Primitives::CreateCube("mesh");

      auto &objectShader = resourceManager.Load<Shader>("shader", "Assets/Shaders/shader.frag", "Assets/Shaders/shader.vert");

      auto &diffuseMap = resourceManager.Load<Texture>("diffuseMap", "Assets/Images/diffuseMap.png");
      auto &specularMap = resourceManager.Load<Texture>("specularMap", "Assets/Images/specularMap.png");
      auto &objectMaterial = resourceManager.Load<Material>("material");
      objectMaterial.Shader = &objectShader;
      objectMaterial.DiffuseMap = &diffuseMap;
      objectMaterial.SpecularMap = &specularMap;

      for (float i = 0; i < 6; i += 0.5) {
         Cube &cube = CreateEntity<Cube>();
         cube.GetComponent<MaterialComponent>().Material = &objectMaterial;
         cube.GetComponent<MeshComponent>().Mesh = &mesh;
         cube.GetComponent<TransformComponent>().Position = {std::cos(i) * 5, 0, std::sin(i) * 5};
      }

      auto &lightShader = resourceManager.Load<Shader>("lightShader", "Assets/Shaders/lightShader.frag",
         "Assets/Shaders/lightShader.vert");

      auto &lightMaterial = resourceManager.Load<Material>("lightMaterial");
      lightMaterial.Shader = &lightShader;


      Light &light = CreateEntity<Light>();
      light.GetComponent<MaterialComponent>().Material = &lightMaterial;
      light.GetComponent<MeshComponent>().Mesh = &mesh;

      light.GetComponent<TransformComponent>().Position = {1.2, 1, 2};
      light.GetComponent<TransformComponent>().Scale = {0.2};

      light.GetComponent<LightComponent>().Ambient = {0.3};
      light.GetComponent<TransformComponent>().EulerRotation = {Math::Radians(90), 0, 0};
      light.GetComponent<LightComponent>().Type = LightType::Spot;

      lightId = light.Id; //Temporary
   }
}

void FirstScene::Update(double dt) {
   Light &light = GetEntity<Light>(lightId);
   auto &transformComponent = light.GetComponent<TransformComponent>();
   auto &input = Engine::Ins->GetModule<Input>();

   if (input.IsKeyHeld(Key::Up)) {
      transformComponent.Position.z += 2 * dt;
   }
   if (input.IsKeyHeld(Key::Down)) {
      transformComponent.Position.z -= 2 * dt;
   }
   if (input.IsKeyHeld(Key::Left)) {
      transformComponent.Position.x -= 2 * dt;
   }
   if (input.IsKeyHeld(Key::Right)) {
      transformComponent.Position.x += 2 * dt;
   }

   if (input.IsKeyHeld(Key::I)) {
      transformComponent.Position.y += 2 * dt;
   }
   if (input.IsKeyHeld(Key::O)) {
      transformComponent.Position.y -= 2 * dt;
   }

   if (input.IsKeyHeld(Key::Z)) {
      transformComponent.EulerRotation.x += 2 * dt;
   }

   if (input.IsKeyHeld(Key::X)) {
      transformComponent.EulerRotation.y += 2 * dt;
   }

   if (input.IsKeyHeld(Key::C)) {
      transformComponent.EulerRotation.z += 2 * dt;

   }
}
