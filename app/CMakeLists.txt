# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library( # Sets the name of the library.
             nativeEgl

             # Sets the library as a shared library.
             SHARED

             # cainfilter
             src/main/cpp/cainfilter/GLImageFilter.cpp
             src/main/cpp/cainfilter/GLImageInputFilter.cpp

             src/main/cpp/cainfilter/adjust/GLBrightnessImageFilter.cpp
             src/main/cpp/cainfilter/adjust/GLContrastImageFilter.cpp
             src/main/cpp/cainfilter/adjust/GLExposureImageFilter.cpp
             src/main/cpp/cainfilter/adjust/GLHueImageFilter.cpp
             src/main/cpp/cainfilter/adjust/GLSaturationImageFilter.cpp
             src/main/cpp/cainfilter/adjust/GLSharpnessImageFilter.cpp

             src/main/cpp/cainfilter/input/ABGRImageInputFilter.cpp
             src/main/cpp/cainfilter/input/ARGBImageInputFilter.cpp
             src/main/cpp/cainfilter/input/BGRImageInputFilter.cpp
             src/main/cpp/cainfilter/input/I420ImageInputFilter.cpp
             src/main/cpp/cainfilter/input/NV12ImageInputFilter.cpp
             src/main/cpp/cainfilter/input/NV21ImageInputFilter.cpp
             src/main/cpp/cainfilter/input/RGBImageInputFilter.cpp

             # caingles
             src/main/cpp/caingles/EglCore.cpp
             src/main/cpp/caingles/EglSurfaceBase.cpp
             src/main/cpp/caingles/GlShaders.cpp
             src/main/cpp/caingles/GlUtils.cpp
             src/main/cpp/caingles/OffscreenSurface.cpp
             src/main/cpp/caingles/WindowSurface.cpp

             # cainrender
             src/main/cpp/cainrender/GLRender.cpp

             # common
             src/main/cpp/common/Looper.cpp
             src/main/cpp/common/MyLooper.cpp

             src/main/cpp/NativeEglController.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

find_library( EGL-lib EGL )
find_library( GLESv2-lib GLESv2 )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
                       nativeEgl

                       # Links the target library to the log library
                       # included in the NDK.
                       -ljnigraphics
                       -landroid
                       ${log-lib}
                       ${EGL-lib}
                       ${GLESv2-lib} )