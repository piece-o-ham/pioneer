// Copyright © 2008-2015 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "ColorBackground.h"
#include "Context.h"
#include "graphics/Renderer.h"
#include "graphics/VertexArray.h"
#include "graphics/Material.h"

#include "Pi.h"
#include "Lang.h"
#include "Easing.h"
#include "graphics/TextureBuilder.h"
#include "graphics/Graphics.h"
#include "scenegraph/SceneGraph.h"
#include "scenegraph/ModelSkin.h"
#include <algorithm>

namespace UI {

MainMenuBackground::MainMenuBackground(Context *context) :
	Single(context), m_last_time(SDL_GetTicks()), m_renderer(context->GetRenderer())
{
}

void MainMenuBackground::Draw()
{
	m_time += 0.001f*(SDL_GetTicks() - m_last_time);
	m_last_time = SDL_GetTicks();
	float duration = m_time - m_startTime;

	//Graphics::Renderer::StateTicket ticket(m_renderer); // unused?

	m_renderer->SetPerspectiveProjection(75, m_aspectRatio, 1.f, 10000.f);
	m_renderer->SetTransform(matrix4x4f::Identity());

	m_renderer->SetAmbientColor(m_ambientColor);
	m_renderer->SetLights(m_lights.size(), &m_lights[0]);

	// XXX all this stuff will *supposedly* be gone when intro uses a Camera
	// rotate background by time, and a bit extra Z so it's not so flat
	m_renderer->ClearDepthBuffer();
	m_background->Draw(matrix4x4f::Identity());

	m_renderer->SetViewport(m_spinnerLeft, 0, m_spinnerWidth, Graphics::GetScreenHeight());
	m_renderer->SetPerspectiveProjection(75, m_spinnerRatio, 1.f, 10000.f);

	matrix4x4f trans =
		matrix4x4f::Translation(0, 0, m_dist) *
		matrix4x4f::RotateXMatrix(DEG2RAD(-15.0f)) *
		matrix4x4f::RotateYMatrix(_time);
	m_model->Render(trans);

	Container::Draw();
}

}
