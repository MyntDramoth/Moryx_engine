#pragma once
#include <chrono>
#include <lua.hpp>

#include "game_engine.h"

#include <thread>
#include <mutex>
#include <atomic>
void  work_thread(float mpos, Game* game, FastNoise::SmartNode<FastNoise::Simplex> i_simplex);
class Game
{
public:
    Game();
    virtual ~Game();

    void run();
    void quit();

    Graphics_Engine* get_graphics_engine() { return graphics.get();}
    entity_handler* get_entity_handler() {return handler.get();}
    std::vector<Instance_Data> get_instance_data() {return inst_data;}
    
    void StartTerrainThread(float move,FastNoise::SmartNode<FastNoise::Simplex> i_simplex) {
        terrain_processing_done = true;
        std::thread terrainThread(work_thread, move,this,i_simplex);
        terrainThread.detach(); // Run asynchronously
    };
    std::mutex data_mutex;
    std::atomic<bool> terrain_processing_done = false;
    //FastNoise::SmartNode<FastNoise::Simplex> i_simplex;
    std::vector<Instance_Data> inst_data = {};

protected:
    virtual void on_create() {};
    virtual void on_update(float delta_time) {};
    virtual void on_quit() {};

   
    
private:
    void on_display_size_change(const Rect& size);
    void on_update_internal();

    std::unique_ptr<Input_System> input;
    std::unique_ptr<Graphics_Engine> graphics;
    std::unique_ptr<Display> display;
    std::unique_ptr<Resource_Manager> resource_manager;
    std::unique_ptr<entity_handler> handler;
    std::unique_ptr<Physics> physics;
    bool is_running = true;


    std::chrono::system_clock::time_point previous_time;
    mesh_sptr tile_mesh;
   
    //------------------------
    // TEMP RESOURCE STORAGE
    //------------------------
    float move = 0;
    
    size_t tile_data[100][100][10];
    
    mesh_sptr mesh;
    material_sptr material;

    flecs::entity player;
    flecs::entity cam;
    flecs::entity text;

    float rot_y = 0;
    float rot_x = 0;
    float rot = 0;
    Vector3D cam_pos;

    static void hit_sprite(Body *self, Body *other, Hit hit) { other->velocity.y = 0.0f;};
    static void hit_sprite_stat(Body *self, Static_Body *other, Hit hit) {std::cout<<"hit static!\n";};

    friend class Graphics_Engine;
    friend class Display;
};

 