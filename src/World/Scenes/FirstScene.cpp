#include "FirstScene.hpp"

#include "Modules/Input/Input.hpp"
#include "Modules/Input/Keys.hpp"
#include "Modules/Renderer/Entities/Cube.hpp"
#include "Modules/Renderer/Entities/Light.hpp"
#include "../../Modules/Renderer/Primitives/Primitives.hpp"
#include "Modules/Renderer/Uniforms/Vector3Uniform.hpp"

unsigned int lightId;
unsigned int cubeId;

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

      Cube &cube = CreateEntity<Cube>();
      cube.GetComponent<MaterialComponent>().Material = &objectMaterial;
      cube.GetComponent<MeshComponent>().Mesh = &mesh;

      cubeId = cube.Id; //Temporary

      auto &lightShader = resourceManager.Load<Shader>("lightShader", "Assets/Shaders/lightShader.frag",
         "Assets/Shaders/lightShader.vert");

      auto &lightMaterial = resourceManager.Load<Material>("lightMaterial");
      lightMaterial.Shader = &lightShader;
      lightMaterial.Diffuse = {5};

      Light &light = CreateEntity<Light>();
      light.GetComponent<MaterialComponent>().Material = &lightMaterial;
      light.GetComponent<MeshComponent>().Mesh = &mesh;

      light.GetComponent<TransformComponent>().Position = {1.2, 1, 2};
      light.GetComponent<TransformComponent>().Scale = {0.2};

      lightId = light.Id; //Temporary
   }
}

void FirstScene::Update(double dt) {
   Light &light = GetEntity<Light>(lightId);
   auto &transformComponent = light.GetComponent<TransformComponent>();
   auto &input = Engine::Ins->GetModule<Input>();

   if (input.IsKeyHeld(Key::Up)) {
      transformComponent.EulerRotation.y += 2 * dt;
   }
   if (input.IsKeyHeld(Key::Down)) {
      transformComponent.EulerRotation.y -= 2 * dt;
   }
   if (input.IsKeyHeld(Key::Left)) {
      transformComponent.EulerRotation.x -= 2 * dt;
   }
   if (input.IsKeyHeld(Key::Right)) {
      transformComponent.EulerRotation.x += 2 * dt;
   }
   //
   // if (input.IsKeyHeld(Key::I)) {
   //    transformComponent.EulerRotation.y += 2 * dt;
   // }
   // if (input.IsKeyHeld(Key::O)) {
   //    transformComponent.EulerRotation.y -= 2 * dt;
   // }
}
