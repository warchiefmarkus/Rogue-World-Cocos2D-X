PACKAGE_PATH=__run_package_path__
PROJECT_NAME=__run_project_name__

C:/android-sdk/platform-tools/adb shell exit
C:/android-sdk/platform-tools/adb shell am start -a android.intent.action.MAIN -n $PACKAGE_PATH/$PACKAGE_PATH.$PROJECT_NAME
C:/android-sdk/platform-tools/adb shell logcat