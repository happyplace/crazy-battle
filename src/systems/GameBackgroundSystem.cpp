#include "GameBackgroundSystem.h"

#include "AssetLoaderHelper.h"

#include "ui/UIRendererHelper.h"

GameBackgroundSystem::GameBackgroundSystem()
{
    m_jungle = AssetLoaderHelper::LoadTexture("media/jungle_asset_pack/jungle_sprites.png");
    m_jungleFrames = AssetLoaderHelper::LoadTextureFrames("media/jungle_sprites.json");
}

void GameBackgroundSystem::Render()
{
    float backgroundScale = 3.4f;
    UIRendererHelper::RenderTextureFrame(0, 0, "plx-1.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);
    UIRendererHelper::RenderTextureFrame(0, 0, "plx-2.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);
    UIRendererHelper::RenderTextureFrame(0, 0, "plx-3.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);
    UIRendererHelper::RenderTextureFrame(0, 0, "plx-4.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);
    UIRendererHelper::RenderTextureFrame(0, 0, "plx-5.png", m_jungle, m_jungleFrames, backgroundScale, backgroundScale);
}
