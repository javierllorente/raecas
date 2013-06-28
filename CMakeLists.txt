project(raecas)
 
find_package(KDE4 REQUIRED)
include(KDE4Defaults)

include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${KDE4_INCLUDES}
   )

set(raecas_SRCS raecas.cpp libqrae.cpp)

kde4_add_plugin(plasma_applet_raecas ${raecas_SRCS})
target_link_libraries(plasma_applet_raecas 
                      ${KDE4_PLASMA_LIBS} ${KDE4_KDEUI_LIBS})
 
install(TARGETS plasma_applet_raecas
        DESTINATION ${PLUGIN_INSTALL_DIR})
 
install(FILES plasma-applet-raecas.desktop
        DESTINATION ${SERVICES_INSTALL_DIR})
        
kde4_install_icons(${ICON_INSTALL_DIR})