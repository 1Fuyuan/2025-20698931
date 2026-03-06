cmake_minimum_required(VERSION 3.19)
project(QtBaseStation LANGUAGES CXX)

# Qt
find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

# VTK (with Qt widget support)
find_package(VTK REQUIRED COMPONENTS
  CommonCore
  CommonDataModel
  FiltersSources
  InteractionStyle
  RenderingCore
  RenderingOpenGL2
  GUISupportQt
  RenderingOpenVR
)

qt_standard_project_setup()

qt_add_executable(QtBaseStation
  WIN32 MACOSX_BUNDLE
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
)

target_link_libraries(QtBaseStation PRIVATE
  Qt::Core
  Qt::Widgets
  ${VTK_LIBRARIES}
)

# VTK 9: module auto-init (important when using VTK modules)
vtk_module_autoinit(
  TARGETS QtBaseStation
  MODULES ${VTK_LIBRARIES}
)

include(GNUInstallDirs)

# Copy across OpenVR bindings that map controllers
# The program will expect to find these in the build dir when it runs
add_custom_target(VRBindings)

add_custom_command(TARGET VRBindings PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E
    copy_directory ${CMAKE_SOURCE_DIR}/vrbindings ${CMAKE_BINARY_DIR}/vrbindings
)

add_dependencies(QtBaseStation VRBindings)

install(TARGETS QtBaseStation
  BUNDLE  DESTINATION .
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
  TARGET QtBaseStation
  OUTPUT_SCRIPT deploy_script
  NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
