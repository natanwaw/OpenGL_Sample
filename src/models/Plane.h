#ifndef PLANE_H

#include "Model.h"

class Plane : public Model
{
	unsigned int planeVAO, planeVBO;
	unsigned int groundDiffuseMap;

public:
	Plane();

protected:
	virtual void DrawShape(Shader& shader) override;

};
#endif