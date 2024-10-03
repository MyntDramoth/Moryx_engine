#pragma once

#include "AABB.h"
#include "../Graphics_System/Math/vector2D.h"
#include <vector>

typedef struct hit Hit;
typedef struct body Body;
typedef struct static_body Static_Body;

typedef void (*On_Hit)(Body *self, Body *other, Hit hit);
typedef void (*On_Hit_Static)(Body *self, Static_Body *other, Hit hit);
struct body {
	AABB aabb;
	Vector2D velocity;
	Vector2D acceleration;
	On_Hit on_hit;
	On_Hit_Static on_hit_static;
    size_t entity_id;
	uint8_t collision_layer;
	uint8_t collision_mask;
	bool is_kinematic;
	bool is_active;
};

struct static_body {
	AABB aabb;
	uint8_t collision_layer;
};

struct hit {
	size_t other_id;
	float time;
	Vector2D position;
	Vector2D normal;
	bool is_hit;
};

typedef struct physics_state_internal {

}Physics_State_Internal;

class Physics {

public:
    Physics();
    ~Physics();

    



    
    void physics_update(float delta_t);


    size_t physics_body_create(Vector2D position, Vector2D size, Vector2D velocity, uint8_t collision_layer, uint8_t collision_mask, bool is_kinematic, On_Hit on_hit, On_Hit_Static on_hit_static, size_t entity_id);
    size_t physics_trigger_create(Vector2D position, Vector2D size, uint8_t collision_layer, uint8_t collision_mask, On_Hit on_hit);
    Body *physics_body_get(size_t index);
    Static_Body *physics_static_body_get(size_t index);
    size_t physics_static_body_count();
    size_t physics_static_body_create(Vector2D position, Vector2D size, uint8_t collision_layer);
    bool physics_point_intersect_aabb(Vector2D point, AABB aabb);
    bool physics_aabb_intersect_aabb(AABB a, AABB b);
    AABB aabb_minkowski_difference(AABB a, AABB b);
    void aabb_penetration_vector(Vector2D r, AABB aabb);
    void aabb_min_max(Vector2D min, Vector2D max, AABB aabb);
    Hit ray_intersect_aabb(Vector2D position, Vector2D magnitude, AABB aabb);
    void physics_reset(void);

    void physics_body_destroy(size_t body_id);


    void update_sweep_result(Hit *result, Body *body, size_t other_id, Vector2D velocity);
    void update_sweep_result_static(Hit *result, Body *body, size_t other_id, Vector2D velocity);
    Hit sweep_static_bodies(Body *body, Vector2D velocity);
    Hit sweep_bodies(Body *body, Vector2D velocity);
    void sweep_response(Body *body, Vector2D velocity);
    void stationary_response(Body *body);

private:
    float gravity;
	float terminal_velocity;
    float tick_rate;
    int iterations = 4;
	std::vector<body> body_list;
	std::vector<static_body> static_body_list;
};