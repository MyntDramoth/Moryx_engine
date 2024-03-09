#pragma once

#include "../../App/types.h"
#include "../math/vector3D.h"
#include "../math/vector2D.h"

typedef struct hit Hit;
typedef struct body Body;
typedef struct static_body Static_Body;

typedef void (*On_Hit)(Body *self, Body *other, Hit hit);
typedef void (*On_Hit_Static)(Body *self, Static_Body *other, Hit hit);


typedef struct aabb {
	Vector3D position;
	Vector3D half_size;
} AABB;

struct body {
	AABB aabb;
	Vector3D velocity;
	Vector3D acceleration;
	On_Hit on_hit;
	On_Hit_Static on_hit_static;
    usize entity_id;
	u8 collision_layer;
	u8 collision_mask;
	bool is_kinematic;
	bool is_active;
};

struct static_body {
	AABB aabb;
	u8 collision_layer;
};

struct hit {
	usize other_id;
	f32 time;
	Vector3D position;
	Vector3D normal;
	bool is_hit;
};
/*
class Physics {
public:
	Physics();
	~Physics(){};
	void physics_update();
	//usize physics_body_create(Vector3D position, Vector3D size, Vector3D velocity, u8 collision_layer, u8 collision_mask, bool is_kinematic, On_Hit on_hit, On_Hit_Static on_hit_static, usize entity_id);
	//usize physics_trigger_create(Vector3D position, Vector3D size, u8 collision_layer, u8 collision_mask, On_Hit on_hit);
	Body *physics_body_get(usize index);
	Static_Body *physics_static_body_get(usize index);
	usize physics_static_body_count();
	//usize physics_static_body_create(Vector3D position, Vector3D size, u8 collision_layer);
	bool physics_point_intersect_aabb(Vector3D point, AABB aabb);
	bool physics_aabb_intersect_aabb(AABB a, AABB b);
	AABB aabb_minkowski_difference(AABB a, AABB b);
	void aabb_penetration_vector(Vector3D r, AABB aabb);
	void aabb_min_max(Vector3D min, Vector3D max, AABB aabb);
	Hit ray_intersect_aabb(Vector3D position, Vector3D magnitude, AABB aabb);
	void physics_reset();

	//void physics_body_destroy(usize body_id);
};*/