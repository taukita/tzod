// DefaultCamera.h

#pragma once

#include "core/MyMath.h"

class DefaultCamera
{
public:
	DefaultCamera();

	void HandleMovement(float worldWidth, float worldHeight, float screenWidth, float screenHeight);
	float GetZoom() const { return _zoom; }
	float GetPosX() const { return _pos.x; }
	float GetPosY() const { return _pos.y; }

private:
	float _zoom;
	float _dt;
	vec2d _pos;
	unsigned int _dwTimeX;
	unsigned int _dwTimeY;
};

// end of file
