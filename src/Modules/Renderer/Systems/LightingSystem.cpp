#include "LightingSystem.hpp"

#include "../Components/LightComponent.hpp"
#include "../Components/MaterialComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Uniforms/FloatUniform.hpp"
#include "../Uniforms/IntUniform.hpp"
#include "../Uniforms/Vector3Uniform.hpp"

Vector3 lightColor;
Vector3 ambient;
Vector3 diffuse;
Vector3 specular;
Vector3 lightPos;
Vector3 lightDir;
LightType lightType;
float lightLinear;
float lightQuadratic;
float lightConstant;
float lightIntensity;
float lightInnerCutOff;
float lightOuterCutOff;

void LightingSystem::Render() {
   auto &scene = Engine::Ins->World.ActiveScene;
   auto &camera = scene->ActiveCamera;

   for (auto &entity: scene->Entities | std::views::values) {
      if (!entity->HasComponent<TransformComponent>()) {
         continue;
      }
      auto &transformComponent = entity->GetComponent<TransformComponent>();

      //TODO- rn this can only work with 1 light, fix that. it breaks with multiple lights.

      if (entity->HasComponent<LightComponent>()) {
         auto &lightComponent = entity->GetComponent<LightComponent>();
         lightColor = lightComponent.Color;
         lightPos = transformComponent.Position;
         lightDir = transformComponent.GetForward();
         ambient = lightComponent.Ambient;
         diffuse = lightComponent.Diffuse;
         specular = lightComponent.Specular;
         lightType = lightComponent.Type;
         lightLinear = lightComponent.Linear;
         lightQuadratic = lightComponent.Quadratic;
         lightConstant = lightComponent.Constant;
         lightIntensity = lightComponent.Intensity;
         lightInnerCutOff = lightComponent.InnerCutOff;
         lightOuterCutOff = lightComponent.OuterCutOff;
      }

      if (entity->HasComponent<MaterialComponent>()) {
         auto &materialComponent = entity->GetComponent<MaterialComponent>();


         materialComponent.Material->Shader->SetUniform(Vector3Uniform("ViewPosition",
            camera->GetComponent<TransformComponent>().Position));

         materialComponent.Material->Shader->SetUniform(Vector3Uniform("Light.Color", lightColor));
         materialComponent.Material->Shader->SetUniform(Vector3Uniform("Light.Position", lightPos));

         materialComponent.Material->Shader->SetUniform(Vector3Uniform("Light.Ambient", ambient));
         materialComponent.Material->Shader->SetUniform(Vector3Uniform("Light.Diffuse", diffuse));
         materialComponent.Material->Shader->SetUniform(Vector3Uniform("Light.Specular", specular));

         materialComponent.Material->Shader->SetUniform(IntUniform("Light.Type", static_cast<int>(lightType)));
         materialComponent.Material->Shader->SetUniform(Vector3Uniform("Light.Direction", lightDir));

         materialComponent.Material->Shader->SetUniform(FloatUniform("Light.Constant", lightConstant));
         materialComponent.Material->Shader->SetUniform(FloatUniform("Light.Linear", lightLinear));
         materialComponent.Material->Shader->SetUniform(FloatUniform("Light.Quadratic", lightQuadratic));
         materialComponent.Material->Shader->SetUniform(FloatUniform("Light.Intensity", lightIntensity));

         materialComponent.Material->Shader->SetUniform(FloatUniform("Light.InnerCutOff", std::cos(lightInnerCutOff)));
         materialComponent.Material->Shader->SetUniform(FloatUniform("Light.OuterCutOff", std::cos(lightOuterCutOff)));

      }
   }
}
