# esp32-DHT-data-monitoring-on-Android-app
Monitor DHT sensor data on an Android application, using Firebase

<img width="341" alt="Capture" src="https://github.com/Marouarad/esp32-DHT-data-monitoring-on-Android-app/assets/114839150/7acdf4c1-a1b8-47a7-8060-0fbbeb619a0e">

# Requirements:
Before getting started, make sure you have the following:

-An ESP32 module.

-DHT sensor

-Arduino IDE installed with ESP32 support.

-Android Studio installed.

-A Firebase account.
# ESP32 Configuration
1- Open the Arduino code located in the "espdht" directory.

2- Ensure you have properly configured Wi-Fi settings, DHT pin and Firebase credentials in the code.

3- Upload the code to your ESP32.

4- The DHT sensor data will be automatically sent to Firebase.

<img width="287" alt="FIREBASE" src="https://github.com/Marouarad/esp32-DHT-data-monitoring-on-Android-app/assets/114839150/08a83ceb-7ac1-4e7b-ad71-92970acb966b">

# Android Application Setup

1. **Copy Code**: Copy the contents of `MainActivity.java` and `activity_main.xml` from the "android_app" directory to the respective locations in your Android Studio project.

2. **Firebase Configuration**: Ensure that you have the necessary Firebase dependencies and configuration files (e.g., `google-services.json`) correctly set up in your Android project.

3. **Firebase Dependencies**: Add the Firebase dependencies to your Android project. You can do this by modifying the `build.gradle` (Module: app) file. Refer to the [Firebase documentation](https://firebase.google.com/docs/android/setup) for the required dependencies.

5. **Testing**: Compile and run your Android application using Android Studio.

   <img width="160" alt="APP" src="https://github.com/Marouarad/esp32-DHT-data-monitoring-on-Android-app/assets/114839150/251ec076-9740-4c48-9372-80150ad4cb3d">




