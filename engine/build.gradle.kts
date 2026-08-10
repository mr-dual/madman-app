plugins {
    id("com.android.library")
}

android {
    namespace = "com.madman.engine"
    compileSdk = 37
    ndkVersion = "29.0.14206865"
    ndkPath = "/data/data/com.termux/files/home/android-ndk-r29"

    defaultConfig {
        minSdk = 24  

        externalNativeBuild {
            cmake {
                arguments(
                    "-DANDROID_STL=c++_shared", 
                    "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON"
                )
                cppFlags("-std=c++20")
            }
        }
    }

    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1+"
        }
    }
}

