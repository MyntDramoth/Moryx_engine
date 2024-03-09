#include "physics.h"
#include <limits>
/*
static u32 iterations = 4;
static f32 tick_rate;

void Physics::aabb_min_max(Vector3D min, Vector3D max, AABB aabb) {
    min = Vector3D(aabb.position - aabb.half_size);
	max = Vector3D(aabb.position + aabb.half_size);
}

AABB Physics::aabb_minkowski_difference(AABB a, AABB b) {
	AABB result;
	result.position = a.position - b.position;
	result.half_size = a.half_size + b.half_size;

	return result;
}

Hit Physics::ray_intersect_aabb(Vector3D pos, Vector3D magnitude, AABB aabb) {
	Hit hit = {0};
	Vector3D min, max;
	aabb_min_max(min, max, aabb);

	f32 last_entry = -INFINITY;
	f32 first_exit = INFINITY;
	/*
	for (u8 i = 0; i < 2; ++i) {
		if (magnitude[i] != 0) {
			f32 t1 = (min[i] - pos[i]) / magnitude[i];
			f32 t2 = (max[i] - pos[i]) / magnitude[i];

			last_entry = fmaxf(last_entry, fminf(t1, t2));
			first_exit = fminf(first_exit, fmaxf(t1, t2));
		} else if (pos[i] <= min[i] || pos[i] >= max[i]) {
			return hit;
		}
	}

	if (magnitude.x != 0) { 	
	f32 t1 = (min.x - pos.x) / magnitude.x;
	f32 t2 = (max.x - pos.x) / magnitude.x;
	last_entry = fmaxf(last_entry, fminf(t1, t2));
	first_exit = fminf(first_exit, fmaxf(t1, t2));
	} else if (pos.x <= min.x || pos.x >= max.x) {
		return hit; 
	}

	if (magnitude.y != 0) { 	
	f32 t1 = (min.y - pos.y) / magnitude.y;
	f32 t2 = (max.y - pos.y) / magnitude.y;
	last_entry = fmaxf(last_entry, fminf(t1, t2));
	first_exit = fminf(first_exit, fmaxf(t1, t2));
	} else if (pos.y <= min.y || pos.y >= max.y) {
		return hit; 
	}

	if (magnitude.z != 0) { 	
	f32 t1 = (min.z - pos.z) / magnitude.z;
	f32 t2 = (max.z - pos.z) / magnitude.z;
	last_entry = fmaxf(last_entry, fminf(t1, t2));
	first_exit = fminf(first_exit, fmaxf(t1, t2));
	} else if (pos.z <= min.z || pos.z >= max.z) {
		return hit; 
	}


	if (first_exit > last_entry && first_exit > 0 && last_entry < 1) {
		hit.position.x = pos.x + magnitude.x * last_entry;
		hit.position.y = pos.y + magnitude.y * last_entry;
		hit.position.z = pos.z + magnitude.z * last_entry;

		hit.is_hit = true;
		hit.time = last_entry;

		f32 dx = hit.position.x - aabb.position.x;
		f32 dy = hit.position.y - aabb.position.y;
		f32 dz = hit.position.z - aabb.position.z;
		f32 px = aabb.half_size.x - fabsf(dx);
		f32 py = aabb.half_size.y - fabsf(dy);
		f32 pz = aabb.half_size.z - fabsf(dz);

		if (px < py && px < pz) {
			hit.normal.x = (dx > 0) - (dx < 0);
		} else if (py < pz) {
			hit.normal.y = (dy > 0) - (dy < 0);
		} else {
			hit.normal.z = (dz > 0) - (dz < 0);
		}
	}

	return hit;
}

bool Physics::physics_aabb_intersect_aabb(AABB a, AABB b) {
	Vector3D min, max;
	aabb_min_max(min, max, aabb_minkowski_difference(a, b));

	return (min.x <= 0 && max.x >= 0 && min.y <= 0 && max.y >= 0 && min.z <= 0 && max.z >= 0);
}

void Physics::aabb_penetration_vector(Vector3D r, AABB aabb) {
	Vector3D min, max;
	aabb_min_max(min, max, aabb);

	f32 min_dist = fabsf(min.x);
	r.x = min.x;
	r.y = 0;
	r.z = 0;

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

	if (fabsf(min.z) < min_dist) {
		min_dist = fabsf(min.z);
		r.y = 0;
		r.z = min.z;
	}

	if (fabsf(max.z) < min_dist) {
		r.y = 0;
		r.z = max.z;
	}
}

bool Physics::physics_point_intersect_aabb(Vector3D point, AABB aabb) {
	Vector3D min, max;
	aabb_min_max(min, max, aabb);
	return  point.x >= min.x &&
		point.x <= max.x &&
		point.y >= min.y &&
		point.y <= max.y;
}


Physics::Physics() {
	//state.body_list = array_list_create(sizeof(Body), 0);
	//state.static_body_list = array_list_create(sizeof(Static_Body), 0);
	//currently can't have enemies that move slower than gravity, an event queue can fix this but it's complicated
	//state.gravity = -79;
	//state.terminal_velocity = -7000;

	tick_rate = 1.f / iterations;
}*/
/*
static void update_sweep_result(Hit *result, Body *body, usize other_id, Vector3D velocity) {
	Body *other = physics_body_get(other_id);

	if ((body->collision_mask & other->collision_layer) == 0) {
		return;
	}

	AABB sum_aabb = other->aabb;
	sum_aabb.half_size = sum_aabb.half_size + body->aabb.half_size;

	Hit hit = ray_intersect_aabb(body->aabb.position, velocity, sum_aabb);
	if (hit.is_hit) {
		if (body->on_hit && (body->collision_mask & other->collision_layer) == 0) {
			body->on_hit(body, other, hit);
		}

		if (hit.time < result->time) {
			*result = hit;
		} else if (hit.time == result->time) {
			// Solve highest velocity axis first.
			if (fabsf(velocity[0]) > fabsf(velocity[1]) && fabsf(velocity[0]) > fabsf(velocity[2]) && hit.normal[0] != 0) {
				*result = hit;
			} else if (fabsf(velocity[1]) > fabsf(velocity[0]) && fabsf(velocity[1]) > fabsf(velocity[2]) &&hit.normal[1] != 0) {
				*result = hit;
			} else if (fabsf(velocity[2]) > fabsf(velocity[0]) && fabsf(velocity[2]) > fabsf(velocity[1]) && hit.normal[2] != 0) {
				*result = hit;
			}
		}

		result->other_id = other_id;
	}
}

static void update_sweep_result_static(Hit *result, Body *body, usize other_id, Vector3D velocity) {
	Static_Body *static_body = physics_static_body_get(other_id);

	if ((body->collision_mask & static_body->collision_layer) == 0) {
		return;
	}

	AABB sum_aabb = static_body->aabb;
	sum_aabb.half_size = sum_aabb.half_size + body->aabb.half_size;

	Hit hit = ray_intersect_aabb(body->aabb.position, velocity, sum_aabb);
	if (hit.is_hit) {
		if (hit.time < result->time) {
			*result = hit;
		} else if (hit.time == result->time) {
			// Solve highest velocity axis first.
			if (fabsf(velocity[0]) > fabsf(velocity[1]) && fabsf(velocity[0]) > fabsf(velocity[2]) && hit.normal[0] != 0) {
				*result = hit;
			} else if (fabsf(velocity[1]) > fabsf(velocity[0]) && fabsf(velocity[1]) > fabsf(velocity[2]) &&hit.normal[1] != 0) {
				*result = hit;
			} else if (fabsf(velocity[2]) > fabsf(velocity[0]) && fabsf(velocity[2]) > fabsf(velocity[1]) && hit.normal[2] != 0) {
				*result = hit;
			}
		}

		result->other_id = other_id;
	}
}
/*
static Hit sweep_static_bodies(Body *body, Vector3D velocity) {
	Hit result = {.time = 0xBEEF};

	for (u32 i = 0; i < state.static_body_list->len; ++i) {
		update_sweep_result_static(&result, body, i, velocity);
	}

	return result;
}*/
/*
static Hit sweep_bodies(Body *body, Vector3D velocity) {
	Hit result = {.time = 0xBEEF};

	for (u32 i = 0; i < state.body_list->len; ++i) {
		Body *other = physics_body_get(i);

		if (body == other) {
			continue;
		}

		update_sweep_result(&result, body, i, velocity);
	}

	return result;
}*/
/*
static void sweep_response(Body *body, Vector3D velocity) {
	Hit hit = sweep_static_bodies(body, velocity);
	Hit hit_moving = sweep_bodies(body, velocity);

	if (hit_moving.is_hit) {
		if (body->on_hit != NULL) {
			body->on_hit(body, physics_body_get(hit_moving.other_id), hit_moving);
		}
	}

	if (hit.is_hit) {
		body->aabb.position[0] = hit.position[0];
		body->aabb.position[1] = hit.position[1];
		body->aabb.position[2] = hit.position[2];

		if (hit.normal[0] != 0) {
			body->aabb.position[1] += velocity[1];
			body->velocity[0] = 0;
		} else if (hit.normal[1] != 0) {
			body->aabb.position[0] += velocity[0];
			body->velocity[1] = 0;
		}

		if (body->on_hit_static != NULL) {
			body->on_hit_static(body, physics_static_body_get(hit.other_id), hit);
		}
	} else {
		body->aabb.position = body->aabb.position + velocity;
	}
}*/
/*
static void stationary_response(Body *body) {
	for (u32 i = 0; i < state.static_body_list->len; ++i) {
		Static_Body *static_body = physics_static_body_get(i);

		if ((body->collision_mask & static_body->collision_layer) == 0) {
			continue;
		}

		AABB aabb = aabb_minkowski_difference(static_body->aabb, body->aabb);
		Vector3D min, max;
		aabb_min_max(min, max, aabb);

		if (min[0] <= 0 && max[0] >= 0 && min[1] <= 0 && max[1] >= 0) {
			Vector3D penetration_vector;
			aabb_penetration_vector(penetration_vector, aabb);

			body->aabb.position = body->aabb.position + penetration_vector;
		}
	}

	// Check for on-hit events.
	for (usize i = 0; i < state.body_list->len; ++i) {
		Body *other = physics_body_get(i);

		if (!body->on_hit) {
			continue;
		}

		if ((body->collision_mask & other->collision_layer) == 0) {
			continue;
		}

		AABB aabb = aabb_minkowski_difference(other->aabb, body->aabb);
		Vector3D min, max;
		aabb_min_max(min, max, aabb);

		if (min[0] <= 0 && max[0] >= 0 && min[1] <= 0 && max[1] >= 0) {
			body->on_hit(body, other, (Hit){.is_hit = true, .other_id = i});
		}
	}
}*/
/*
void physics_update(void) {
	Body *body;

	for (u32 i = 0; i < state.body_list->len; ++i) {
		body = array_list_get(state.body_list, i);

		if (!body->is_active) {
			continue;
		}

		if (!body->is_kinematic) {
			body->velocity[1] += state.gravity;
			if (state.terminal_velocity > body->velocity[1]) {
				body->velocity[1] = state.terminal_velocity;
			}
		}

		body->velocity[0] += body->acceleration[0];
		body->velocity[1] += body->acceleration[1];

		Vector3D scaled_velocity;
		vec2_scale(scaled_velocity, body->velocity, global.time.delta * tick_rate);

		for (u32 j = 0; j < iterations; ++j) {
			sweep_response(body, scaled_velocity);
			stationary_response(body);
		}
	}
}*/
/*
usize physics_body_create(Vector3D position, Vector3D size, Vector3D velocity, u8 collision_layer, u8 collision_mask, bool is_kinematic, On_Hit on_hit, On_Hit_Static on_hit_static, usize entity_id) {
	usize id = state.body_list->len;

	// Find inactive Body.
	for (usize i = 0; i < state.body_list->len; ++i) {
		Body *body = array_list_get(state.body_list, i);
		if (!body->is_active) {
			id = i;
			break;
		}
	}

	if (id == state.body_list->len) {
		if (array_list_append(state.body_list, &(Body){0}) == (usize)-1) {
			ERROR_EXIT("Could not append body to list\n");
		}
	}

	Body *body = physics_body_get(id);

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
	};

	return id;
}*/
/*
Body *physics_body_get(usize index) {
	return array_list_get(state.body_list, index);
}*/
/*
usize physics_static_body_create(Vector3D position, Vector3D size, u8 collision_layer) {
	Static_Body static_body = {
		.aabb = {
			.position = { position[0], position[1] },
			.half_size = { size[0] * 0.5, size[1] * 0.5 },
		},
		.collision_layer = collision_layer,
	};

	if (array_list_append(state.static_body_list, &static_body) == (usize)-1)
		ERROR_EXIT("Could not append static body to list\n");

	return state.static_body_list->len - 1;
}*/
/*
usize physics_trigger_create(Vector3D position, Vector3D size, u8 collision_layer, u8 collision_mask, On_Hit on_hit) {
    return physics_body_create(position, size, (Vector3D)(0,0,0), collision_layer, collision_mask, true, on_hit, NULL, (usize)-1);
}
/*
Static_Body *physics_static_body_get(usize index) {
	return array_list_get(state.static_body_list, index);
}*/
/*
usize physics_static_body_count() {
    return state.static_body_list->len;
}*/
/*
void physics_reset(void) {
    state.static_body_list->len = 0;
    state.body_list->len = 0;
}*/
/*
void physics_body_destroy(usize body_id) {
    Body *body = physics_body_get(body_id);
    body->is_active = false;
}*/