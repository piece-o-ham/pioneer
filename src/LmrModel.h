#ifndef _LUA_MODEL_COMPILER_H
#define _LUA_MODEL_COMPILER_H

#include <map>
#include <vector>

// LMR = Lua Model Renderer
class LmrGeomBuffer;
class LmrCollMesh;
class GeomTree;

#define LMR_MAX_LOD 4

#define LMR_ARG_MAX 40
	
struct LmrMaterial {
	float diffuse[4];
	float specular[4];
	float emissive[4];
	float shininess;
};

struct LmrObjParams
{
	float argFloats[LMR_ARG_MAX];
	const char *argStrings[LMR_ARG_MAX];

	float linthrust[3];		// 1.0 to -1.0
	float angthrust[3];		// 1.0 to -1.0

	struct LmrMaterial pMat[3];
};

struct RenderState;
class LmrCollMesh;

class LmrModel {
public:
	LmrModel(const char *model_name);
	virtual ~LmrModel();
	void Render(const matrix4x4f &trans, const LmrObjParams *params);
	void Render(const RenderState *rstate, const vector3f &cameraPos, const matrix4x4f &trans, const LmrObjParams *params);
	void GetCollMeshGeometry(LmrCollMesh *mesh, const matrix4x4f &transform, const LmrObjParams *params);
	float GetBoundingRadius() const { return m_boundingRadius; }
	float GetFloatAttribute(const char *attr_name) const;
	const char *GetName() const { return m_name.c_str(); }
private:
	void Build(int lod, const LmrObjParams *params);

	// index into m_materials
	std::map<std::string, int> m_materialLookup;
	std::vector<LmrMaterial> m_materials;
	float m_lodPixelSize[LMR_MAX_LOD];
	int m_numLods;
	LmrGeomBuffer *m_staticGeometry[LMR_MAX_LOD];
	LmrGeomBuffer *m_dynamicGeometry[LMR_MAX_LOD];
	std::string m_name;
	bool m_hasDynamicFunc;
	// only used for lod pixel size at the moment
	float m_boundingRadius;
	float m_scale;
	friend class LmrGeomBuffer;
};

void LmrModelCompilerInit();
struct LmrModelNotFoundException {};
LmrModel *LmrLookupModelByName(const char *name) throw (LmrModelNotFoundException);
void LmrModelRender(LmrModel *m, const matrix4x4f &transform);
int LmrModelGetStatsTris();
void LmrModelClearStatsTris();
void LmrNotifyScreenWidth(float width);
void LmrGetModelsWithTag(const char *tag, std::vector<LmrModel*> &outModels);

class LmrCollMesh
{
public:
	LmrCollMesh(LmrModel *m, const LmrObjParams *params);
	~LmrCollMesh();

	const Aabb &GetAabb() const { return m_aabb; }
	float GetBoundingRadius() const { return m_radius; }
	int GetTrisWithGeomflag(unsigned int flags, int num, vector3d *outVtx) const;
	GeomTree *geomTree;
	// num vertices, num indices, num flags
	int nv, ni, nf;
	float *pVertex;
	int *pIndex;
	int m_numTris; // ni/3
	int *pFlag; // 1 per tri
	friend class LmrModel;
	friend class LmrGeomBuffer;
private:
	Aabb m_aabb;
	float m_radius;
};


#endif /* _LUA_MODEL_COMPILER_H */
