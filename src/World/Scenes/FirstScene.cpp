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

      auto &mesh = Primitives::CreateCube("cubeMesh");

      auto &objectShader = resourceManager.Load<Shader>("shader", "Assets/Shaders/shader.frag", "Assets/Shaders/shader.vert");

      auto &diffuseMap = resourceManager.Load<Texture>("diffuseMap", "Assets/Images/diffuseMap.png");
      auto &specularMap = resourceManager.Load<Texture>("specularMap", "Assets/Images/specularMap.png");
      auto &emissionMap = resourceManager.Load<Texture>("emissionMap", "Assets/Images/emissionMap.jpg");
      auto &rubyTexture = resourceManager.Load<Texture>("rubyTexture", "Assets/Images/ruby.png");
      auto &objectMaterial = resourceManager.Load<Material>("material");
      objectMaterial.AssignTexture(rubyTexture, 0);
      objectMaterial.Shader = &objectShader;
      objectMaterial.DiffuseMap = &diffuseMap;
      objectMaterial.SpecularMap = &specularMap;
      objectMaterial.EmissionMap = &emissionMap;

      // objectMaterial.Diffuse = {0};
      // objectMaterial.Ambient = {0};
      // objectMaterial.Specular = {0};
      // objectMaterial.Diffuse = {0};
      objectMaterial.Emission = {3};

      Cube &cube = CreateEntity<Cube>();
      cube.GetComponent<MaterialComponent>().Material = &objectMaterial;
      cube.GetComponent<MeshComponent>().Mesh = &mesh;

      cubeId = cube.Id; //Temporary

      auto &lightShader = resourceManager.Load<Shader>("lightShader", "Assets/Shaders/lightShader.frag",
         "Assets/Shaders/lightShader.vert");

      auto &lightMaterial = resourceManager.Load<Material>("lightMaterial");
      lightMaterial.Shader = &lightShader;

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

   auto &materialComponent = GetEntity<Cube>(cubeId).GetComponent<MaterialComponent>();

   materialComponent.Material->Shader->SetUniform(Vector3Uniform("LightPosition", transformComponent.Position));
}
