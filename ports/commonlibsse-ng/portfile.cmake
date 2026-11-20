vcpkg_from_github(
        OUT_SOURCE_PATH SOURCE_PATH
        # MinLL/CommonLibVR: MIT continuation of CommonLibSSE NG from v4.39.3 (upstream is GPL-3.0 from v5.0.0).
        # v4.39.5 adds Skyrim 1.7.99 / 1.7.104 support (format-5 address library, AddressLibraryV5 plugin bit).
        REPO MinLL/CommonLibVR
        REF 550cc4fb9114649dcf526d1f3d73d710c5d7003b # v4.39.5
        SHA512 a053d852b682d597acc9e7684740ab95f212e79542265a3e379ff0132bb333592051ddaa2ffc81b1f85fdbda080afe360f5dc7a54d15d1aa7982a98865ce7243
        HEAD_REF ng
)

vcpkg_from_github(
    OUT_SOURCE_PATH OPENVR_PATH
    REPO ValveSoftware/openvr
    REF 60eb187801956ad277f1cae6680e3a410ee0873b # the extern/openvr submodule commit of v4.39.5
    SHA512 bb85b4705e7095ac65df9969112b2df8930cee7917cc5f14231c5a0ffeed7a73ffa60727fd32f8786a403656f95a3ec0f80bf3ceabc5b8ede964aefb920bc718
)

# install(DIRECTORY "${OPENVR_PATH}/" DESTINATION "${SOURCE_PATH}/extern/openvr/")
file(INSTALL "${OPENVR_PATH}/headers/openvr.h" DESTINATION "${SOURCE_PATH}/extern/openvr/headers")

# Only openvr.h is fetched. CommonLib resolves the OpenVR functions it uses at runtime with GetProcAddress,
# so drop the openvr_api.lib link: it is not in the archive, and its buildtree path would end up in the
# exported CMake config.
vcpkg_replace_string("${SOURCE_PATH}/CMakeLists.txt"
        [["$<$<BOOL:${ENABLE_SKYRIM_VR}>:${OPENVR_LIB_DIR}/openvr_api.lib>"]]
        "")

vcpkg_configure_cmake(
        SOURCE_PATH "${SOURCE_PATH}"
        PREFER_NINJA
        OPTIONS -DBUILD_TESTS=off -DSKSE_SUPPORT_XBYAK=on -DCOMMONLIB_PREBUILT=OFF
)

vcpkg_install_cmake()
vcpkg_cmake_config_fixup(PACKAGE_NAME CommonLibSSE CONFIG_PATH lib/cmake)
vcpkg_copy_pdbs()

file(GLOB CMAKE_CONFIGS "${CURRENT_PACKAGES_DIR}/share/CommonLibSSE/CommonLibSSE/*.cmake")
file(INSTALL ${CMAKE_CONFIGS} DESTINATION "${CURRENT_PACKAGES_DIR}/share/CommonLibSSE")
file(INSTALL "${SOURCE_PATH}/cmake/CommonLibSSE.cmake" DESTINATION "${CURRENT_PACKAGES_DIR}/share/CommonLibSSE")

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")
file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/share/CommonLibSSE/CommonLibSSE")

file(INSTALL "${OPENVR_PATH}/headers/openvr.h" DESTINATION "${CURRENT_PACKAGES_DIR}/include")

file(
        INSTALL "${SOURCE_PATH}/LICENSE"
        DESTINATION "${CURRENT_PACKAGES_DIR}/share/${PORT}"
        RENAME copyright)
