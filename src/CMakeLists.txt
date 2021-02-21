## local variable for managing the gamelib target
set(GAMELIB "ASGENetLib")

## glob is useful but not reliant in compilation so just use it for headers ##
file(GLOB_RECURSE HEADER_LIST
        LIST_DIRECTORIES FALSE
        CONFIGURE_DEPENDS
        ${CMAKE_SOURCE_DIR}/include/ASGENetLib/*.hpp
        ${CMAKE_SOURCE_DIR}/include/ASGENetLib/*.h
        *.hpp *.h)

## cpp files go here, [h]pp files are globbed so don't need to be explicitly added ##
set(GAMELIB_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/GComponent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GCNetClient.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GCNetServer.cpp ../include/GameComponents/TextComponent.cpp ../include/GameComponents/TextComponent.hpp ../include/Utilities/UserClient.h ../include/Utilities/NetUtil.h ../include/GameObjects/GameObject.cpp ../include/GameObjects/GameObject.h ../include/GameObjects/UI/UIButton.cpp ../include/GameObjects/UI/UIButton.h ../include/GameObjects/UI/UITextBox.cpp ../include/GameObjects/UI/UITextBox.h ../include/Utilities/FontManager.cpp ../include/Utilities/FontManager.h ../include/GameObjects/Scenes/TitleScreen.cpp ../include/GameObjects/Scenes/TitleScreen.h ../include/GameObjects/Scenes/GameScene.cpp ../include/GameObjects/Scenes/GameScene.h)

## create the game library
add_library(${GAMELIB} STATIC ${GAMELIB_SOURCES} "${HEADER_LIST}")
add_library(libs::${GAMELIB} ALIAS ${GAMELIB})
target_include_directories(${GAMELIB} PRIVATE ${CMAKE_SOURCE_DIR}/include/${GAMELIB} ".")
target_compile_options(${GAMELIB} PUBLIC $<$<STREQUAL:x${CMAKE_CXX_SIMULATE_ID},xMSVC>:/EHsc>)

## set the build target properties ##
configure_target(${GAMELIB} ${CMAKE_SOURCE_DIR}/include "${HEADER_LIST}" "kissnet::kissnet")
add_asge_dependency(${GAMELIB})