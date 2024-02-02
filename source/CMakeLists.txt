add_library(autopilot SHARED)
target_compile_definitions(autopilot PRIVATE -DAUTOPILOT_EXPORTS)
target_include_directories(autopilot PRIVATE ${inface_INCLUDE_DIR})
target_sources(autopilot 
INTERFACE
        ${inface_INCLUDE_DIR}/autopilot.h
        global.define.hpp
PRIVATE
        # module.error.cpp
        # module.impl.cpp
        # module.inface.cpp
        module.string.cpp
        # module.task.cpp
)

