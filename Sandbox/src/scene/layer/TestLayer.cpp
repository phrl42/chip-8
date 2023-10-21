#include "scene/layer/TestLayer.h"

#include "renderer/Renderer2D.h"

#include "ecs/components/QuadComponent.h"
#include "ecs/components/TextComponent.h"

namespace SANDBOX
{
  TestLayer::TestLayer(const std::string& name)
  : name(name)
  {
    CHIP8::Init_Spec(spec, "assets/roms/TEST");
  }

  TestLayer::~TestLayer()
  {

  }

  void TestLayer::OnAttach()
  {
    for(size_t y = 0; y < 32; y++)
    {
      for(size_t x = 0; x < 64; x++)
      {
	ent[y][x].AddComponent(new Banana::QuadComponent());
      }
    }
  }

  void TestLayer::OnDetach()
  {

  }


  void TestLayer::OnEvent(Banana::Event& event)
  {

  }

  void TestLayer::OnUpdate(float dt)
  {
    if(Banana::Input::IsKeyPressed(KEY_Y))
    {
    }
    if(Banana::Input::IsKeyPressed(KEY_Z))
    {
    }

    float one_width = 2.0f / 64;
    float one_height = 2.0f / 32;
    for(size_t y = 0; y < 32; y++)
    {
      for(size_t x = 0; x < 64; x++)
      {
	ent[y][x].transform.proj = Banana::Projection::NONE;
	ent[y][x].transform.pos = {(x * one_width) - 1, (y * one_height) - 1, 0};
	ent[y][x].transform.size = {one_width, one_height, 0};
	ent[y][x].transform.color = {spec.display[y][x], spec.display[y][x], spec.display[y][x], spec.display[y][x]};
	ent[y][x].Render(dt);
      }
    }
    
    CHIP8::Update(spec);

  }
};
