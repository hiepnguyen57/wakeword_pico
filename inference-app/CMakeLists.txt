cmake_minimum_required(VERSION 3.12)

# initialize pico_sdk from GIT
# (note this can come from environment, CMake cache etc)
# set(PICO_SDK_FETCH_FROM_GIT on)

# pico_sdk_import.cmake is a single file copied from this SDK
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(pico_inference_app)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

# initialize the Pico SDK
pico_sdk_init()

# Define ARM_CPU, CMSIS ROOT and DSP to use CMSIS-DSP
# set(ARM_CPU "cortex-m0plus")
# set(ROOT ${CMAKE_CURRENT_LIST_DIR}/lib/CMSIS_5)
# set(DSP ${ROOT}/CMSIS/DSP)
# set(CONFIGTABLE ON)
# set(RFFT_Q15_256 ON)
# set(ALLFAST ON)
# include CMSIS-DSP .cmake for GCC Toolchain
# include(${DSP}/Toolchain/GCC.cmake)
# add CMSIS-DSP Source directory as subdirectory
# add_subdirectory(${DSP}/Source EXCLUDE_FROM_ALL)

add_executable(pico_inference_app "")

set(PICO_TFLMICRO_MICRO_SPEECH_PATH ${CMAKE_CURRENT_LIST_DIR}/lib/pico-tflmicro/examples/micro_speech)

target_include_directories(pico_inference_app
  PRIVATE
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/.
)

set_target_properties(
  pico_inference_app
  PROPERTIES
  COMPILE_FLAGS -fno-rtti
  COMPILE_FLAGS -fno-exceptions
  COMPILE_FLAGS -fno-threadsafe-statics
  COMPILE_FLAGS -nostdlib
)

target_sources(pico_inference_app
  PRIVATE
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/fft.cpp
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/fft_util.cpp
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/filterbank.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/filterbank_util.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/frontend.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/frontend_util.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/log_lut.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/log_scale.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/log_scale_util.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/noise_reduction.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/noise_reduction_util.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/pcan_gain_control.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/pcan_gain_control_util.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/window.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/window_util.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/feature_provider.cpp
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/micro_features/micro_features_generator.cpp
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/micro_features/micro_model_settings.cpp
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/micro_features/model.cpp
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/recognize_commands.cpp
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/micro/tools/make/downloads/kissfft/kiss_fft.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/micro/tools/make/downloads/kissfft/tools/kiss_fftr.c
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/bits.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/fft.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/fft_util.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/filterbank.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/filterbank_util.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/frontend.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/frontend_util.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/log_lut.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/log_scale.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/log_scale_util.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/noise_reduction.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/noise_reduction_util.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/pcan_gain_control.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/pcan_gain_control_util.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/window.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/experimental/microfrontend/lib/window_util.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/audio_provider.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/feature_provider.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/micro_features/micro_features_generator.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/micro_features/micro_features_generator.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/micro_features/micro_model_settings.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/micro_features/model.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/recognize_commands.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/micro/tools/make/downloads/kissfft/COPYING
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/micro/tools/make/downloads/kissfft/_kiss_fft_guts.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/micro/tools/make/downloads/kissfft/kiss_fft.h
  ${PICO_TFLMICRO_MICRO_SPEECH_PATH}/tensorflow/lite/micro/tools/make/downloads/kissfft/tools/kiss_fftr.h
  ${CMAKE_CURRENT_LIST_DIR}/src/pdm_audio_provider.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/command_responder.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
  ${CMAKE_CURRENT_LIST_DIR}/src/main_functions.cpp
)

# CMSISDSPTransform CMSISDSPSupport CMSISDSPCommon CMSISDSPComplexMath CMSISDSPFastMath CMSISDSPBasicMath
target_link_libraries(pico_inference_app
  pico-tflmicro
  pico_pdm_microphone
  hardware_adc
  hardware_dma
  hardware_pwm
  hardware_pio
)

# enable usb output, disable uart output
pico_enable_stdio_usb(pico_inference_app 1)
pico_enable_stdio_uart(pico_inference_app 0)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(pico_inference_app)

add_subdirectory("lib/microphone-library-for-pico" EXCLUDE_FROM_ALL)
add_subdirectory("lib/pico-tflmicro" EXCLUDE_FROM_ALL)

