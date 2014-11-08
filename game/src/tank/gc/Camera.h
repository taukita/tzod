// Camera.h

#pragma once

#include "Actor.h"
#include "Rotator.h"

// forward declarations
class GC_Player;


class GC_Camera : public GC_Actor
{
	DECLARE_SELF_REGISTRATION(GC_Camera);
    DECLARE_LIST_MEMBER();
    typedef GC_Actor base;

private:
	vec2d _target;
	float _time_shake;
	float _time_seed;

	float _zoom;
	ObjPtr<GC_Player>  _player;

public:    
    GC_Camera(World &world, GC_Player *player);
	GC_Camera(FromFile);
	virtual ~GC_Camera();

	void CameraTimeStep(World &world, float dt, vec2d viewSize);

	vec2d GetCameraPos() const;
	float GetZoom() const { return _zoom; }
	GC_Player* GetPlayer() const { assert(_player); return _player; }

	void Shake(float level);
	float GetShake() const { return _time_shake; }

    // GC_Actor
    virtual void MoveTo(World &world, const vec2d &pos);

	// GC_Object
	virtual void Serialize(World &world, SaveFile &f);
};

// end of file
