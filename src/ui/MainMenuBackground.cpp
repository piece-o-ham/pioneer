// Copyright © 2008-2015 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "MainMenuBackground.h"
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
#include "ShipType.h"
#include <algorithm>

namespace UI {

MainMenuBackground::MainMenuBackground(Context *context, int width, int height) :
	Single(context), m_initzd(false), m_last_time(SDL_GetTicks()), m_renderer(context->GetRenderer()),
	m_stationModel(nullptr)
{
	m_aspectRatio = static_cast<float>(width) / static_cast<float>(height);
	m_ambientColor = Color(0);

	m_background.reset(new ::Background::Container(m_renderer, Pi::rng));
}

MainMenuBackground::~MainMenuBackground()
{
	delete m_stationModel;
	m_stationModel = nullptr;
}

// We need to initialize later because the models won't be ready when the constructor
// is called.
void MainMenuBackground::InitBackground()
{
	m_stationModel = Pi::FindModel("orbital_station_2-5k")->MakeInstance();
	m_initzd = true;
}

const matrix4x4d btrans = matrix4x4d::RotateXMatrix(0.25) * matrix4x4d::RotateZMatrix(0.6);
void MainMenuBackground::Draw()
{
	if(!m_initzd)
	{
		InitBackground();
	}
	else
	{
		// Something feels weird about using SDL here, but this is not
		// a major game component. It is only used in one place.
		// Remove comment if you disagree, fix it if you agree.
		m_time += 0.001f*(SDL_GetTicks() - m_last_time);
		m_last_time = SDL_GetTicks();

		Graphics::Renderer::StateTicket ticket(m_renderer); // unused?

		m_renderer->SetViewport(0, 0, Graphics::GetScreenWidth(), Graphics::GetScreenHeight());
		m_renderer->SetPerspectiveProjection(75, m_aspectRatio, 1.f, 10000.f);
		m_renderer->SetTransform(matrix4x4f::Identity());

		m_renderer->SetAmbientColor(m_ambientColor);
		//m_renderer->SetLights(m_lights.size(), &m_lights[0]);

		// XXX all this stuff will *supposedly* be gone when intro uses a Camera
		m_renderer->ClearDepthBuffer();
		m_background->Draw(btrans);

		matrix4x4f trans =
			matrix4x4f::Translation(0, 0, -60.0f) *
			matrix4x4f::RotateXMatrix(DEG2RAD(-110.f)) *
			matrix4x4f::RotateZMatrix(DEG2RAD(35.f)) *
			matrix4x4f::Translation(0, -230.0f, -100.f) *
			matrix4x4f::RotateYMatrix(m_time * 0.15);
		m_stationModel->Render(trans);
	}

	Container::Draw();
}

}
