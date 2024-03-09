#include "resource_manager.h"

#if __cplusplus <= 201402L 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#if __cplusplus >= 201703L
#include <filesystem>
#endif

Resource_Manager::Resource_Manager() {

}

Resource_Manager::~Resource_Manager() {

}

resource_sptr Resource_Manager::create_resource_from_file(const wchar_t *file_path) {
    
   #if (_MSC_VER >= 1900 && _MSC_VER <= 1916)  || ( _MSC_VER >= 1920 && __cplusplus <= 201402L) 
	std::wstring full_path = std::experimental::filesystem::absolute(file_path);
    #endif

    #if _MSC_VER >= 1920 && __cplusplus > 201402L 
        std::wstring full_path = std::filesystem::absolute(file_path);
    #endif

    auto iterator = resources_map.find(full_path);

    if(iterator != resources_map.end()) {
        return iterator->second;
    }

    Resource* raw_resource = this->create_resource_from_file_concrete(full_path.c_str());

    if(raw_resource) {
        resource_sptr res{raw_resource};
        resources_map[full_path] = res;
        return res;
    }

    return nullptr;
}
