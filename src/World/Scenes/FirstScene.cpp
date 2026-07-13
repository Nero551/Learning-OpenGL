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
      SetActiveCamera(camera);

      auto &mesh = Primitives::CreateCube("cubeMesh");

      auto &objectShader = resourceManager.Load<Shader>("shader", "Assets/Shaders/shader.frag", "Assets/Shaders/shader.vert");

      auto &objectMaterial = resourceManager.Load<Material>("material");
      objectMaterial.AssignShader(objectShader);

      Cube &cube = CreateEntity<Cube>();
      cube.GetComponent<MaterialComponent>().SetMaterial(objectMaterial);
      cube.GetComponent<MeshComponent>().SetMesh(mesh);

      cubeId = cube.Id; //Temporary

      auto &lightShader = resourceManager.Load<Shader>("lightShader", "Assets/Shaders/lightShader.frag",
         "Assets/Shaders/lightShader.vert");

      auto &lightMaterial = resourceManager.Load<Material>("lightMaterial");
      lightMaterial.AssignShader(lightShader);

      Light &light = CreateEntity<Light>();
      light.GetComponent<MaterialComponent>().SetMaterial(lightMaterial);
      light.GetComponent<MeshComponent>().SetMesh(mesh);

      light.GetComponent<TransformComponent>().Position = {1.2, 1, 2};
      light.GetComponent<TransformComponent>().Scale = {0.2};

      light.GetComponent<LightComponent>().Ambient = {0.2};
      light.GetComponent<LightComponent>().Diffuse = {0.5};
      light.GetComponent<LightComponent>().Specular = {0.2};

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

   materialComponent.GetMaterial().GetShader().SetUniform(Vector3Uniform("LightPosition", transformComponent.Position));
}
