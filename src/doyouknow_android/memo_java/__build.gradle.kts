import com.android.build.api.dsl.AaptOptions

plugins {
    alias(libs.plugins.android.application)
}

android {
    namespace = "com.example.testapi32"
    compileSdk = 34

    androidResources {
        //noCompress += listOf("txt")
        //noCompress += listOf("so")
    }

    packaging {
        resources {
            //excludes += listOf("META-INF/SomeFile.txt")
            //jniLibs.pickFirsts.add("/vendor/lib64/libOpenCLs.so")
            //jniLibs.pickFirsts.add("/vendor/lib64/egl/libGLES_mali.so")
            //pickFirsts.add("/vendor/lib64/libOpenCLs.so")
            //pickFirsts.add("/vendor/lib64/egl/libGLES_mali.so")
        }
    }

    defaultConfig {
        applicationId = "com.example.testapi32"
        minSdk = 32
        targetSdk = 34
        versionCode = 1
        versionName = "1.0"
        testInstrumentationRunner = "androidx.test.runner.AndroidJUnitRunner"
        externalNativeBuild {
            cmake {
                //cFlags += listOf("-DSomeFlagIsDefine")
                //cppFlags += listOf("-DSomeFlagIsValue=1234")
            }
            ndk {
                abiFilters += listOf("arm64-v8a")
            }
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
            proguardFiles(getDefaultProguardFile("proguard-android-optimize.txt"), "proguard-rules.pro")
            signingConfig = signingConfigs.getByName("debug")
        }
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_1_8
        targetCompatibility = JavaVersion.VERSION_1_8
    }

    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }
    }

}

dependencies {
    implementation(libs.appcompat)
    implementation(libs.material)
    implementation(libs.activity)
    implementation(libs.constraintlayout)
    testImplementation(libs.junit)
    androidTestImplementation(libs.ext.junit)
    androidTestImplementation(libs.espresso.core)
}