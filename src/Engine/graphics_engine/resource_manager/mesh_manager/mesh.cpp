#include "mesh.h"

#include "../../graphics_engine.h"
#include "../../../math/vertex_mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <locale>
#include <filesystem>

Mesh::Mesh(const wchar_t* full_path):Resource(full_path) {

    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    
    std::string warn, error;

    auto input_file = std::filesystem::path(full_path).string();

    bool res = tinyobj::LoadObj(&attribs,&shapes,&materials,&warn,&error,input_file.c_str());

    if(!error.empty() || !res) {
        throw std::exception("Failed to load Mesh!");
    }

    std::vector<Vertex_Mesh> vertices;
    std::vector<unsigned int> indeces;

    // ONLY WORKS FOR SINGLE FACED/SHAPED MESH AT THE MOMENT

    for(size_t s = 0; s < shapes.size();s++) {

        size_t index_offset = 0;
        vertices.reserve(shapes[s].mesh.indices.size());
        indeces.reserve(shapes[s].mesh.indices.size());

        for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size();f++) {

            unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

            for(unsigned char verts = 0; verts < num_face_verts;verts++) {

                tinyobj::index_t index = shapes[s].mesh.indices[index_offset + verts];

                tinyobj::real_t vert_Xpos = attribs.vertices[index.vertex_index * 3 + 0];
                tinyobj::real_t vert_Ypos = attribs.vertices[index.vertex_index * 3 + 1];
                tinyobj::real_t vert_Zpos = attribs.vertices[index.vertex_index * 3 + 2];

                tinyobj::real_t tex_Xpos = attribs.texcoords[index.texcoord_index * 2 + 0];
                tinyobj::real_t tex_Ypos = attribs.texcoords[index.texcoord_index * 2 + 1];

                tinyobj::real_t norm_Xpos = attribs.normals[index.normal_index * 3 + 0];
                tinyobj::real_t norm_Ypos = attribs.normals[index.normal_index * 3 + 1];
                tinyobj::real_t norm_Zpos = attribs.normals[index.normal_index * 3 + 2];

                Vertex_Mesh vertex(Vector3D(vert_Xpos,vert_Ypos,vert_Zpos),Vector2D(tex_Xpos,tex_Ypos),Vector3D(norm_Xpos,norm_Ypos,norm_Zpos));
                vertices.push_back(vertex);
                indeces.push_back((unsigned int)index_offset + verts);
            }

            index_offset += num_face_verts;

        }
    }

    void* shader_byte_code = nullptr;
    size_t shader_size = 0;

    Graphics_Engine::get_engine()->get_vert_mesh_layout_shader_data(&shader_byte_code,&shader_size);

    vertex_buffer = Graphics_Engine::get_engine()->get_render_system()->create_vertex_buffer(&vertices[0],sizeof(Vertex_Mesh),(UINT)vertices.size(),shader_byte_code,(UINT)shader_size);
    index_buffer = Graphics_Engine::get_engine()->get_render_system()->create_index_buffer(&indeces[0],(UINT)indeces.size());
}

Mesh::~Mesh() {

}

const vert_buffer_sptr &Mesh::get_vert_buffer() {
    return vertex_buffer;
}

const index_buffer_sptr &Mesh::get_index_buffer() {
    return index_buffer;
}
