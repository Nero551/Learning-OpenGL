#include "FirstScene.hpp"

#include "Modules/Input/Input.hpp"
#include "Modules/Input/Keys.hpp"
#include "Modules/Renderer/Entities/Cube.hpp"
#include "Modules/Renderer/Entities/Light.hpp"
#include "../../Modules/Renderer/Primitives/Primitives.hpp"
#include "Modules/Renderer/Uniforms/Vector3Uniform.hpp"
#include "Utilities/Math/Color.hpp"
#include "World/Entities/Axis.hpp"

unsigned int lightId;

void FirstScene::Initialize()
{
   auto& resourceManager = Engine::Ins->ResourceManager;
   auto& camera = CreateEntity<Camera>();
   camera.GetComponent<CameraComponent>().AspectRatio = Engine::Ins->Window.Width / Engine::Ins->Window.Height;
   ActiveCamera = &camera;

   auto& shader = Engine::Ins->ResourceManager.Load<Shader>("AxisShader", "Assets/Shaders/axisShader.frag",
                                                            "Assets/Shaders/axisShader.vert");
   auto& line = Primitives::CreateLine("Line");

   auto& xAxis = CreateEntity<Axis>();
   xAxis.GetComponent<MeshComponent>().Mesh = &line;
   xAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("X-Axis Material");
   xAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

   xAxis.GetComponent<TransformComponent>().EulerRotation = {0, Math::Radians(90), 0};
   xAxis.GetComponent<TransformComponent>().Position = {-50, 0, 0};
   xAxis.GetComponent<TransformComponent>().Scale = {1, 1, 200};
   xAxis.GetComponent<MaterialComponent>().Material->Color = Color::Red;

   auto& yAxis = CreateEntity<Axis>();
   yAxis.GetComponent<MeshComponent>().Mesh = &line;
   yAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("Y-Axis Material");;
   yAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

   yAxis.GetComponent<TransformComponent>().EulerRotation = {Math::Radians(-90), 0, 0};
   yAxis.GetComponent<TransformComponent>().Position = {0, -50, 0};
   yAxis.GetComponent<TransformComponent>().Scale = {1, 1, 200};
   yAxis.GetComponent<MaterialComponent>().Material->Color = Color::Green;

   auto& zAxis = CreateEntity<Axis>();
   zAxis.GetComponent<MeshComponent>().Mesh = &line;
   zAxis.GetComponent<MaterialComponent>().Material = &resourceManager.Load<Material>("Z-Axis Material");
   zAxis.GetComponent<MaterialComponent>().Material->Shader = &shader;

   zAxis.GetComponent<TransformComponent>().EulerRotation = {0, 0, 0};
   zAxis.GetComponent<TransformComponent>().Position = {0, 0, -50};
   zAxis.GetComponent<TransformComponent>().Scale = {1, 1, 200};
   zAxis.GetComponent<MaterialComponent>().Material->Color = Color::Blue;

   auto& mesh = Primitives::CreateCube("mesh");

   auto& objectShader = resourceManager.Load<Shader>("shader", "Assets/Shaders/shader.frag",
                                                     "Assets/Shaders/shader.vert");

   auto& diffuseMap = resourceManager.Load<Texture>("diffuseMap", "Assets/Images/diffuseMap.png");
   auto& specularMap = resourceManager.Load<Texture>("specularMap", "Assets/Images/specularMap.png");
   auto& objectMaterial = resourceManager.Load<Material>("material");
   objectMaterial.Shader = &objectShader;
   objectMaterial.DiffuseMap = &diffuseMap;
   objectMaterial.SpecularMap = &specularMap;

   for (float i = 0; i < 6; i += 0.5)
   {
      Cube& cube = CreateEntity<Cube>();
      cube.GetComponent<MaterialComponent>().Material = &objectMaterial;
      cube.GetComponent<MeshComponent>().Mesh = &mesh;
      cube.GetComponent<TransformComponent>().Position = {std::cos(i) * 5, 0, std::sin(i) * 5};
   }

   auto& lightShader = resourceManager.Load<Shader>("lightShader", "Assets/Shaders/lightShader.frag",
                                                    "Assets/Shaders/lightShader.vert");

   auto& lightMaterial = resourceManager.Load<Material>("lightMaterial");
   lightMaterial.Shader = &lightShader;

   auto& light = CreateEntity<Light>();
   light.GetComponent<MaterialComponent>().Material = &lightMaterial;
   light.GetComponent<MeshComponent>().Mesh = &mesh;

   light.GetComponent<TransformComponent>().Scale = {0.2};

   light.GetComponent<LightComponent>().Type = LightType::Directional;

   lightId = light.Id; //Temporary
}

void FirstScene::Update(double dt)
{
   auto& light = GetEntity<Light>(lightId);
   auto& transformComponent = light.GetComponent<TransformComponent>();
   auto& input = Engine::Ins->GetModule<Input>();

   auto dtf = static_cast<float>(dt);

   if (input.IsKeyHeld(Key::Up))
   {
      transformComponent.Position.z += 2.0f * dtf;
   }
   if (input.IsKeyHeld(Key::Down))
   {
      transformComponent.Position.z -= 2.0f * dtf;
   }
   if (input.IsKeyHeld(Key::Left))
   {
      transformComponent.Position.x -= 2.0f * dtf;
   }
   if (input.IsKeyHeld(Key::Right))
   {
      transformComponent.Position.x += 2.0f * dtf;
   }

   if (input.IsKeyHeld(Key::I))
   {
      transformComponent.Position.y += 2.0f * dtf;
   }
   if (input.IsKeyHeld(Key::O))
   {
      transformComponent.Position.y -= 2.0f * dtf;
   }

   if (input.IsKeyHeld(Key::Z))
   {
      transformComponent.EulerRotation.x += 2.0f * dtf;
   }

   if (input.IsKeyHeld(Key::X))
   {
      transformComponent.EulerRotation.y += 2.0f * dtf;
   }

   if (input.IsKeyHeld(Key::C))
   {
      transformComponent.EulerRotation.z += 2.0f * dtf;
   }
}
