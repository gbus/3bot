cmake_minimum_required(VERSION 2.8)
project( camcv )
SET(COMPILE_DEFINITIONS -Werror)

find_package( OpenCV REQUIRED )
include_directories(/opt/vc/host_applications/linux/libs/bcm_host/include)
include_directories(/opt/vc/interface/vcos)
include_directories(/opt/vc)
include_directories(/opt/vc/interface/vcos/pthreads)
include_directories(/opt/vc/interface/vmcs_host/linux)
add_executable(dumpimg RaspiCamControl.c RaspiCLI.c RaspiPreview.c dumpimg.c)
target_link_libraries(dumpimg /opt/vc/lib/libmmal_core.so /opt/vc/lib/libmmal_util.so /opt/vc/lib/libmmal_vc_client.so /opt/vc/lib/libvcos.so /opt/vc/lib/libbcm_host.so ${OpenCV_LIBS})
