// Copyright © 2008-2015 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef UI_MAINMENUBACKGROUND_H
#define UI_MAINMENUBACKGROUND_H

#include "Single.h"
#include "scenegraph/ModelSkin.h"

namespace UI {

class MainMenuBackground : public Single {
public:
	virtual void Draw();

protected:
	friend class Context;
	MainMenuBackground(Context *context);

private:
	float m_time;
	float m_last_time;
	Graphics::Renderer *m_renderer;

	std::vector<SceneGraph::Model*> m_models;
	SceneGraph::ModelSkin m_skin;
};

}

#endif
