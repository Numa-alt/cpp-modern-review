
# このCMakeLists.txtで使用するCMakeの最低バージョン
cmake_minimum_required(VERSION 3.20)

# プロジェクト名と使用言語を指定
project(cpp-modern-review LANGUAGES CXX)

# CTestによるテスト機能を有効化
enable_testing()

# C++17を使用する
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# gnu++17のようなコンパイラ独自拡張は使わず、標準C++17を使う
set(CMAKE_CXX_EXTENSIONS OFF)

# compile_commands.jsonを生成する
# VS Codeやclangdなどの補完・解析ツールで利用できる
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 警告オプション（core / platform 共通）
if(MSVC)
    set(PUYO_WARN_FLAGS /W4 /utf-8)
else()
    set(PUYO_WARN_FLAGS -Wall -Wextra -Wconversion -Wsign-conversion -Wshadow)
endif()

# ------------------------------------------------------------
# Device関連の共通ライブラリ
# ------------------------------------------------------------

# Device関連の実装を device_core というSTATICライブラリにまとめる
#
# これにより、
#   - メインプログラム
#   - 各テストプログラム
# から同じDevice実装を共通利用できる
add_library(device_core STATIC
    src/device/DeviceManager.cpp
    src/device/MonitorWorker.cpp
    src/device/Motor.cpp
    src/device/TemperatureSensor.cpp
)

# device_coreを利用するターゲットから、
#
#   #include "device/Motor.h"
#
# のように src 配下のヘッダを参照できるようにする
#
# PUBLICなので、device_coreをリンクした側にも
# このinclude pathが引き継がれる
target_include_directories(device_core PUBLIC
    src
)


# ------------------------------------------------------------
# メインプログラム
# ------------------------------------------------------------

# cpp-modern-review という実行ファイルを作る
add_executable(cpp-modern-review
    src/main.cpp
    src/item_manager/ItemManager.cpp
)

# メインプログラムからDevice関連の実装を利用する
target_link_libraries(cpp-modern-review PRIVATE
    device_core
)


# ------------------------------------------------------------
# Motorの単体テスト
# ------------------------------------------------------------

# Motorテスト用の実行ファイルを作る
add_executable(test_motor
    src/tests/test_motor.cpp
)

# test_motorからMotorなどのDevice実装を利用する
#
# device_core側のPUBLIC include pathも引き継がれるので、
# test_motor.cppから
#
#   #include "device/Motor.h"
#
# のように書ける
target_link_libraries(test_motor PRIVATE
    device_core
)


# ------------------------------------------------------------
# CTestへのテスト登録
# ------------------------------------------------------------

# ctest実行時に test_motor を MotorTest という名前で実行する
add_test(
    NAME MotorTest
    COMMAND test_motor
)

# ------------------------------------------------------------
# TemperatureSensorの単体テスト
# ------------------------------------------------------------

# Temperatureテスト用の実行ファイルを作る
add_executable(test_temperature_sensor
    src/tests/test_temperature_sensor.cpp
)

# test_temperature_sensorからTemperatureSensorなどのDevice実装を利用する
#
# device_core側のPUBLIC include pathも引き継がれるので、
# test_temperature_sensor.cppから
#
#   #include "device/TemperatureSensor.h"
#
# のように書ける
target_link_libraries(test_temperature_sensor PRIVATE
    device_core
)


# ------------------------------------------------------------
# CTestへのテスト登録
# ------------------------------------------------------------

# ctest実行時に test_temperature を TemperatureSensorTest という名前で実行する
add_test(
    NAME TemperatureSensorTest
    COMMAND test_temperature_sensor
)


# ------------------------------------------------------------
# ThreadSafeQueueの単体テスト
# ------------------------------------------------------------

# ThreadSafeQueueテスト用の実行ファイルを作る
add_executable(test_thread_safe_queue
    src/tests/test_thread_safe_queue.cpp
)

# test_thread_safe_queueからThreadSafeQueueなどのDevice実装を利用する
#
# device_core側のPUBLIC include pathも引き継がれるので、
# test_thread_test_queue.cppから
#
#   #include "device/ThreadSafeQueue.h"
#
# のように書ける
target_link_libraries(test_thread_safe_queue PRIVATE
    device_core
)


# ------------------------------------------------------------
# CTestへのテスト登録
# ------------------------------------------------------------

# ctest実行時に test_thread_safe_queue を ThreadSafeQueueTest という名前で実行する
add_test(
    NAME ThreadSafeQueueTest
    COMMAND test_thread_safe_queue
)

# ------------------------------------------------------------
# MonitorWorkerの単体テスト
# ------------------------------------------------------------

# MonitorWorkerテスト用の実行ファイルを作る
add_executable(test_monitor_worker
    src/tests/test_monitor_worker.cpp
)

# test_monitor_workerからMonitorWorkerなどのDevice実装を利用する
#
# device_core側のPUBLIC include pathも引き継がれるので、
# test_monitor_worker.cppから
#
#   #include "device/MonitorWorker.h"
#
# のように書ける
target_link_libraries(test_monitor_worker PRIVATE
    device_core
)


# ------------------------------------------------------------
# CTestへのテスト登録
# ------------------------------------------------------------

# ctest実行時に test_monitor_worker を MonitorWorkerTest という名前で実行する
add_test(
    NAME MonitorWorkerTest
    COMMAND test_monitor_worker
)
