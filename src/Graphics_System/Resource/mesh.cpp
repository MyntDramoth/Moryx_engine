#include "mesh.h"

#include "../Graphics/graphics_engine.h"


#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include "resource_manager.h"
#include "../../Game/game.h"

#include <filesystem>
#include <iostream>
#include <exception>

Mesh::Mesh(const wchar_t* full_path, Resource_Manager* manager):Resource(full_path, manager) {

    if(!std::filesystem::exists(full_path)) {
        MORYX_ERROR("File path is wrong or file does not exist!" << " || File name: " << std::filesystem::path(full_path).filename()<<"\n");
    }

    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    
    std::string warn, error;

    auto input_file = std::filesystem::path(full_path).string();

    std::string mtl_dir = input_file.substr(0,input_file.find_last_of("\\/"));

    bool res = tinyobj::LoadObj(&attribs,&shapes,&materials,&warn,&error,input_file.c_str(),mtl_dir.c_str());

    if(!error.empty() || !res) {
        MORYX_ERROR("Failed to load Mesh!");
    }

    std::vector<Vertex_Mesh> vertices;
    std::vector<unsigned int> indeces;

    size_t size_of_verts_and_indeces = 0;

    for(size_t s = 0; s < shapes.size();s++) {
        size_of_verts_and_indeces += shapes[s].mesh.indices.size();
    }

    vertices.reserve(size_of_verts_and_indeces);
    indeces.reserve(size_of_verts_and_indeces);
    material_slots.resize(materials.size());

    size_t index_global_offset = 0;

    for(size_t m = 0; m < materials.size();m++) { 

        material_slots[m].start_index = index_global_offset;
        material_slots[m].material_id = m;

        for(size_t s = 0; s < shapes.size();s++) {

            size_t index_offset = 0;

            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size();f++) {

                unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];
                
                if(shapes[s].mesh.material_ids[f] != m) {
                    index_offset += num_face_verts;
                    continue;
                }


                Vector3D vert_face[3];
                Vector2D uv_face[3];
                for(unsigned char verts = 0; verts < num_face_verts;verts++) {
                    tinyobj::index_t index = shapes[s].mesh.indices[index_offset + verts];

                    tinyobj::real_t vert_Xpos = attribs.vertices[index.vertex_index * 3 + 0];
                    tinyobj::real_t vert_Ypos = attribs.vertices[index.vertex_index * 3 + 1];
                    tinyobj::real_t vert_Zpos = -attribs.vertices[index.vertex_index * 3 + 2];

                    tinyobj::real_t tex_Xpos = attribs.texcoords[index.texcoord_index * 2 + 0];
                    tinyobj::real_t tex_Ypos = attribs.texcoords[index.texcoord_index * 2 + 1];

                    vert_face[verts] = Vector3D(vert_Xpos,vert_Ypos,vert_Zpos);
                    uv_face[verts] = Vector2D(tex_Xpos,tex_Ypos);
                }

                Vector3D tangent, binormal;

                compute_tangents(vert_face[0],vert_face[1],vert_face[2],uv_face[0],uv_face[1],uv_face[2],tangent,binormal);

                for(unsigned char verts = 0; verts < num_face_verts;verts++) {

                    tinyobj::index_t index = shapes[s].mesh.indices[index_offset + verts];

                    tinyobj::real_t vert_Xpos = attribs.vertices[index.vertex_index * 3 + 0];
                    tinyobj::real_t vert_Ypos = attribs.vertices[index.vertex_index * 3 + 1];
                    tinyobj::real_t vert_Zpos = -attribs.vertices[index.vertex_index * 3 + 2];

                    tinyobj::real_t tex_Xpos = attribs.texcoords[index.texcoord_index * 2 + 0];
                    tinyobj::real_t tex_Ypos = attribs.texcoords[index.texcoord_index * 2 + 1];

                    tinyobj::real_t norm_Xpos = attribs.normals[index.normal_index * 3 + 0];
                    tinyobj::real_t norm_Ypos = attribs.normals[index.normal_index * 3 + 1];
                    tinyobj::real_t norm_Zpos = -attribs.normals[index.normal_index * 3 + 2];

                    Vector3D v_tangent, v_binormal;
                    v_binormal = Vector3D::cross(Vector3D(norm_Xpos,norm_Ypos,norm_Zpos),tangent);
                    v_tangent = Vector3D::cross(v_binormal,Vector3D(norm_Xpos,norm_Ypos,norm_Zpos));

                    Vertex_Mesh vertex(Vector3D(vert_Xpos,vert_Ypos,vert_Zpos),Vector2D(tex_Xpos,tex_Ypos),Vector3D(norm_Xpos,norm_Ypos,norm_Zpos),v_tangent,v_binormal);
                    vertices.push_back(vertex);
                    indeces.push_back((unsigned int)index_global_offset + verts);
                }

                index_offset += num_face_verts;
                index_global_offset += num_face_verts;
            }
        }

        material_slots[m].num_indeces = index_global_offset - material_slots[m].start_index;
    }

    auto render_sys = manager->get_game()->get_graphics_engine()->get_render_system();

    vertex_buffer = render_sys->create_vertex_buffer(&vertices[0],sizeof(Vertex_Mesh),(UINT)vertices.size());
    index_buffer = render_sys->create_index_buffer(&indeces[0],(UINT)indeces.size());
}

Mesh::Mesh(Vertex_Mesh *vert_list, UINT vert_list_size, UINT *index_list, UINT index_list_size, Material_Slot *material_slot_list, UINT slot_list_size, Resource_Manager* manager):Resource(L"",manager) {
    auto render_sys = manager->get_game()->get_graphics_engine()->get_render_system();

    vertex_buffer = render_sys->create_vertex_buffer(vert_list,sizeof(Vertex_Mesh),vert_list_size);
    index_buffer = render_sys->create_index_buffer(index_list,index_list_size);
    material_slots.resize(slot_list_size);
    for(UINT i =0; i < slot_list_size;i++) {
        material_slots[i] = material_slot_list[i];
    }
}

Mesh::Mesh(const wchar_t *full_path, Resource_Manager *manager, Instance_Data *inst_list, UINT instance_list_size):Resource(full_path, manager)
{
     if(!std::filesystem::exists(full_path)) {
        MORYX_ERROR("File path is wrong or file does not exist!" << " || File name: " << std::filesystem::path(full_path).filename()<<"\n");
    }

    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    
    std::string warn, error;

    auto input_file = std::filesystem::path(full_path).string();

    std::string mtl_dir = input_file.substr(0,input_file.find_last_of("\\/"));

    bool res = tinyobj::LoadObj(&attribs,&shapes,&materials,&warn,&error,input_file.c_str(),mtl_dir.c_str());

    if(!error.empty() || !res) {
        MORYX_ERROR("Failed to load Mesh!");
    }

    std::vector<Vertex_Mesh> vertices;
    std::vector<unsigned int> indeces;

    size_t size_of_verts_and_indeces = 0;

    for(size_t s = 0; s < shapes.size();s++) {
        size_of_verts_and_indeces += shapes[s].mesh.indices.size();
    }

    vertices.reserve(size_of_verts_and_indeces);
    indeces.reserve(size_of_verts_and_indeces);
    material_slots.resize(materials.size());

    size_t index_global_offset = 0;

    for(size_t m = 0; m < materials.size();m++) { 

        material_slots[m].start_index = index_global_offset;
        material_slots[m].material_id = m;

        for(size_t s = 0; s < shapes.size();s++) {

            size_t index_offset = 0;

            for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size();f++) {

                unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];
                
                if(shapes[s].mesh.material_ids[f] != m) {
                    index_offset += num_face_verts;
                    continue;
                }


                Vector3D vert_face[3];
                Vector2D uv_face[3];
                for(unsigned char verts = 0; verts < num_face_verts;verts++) {
                    tinyobj::index_t index = shapes[s].mesh.indices[index_offset + verts];

                    tinyobj::real_t vert_Xpos = attribs.vertices[index.vertex_index * 3 + 0];
                    tinyobj::real_t vert_Ypos = attribs.vertices[index.vertex_index * 3 + 1];
                    tinyobj::real_t vert_Zpos = -attribs.vertices[index.vertex_index * 3 + 2];

                    tinyobj::real_t tex_Xpos = attribs.texcoords[index.texcoord_index * 2 + 0];
                    tinyobj::real_t tex_Ypos = attribs.texcoords[index.texcoord_index * 2 + 1];

                    vert_face[verts] = Vector3D(vert_Xpos,vert_Ypos,vert_Zpos);
                    uv_face[verts] = Vector2D(tex_Xpos,tex_Ypos);
                }

                Vector3D tangent, binormal;

                compute_tangents(vert_face[0],vert_face[1],vert_face[2],uv_face[0],uv_face[1],uv_face[2],tangent,binormal);

                for(unsigned char verts = 0; verts < num_face_verts;verts++) {

                    tinyobj::index_t index = shapes[s].mesh.indices[index_offset + verts];

                    tinyobj::real_t vert_Xpos = attribs.vertices[index.vertex_index * 3 + 0];
                    tinyobj::real_t vert_Ypos = attribs.vertices[index.vertex_index * 3 + 1];
                    tinyobj::real_t vert_Zpos = -attribs.vertices[index.vertex_index * 3 + 2];

                    tinyobj::real_t tex_Xpos = attribs.texcoords[index.texcoord_index * 2 + 0];
                    tinyobj::real_t tex_Ypos = attribs.texcoords[index.texcoord_index * 2 + 1];

                    tinyobj::real_t norm_Xpos = attribs.normals[index.normal_index * 3 + 0];
                    tinyobj::real_t norm_Ypos = attribs.normals[index.normal_index * 3 + 1];
                    tinyobj::real_t norm_Zpos = -attribs.normals[index.normal_index * 3 + 2];

                    Vector3D v_tangent, v_binormal;
                    v_binormal = Vector3D::cross(Vector3D(norm_Xpos,norm_Ypos,norm_Zpos),tangent);
                    v_tangent = Vector3D::cross(v_binormal,Vector3D(norm_Xpos,norm_Ypos,norm_Zpos));

                    Vertex_Mesh vertex(Vector3D(vert_Xpos,vert_Ypos,vert_Zpos),Vector2D(tex_Xpos,tex_Ypos),Vector3D(norm_Xpos,norm_Ypos,norm_Zpos),v_tangent,v_binormal);
                    vertices.push_back(vertex);
                    indeces.push_back((unsigned int)index_global_offset + verts);
                }

                index_offset += num_face_verts;
                index_global_offset += num_face_verts;
            }
        }

        material_slots[m].num_indeces = index_global_offset - material_slots[m].start_index;
    }

    auto render_sys = manager->get_game()->get_graphics_engine()->get_render_system();

    vertex_buffer = render_sys->create_vertex_buffer(&vertices[0],sizeof(Vertex_Mesh),(UINT)vertices.size());
    inst_buffer = render_sys->create_instance_buffer(inst_list,sizeof(Instance_Data),instance_list_size);
    index_buffer = render_sys->create_index_buffer(&indeces[0],(UINT)indeces.size());
}

Mesh::Mesh(Vertex_Mesh *vert_list, UINT vert_list_size, UINT *index_list, UINT index_list_size, Instance_Data *inst_list, UINT instance_list_size, Material_Slot *material_slot_list, UINT slot_list_size, Resource_Manager *manager):Resource(L"", manager) {
    auto render_sys = manager->get_game()->get_graphics_engine()->get_render_system();

    vertex_buffer = render_sys->create_vertex_buffer(vert_list,sizeof(Vertex_Mesh),vert_list_size);
    inst_buffer = render_sys->create_instance_buffer(inst_list,sizeof(Instance_Data),instance_list_size);
    index_buffer = render_sys->create_index_buffer(index_list,index_list_size);
    material_slots.resize(slot_list_size);
    for(UINT i =0; i < slot_list_size;i++) {
        material_slots[i] = material_slot_list[i];
    }
}

Mesh::~Mesh() {

}


Material_Slot Mesh::get_material_slot(UINT slot) {
   if(slot >= material_slots.size()) {return Material_Slot();}
   return material_slots[slot];
}

size_t Mesh::get_num_materials() {
    return material_slots.size();
}

void Mesh::compute_tangents(
    const Vector3D &v0, const Vector3D &v1, const Vector3D &v2, 
    const Vector2D &t0, const Vector2D &t1, const Vector2D &t2, 
    Vector3D &tangent, Vector3D &binormal) {
        
    Vector3D delta_pos1 = v1 - v0;
    Vector3D delta_pos2 = v2 - v0;

    Vector2D delta_UV1 = t1 - t0;
    Vector2D delta_UV2 = t2 - t0;

    float r = 1.0f/((delta_UV1.x * delta_UV2.y) - (delta_UV1.y * delta_UV2.x));

    tangent = ((delta_pos1 * delta_UV2.y) - (delta_pos2 * delta_UV1.y));
    tangent = Vector3D::normalize(tangent);

    binormal = ((delta_pos2 * delta_UV1.x) - (delta_pos1 * delta_UV2.x));
    binormal = Vector3D::normalize(binormal);
}
