#include "resource.h"

Resource::Resource(const wchar_t* full_path, Resource_Manager* manager): i_full_path(full_path), manager(manager) {

}

Resource::~Resource() {

}