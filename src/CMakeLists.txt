# SFML
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

# Qt
set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Widgets Gui OpenGL REQUIRED)
if (${Qt5_FOUND})
    message("Found Qt: " ${Qt5_VERSION})
endif()

IF (${SFML_Found})
	message("Found SFML")
ENDIF()

find_package(OpenGL)
if (${OpenGL_FOUND})
    message("Found OpenGL")
endif()

add_executable(${PROJECT_NAME} "main.cpp"
"particle.h"
"mymath.h"
"simulation.cpp"
"simulation.h"
"particle.cpp"
"solver.cpp"
"solver.h"
"app.cpp"
"app.h"
"vc.h"
"vc.cpp"
"qsfmlcanvas.h"
"qsfmlcanvas.cpp"
"misc.h"
"labelvaluepair.h"
"labelvaluepair.cpp" "bhgrid.h"  "bhgrid.cpp")

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-system sfml-network sfml-graphics sfml-window)
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets Qt5::OpenGL) 
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL) 