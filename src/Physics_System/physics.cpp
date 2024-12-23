#include "physics.h"
#include "../Graphics_System/prerequisites.h"

Physics::Physics() {
   
	
	//currently can't have enemies that move slower than gravity, an event queue can fix this but it's complicated
	gravity = 10.0f;
	terminal_velocity = 7000.0f;

	tick_rate = 1.0f / iterations;
}

Physics::~Physics()
{
}

void Physics::physics_update(float delta_t) {
	Body *body;

	for (int i = 0; i < body_list.size(); ++i) {
		body = &body_list[i];

		if (!body->is_active) {
			continue;
		}

		if (!body->is_kinematic) {
			body->velocity.y += gravity;
			if (terminal_velocity < body->velocity.y) {
				body->velocity.y = terminal_velocity;
			}
		}
		
		body->velocity.x += body->acceleration.x;
		body->velocity.y += body->acceleration.y;

		Vector2D scaled_velocity;
		
		scaled_velocity = body->velocity * (delta_t * tick_rate);

		for (int j = 0; j < iterations; ++j) {
			sweep_response(body, scaled_velocity);
			stationary_response(body);
		}
	}
}

size_t Physics::physics_body_create(Vector2D position, Vector2D size, Vector2D velocity, uint8_t collision_layer, uint8_t collision_mask, bool is_kinematic, On_Hit on_hit, On_Hit_Static on_hit_static, size_t entity_id) {
   size_t id = body_list.size();

	// Find inactive Body.
	for (size_t i = 0; i < body_list.size(); ++i) {
		Body *body = &body_list[i];
		if (!body->is_active) {
			id = i;
			break;
		}
	}
	body_list.push_back({});
	/*
	if (id == body_list.size()) {
		if (array_list_append(state.body_list, &(Body){0}) == (usize)-1) {
			ERROR_EXIT("Could not append body to list\n");
		}
	}*/

	Body *body = physics_body_get(id);
/*
	*body = (Body){
		.aabb = {
			.position = { position[0], position[1] },
			.half_size = { size[0] * 0.5, size[1] * 0.5 },
		},
		.velocity = { velocity[0], velocity[1] },
		.collision_layer = collision_layer,
		.collision_mask = collision_mask,
		.on_hit = on_hit,
		.on_hit_static = on_hit_static,
		.is_kinematic = is_kinematic,
		.is_active = true,
        .entity_id = entity_id
	};*/
	body->aabb.position = Vector3D(position.x,position.y,0.0f);
	body->aabb.bounds = Vector3D(size.x*0.5f,size.y*0.5f,0.0f);
	body->velocity = velocity;
	body->collision_layer = collision_layer;
	body->collision_mask = collision_mask;
	body->on_hit = on_hit;
	body->on_hit_static = on_hit_static;
	body->is_kinematic = is_kinematic;
	body->is_active = true;
	body->entity_id = entity_id;
	

	return id;
}

size_t Physics::physics_trigger_create(Vector2D position, Vector2D size, uint8_t collision_layer, uint8_t collision_mask, On_Hit on_hit) {
   return physics_body_create(position, size, Vector2D{0, 0}, collision_layer, collision_mask, true, on_hit, NULL, (size_t)-1);
}

Body *Physics::physics_body_get(size_t index) {
    return &body_list[index];
}

Static_Body *Physics::physics_static_body_get(size_t index) {
    return &static_body_list[index];
}

size_t Physics::physics_static_body_count() {
    return static_body_list.size();
}

size_t Physics::physics_static_body_create(Vector2D position, Vector2D size, uint8_t collision_layer)
{
    Static_Body static_body = {};
    static_body.aabb.position = Vector3D(position.x,position.y,0.0f);
    static_body.aabb.bounds = Vector3D(size.x * 0.5, size.y * 0.5,0.0f);
		
	static_body.collision_layer = collision_layer,
    static_body_list.push_back(static_body);
	//if (static_body_list.pushback(static_body) == (size_t)-1)
		//("Could not append static body to list\n");

	return static_body_list.size() - 1;
}

bool Physics::physics_point_intersect_aabb(Vector2D point, AABB aabb)
{
   Vector2D min, max;
	aabb_min_max(&min, &max, aabb);
	return  point.x >= min.x &&
		point.x <= max.x &&
		point.y >= min.y &&
		point.y <= max.y;
}

bool Physics::physics_aabb_intersect_aabb(AABB a, AABB b)
{
    Vector2D min, max;
	aabb_min_max(&min, &max, aabb_minkowski_difference(a, b));

	return (min.x <= 0 && max.x >= 0 && min.y <= 0 && max.y >= 0);
}

AABB Physics::aabb_minkowski_difference(AABB a, AABB b) {
    AABB result;
	result.position = a.position - b.position;
	result.bounds = a.bounds + b.bounds;

	return result;
}

void Physics::aabb_penetration_vector(Vector2D r, AABB aabb) {
    Vector2D min, max;
	aabb_min_max(&min, &max, aabb);

	float min_dist = fabsf(min.x);
	r.x = min.x;
	r.y = 0;

	if (fabsf(max.x) < min_dist) {
		min_dist = fabsf(max.x);
		r.x = max.x;
	}

	if (fabsf(min.y) < min_dist) {
		min_dist = fabsf(min.y);
		r.x = 0;
		r.y = min.y;
	}

	if (fabsf(max.y) < min_dist) {
		r.x = 0;
		r.y = max.y;
	}
}

void Physics::aabb_min_max(Vector2D* min, Vector2D* max, AABB aabb) {
	
	//min = &Vector2D(aabb.position.x - aabb.bounds.x,aabb.position.y - aabb.bounds.y);
	if(min) {
		min->y = aabb.position.y - aabb.bounds.y;
		min->x = aabb.position.x - aabb.bounds.x;
	}
	//max = &Vector2D(aabb.position.x + aabb.bounds.x,aabb.position.y + aabb.bounds.y);
	if(max) {
		max->x = aabb.position.x + aabb.bounds.x;
		max->y = aabb.position.y + aabb.bounds.y;
	}
	MORYX_INFO("min: "<<min->y<<"|| max: "<<max->y);
}

Hit Physics::ray_intersect_aabb(Vector2D position, Vector2D magnitude, AABB aabb)
{
    Hit hit = {0};
	Vector2D min, max;
	aabb_min_max(&min, &max, aabb);

	float last_entry = -INFINITY;
	float first_exit = INFINITY;

	for (uint8_t i = 0; i < 2; ++i) {
		if (magnitude[i] != 0) {
			float t1 = (min[i] - position[i]) / magnitude[i];
			float t2 = (max[i] - position[i]) / magnitude[i];

			last_entry = fmaxf(last_entry, fminf(t1, t2));
			first_exit = fminf(first_exit, fmaxf(t1, t2));
		} else if (position[i] <= min[i] || position[i] >= max[i]) {
			return hit;
		}
	}

	if (first_exit > last_entry && first_exit > 0 && last_entry < 1) {
		hit.position.x = position[0] + magnitude[0] * last_entry;
		hit.position.y = position[1] + magnitude[1] * last_entry;

		hit.is_hit = true;
		hit.time = last_entry;

		float dx = hit.position[0] - aabb.position[0];
		float dy = hit.position[1] - aabb.position[1];
		float px = aabb.bounds[0] - fabsf(dx);
		float py = aabb.bounds[1] - fabsf(dy);

		if (px < py) {
			hit.normal.x = (dx > 0) - (dx < 0);
		} else {
			hit.normal.y = (dy > 0) - (dy < 0);
		}
	}

	return hit;
}

void Physics::physics_reset(void) {
    body_list.empty();
    static_body_list.empty();
}

void Physics::physics_body_destroy(size_t body_id) {
    Body *body = physics_body_get(body_id);
    body->is_active = false;
}

void Physics::update_sweep_result(Hit *result, Body *body, size_t other_id, Vector2D velocity) {
	Body *other = physics_body_get(other_id);

	if ((body->collision_mask & other->collision_layer) == 0) {
		return;
	}
	
	AABB sum_aabb = other->aabb;
	sum_aabb.bounds = sum_aabb.bounds + body->aabb.bounds;

	Hit hit = ray_intersect_aabb(Vector2D(body->aabb.position.x,body->aabb.position.y), velocity, sum_aabb);
	if (hit.is_hit) {
		if (body->on_hit && (body->collision_mask & other->collision_layer) == 0) {
			body->on_hit(body, other, hit);
		}

		if (hit.time < result->time) {
			*result = hit;
		} else if (hit.time == result->time) {
			// Solve highest velocity axis first.
			if (fabsf(velocity.x) > fabsf(velocity.y) && hit.normal.x != 0) {
				*result = hit;
			} else if (fabsf(velocity.y) > fabsf(velocity.x) && hit.normal.y != 0) {
				*result = hit;
			}
		}

		result->other_id = other_id;
	}
}

void Physics::update_sweep_result_static(Hit *result, Body *body, size_t other_id, Vector2D velocity) {
	Static_Body *static_body = physics_static_body_get(other_id);
	
	if ((body->collision_mask & static_body->collision_layer) == 0) {
		return;
	}
	
	AABB sum_aabb = static_body->aabb;
	sum_aabb.bounds = sum_aabb.bounds + body->aabb.bounds;

	Hit hit = ray_intersect_aabb(Vector2D(body->aabb.position.x,body->aabb.position.y), velocity, sum_aabb);
	if (hit.is_hit) {
		if (hit.time < result->time) {
			*result = hit;
		} else if (hit.time == result->time) {
			// Solve highest velocity axis first.
			if (fabsf(velocity.x) > fabsf(velocity.y) && hit.normal.x != 0) {
				*result = hit;
			} else if (fabsf(velocity.y) > fabsf(velocity.x) && hit.normal.y != 0) {
				*result = hit;
			}
		}

		result->other_id = other_id;
	}
}

Hit Physics::sweep_static_bodies(Body *body, Vector2D velocity) {
    Hit result = {};
	result.time = 0xBEEF;

	for (int i = 0; i < static_body_list.size(); ++i) {
		update_sweep_result_static(&result, body, i, velocity);
	}

	return result;
}

Hit Physics::sweep_bodies(Body *body, Vector2D velocity)
{
   	Hit result = {};
	result.time = 0xBEEF;

	for (int i = 0; i < body_list.size(); ++i) {
		Body *other = physics_body_get(i);

		if (body == other) {
			continue;
		}
		update_sweep_result(&result, body, i, velocity);
	}

	return result;
}

void Physics::sweep_response(Body *body, Vector2D velocity) {
	Hit hit = sweep_static_bodies(body, velocity);
	Hit hit_moving = sweep_bodies(body, velocity);

	if (hit_moving.is_hit) {
		if (body->on_hit != NULL) {
			body->on_hit(body, physics_body_get(hit_moving.other_id), hit_moving);
		}
	}

	if (hit.is_hit) {
		
		body->aabb.position.x = hit.position.x;
		body->aabb.position.y = hit.position.y;

		if (hit.normal.x != 0) {
			body->aabb.position.x += velocity.x;
			body->velocity.y = 0;
		} else if (hit.normal.y != 0) {
			body->aabb.position.x += velocity.x;
			body->velocity.y = 0;
		}

		if (body->on_hit_static != NULL) {
			body->on_hit_static(body, physics_static_body_get(hit.other_id), hit);
		}
	} else {
		body->aabb.position = body->aabb.position + Vector3D(velocity.x,velocity.y,0.0f);
	}
	body->aabb.position = body->aabb.position + Vector3D(velocity.x,velocity.y,0.0f);
}

void Physics::stationary_response(Body *body) {
	for (int i = 0; i < static_body_list.size(); ++i) {
		Static_Body *static_body = physics_static_body_get(i);

		if ((body->collision_mask & static_body->collision_layer) == 0) {
			continue;
		}

		AABB aabb = aabb_minkowski_difference(static_body->aabb, body->aabb);
		Vector2D min, max;
		aabb_min_max(&min, &max, aabb);
		MORYX_INFO("calc min: "<<min.y<<"|| calc max: "<<max.y);
		if (min.x <= 0 && max.x >= 0 && min.y <= 0 && max.y >= 0) {
			Vector2D penetration_vector;
			aabb_penetration_vector(penetration_vector, aabb);

			body->aabb.position = body->aabb.position + Vector3D(penetration_vector.x,penetration_vector.y,0.0f);
		}
	}

	// Check for on-hit events.
	for (size_t i = 0; i < body_list.size(); ++i) {
		Body *other = physics_body_get(i);

		if (!body->on_hit) {
			continue;
		}

		if ((body->collision_mask & other->collision_layer) == 0) {
			continue;
		}

		AABB aabb = aabb_minkowski_difference(other->aabb, body->aabb);
		Vector2D min, max;
		aabb_min_max(&min, &max, aabb);

		if (min.x <= 0 && max.x >= 0 && min.y <= 0 && max.y >= 0) {
			Hit h = {true,i};
			body->on_hit(body, other, h);
			
		}
	}
}
