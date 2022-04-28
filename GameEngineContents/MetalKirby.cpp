#include "MetalKirby.h"

#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineLevel.h>

#include "Bullet.h"
#include "Stage.h"
#include "ContentsEnum.h"
#include "Monster.h"
#include "Scarfy.h"

MetalKirby* MetalKirby::MetalPlayer = nullptr;

MetalKirby::MetalKirby()
{

}
MetalKirby::~MetalKirby()
{

}


