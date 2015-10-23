// Copyright © 2008-2015 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef UI_MAINMENUBACKGROUND_H
#define UI_MAINMENUBACKGROUND_H

#include "Single.h"
#include "../Background.h" // ../ since this directory has a "Background.h" too.
#include "graphics/Renderer.h"
#include "scenegraph/ModelSkin.h"

namespace UI {

class MainMenuBackground : public Single {
public:
	virtual void Draw();
	void InitBackground();

protected:
	friend class Context;
	MainMenuBackground(Context *context, int width, int height);

private:
	bool m_initzd;

	float m_time;
	float m_last_time;
	Graphics::Renderer *m_renderer;
	float m_aspectRatio;
	
	Color m_ambientColor;
	std::vector<Graphics::Light> m_lights;
	
	// A double colon is needed since UI has a Background class.
	// This makes it look in the global first.
	std::unique_ptr<::Background::Container> m_background;

	std::vector<SceneGraph::Model*> m_models;
	SceneGraph::ModelSkin m_skin;
	SceneGraph::Model *m_stationModel;
};

}

#endif
