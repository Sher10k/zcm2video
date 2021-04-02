#========================================================================================

set( ZCM_TYPES_DIR ${CMAKE_CURRENT_LIST_DIR}/zcm_types )

#========================================================================================

include_directories( ${ZCM_TYPES_DIR}
    ${ZCM_TYPES_DIR}/service
    ${ZCM_TYPES_DIR}/service/cpp_types
    ${ZCM_TYPES_DIR}/scop_camera_msg
    ${ZCM_TYPES_DIR}/scop_camera_msg/cpp_types
    )

#========================================================================================

set( ZCM_TYPES
    ${ZCM_TYPES_DIR}/service/cpp_types/ZcmService.hpp
    ${ZCM_TYPES_DIR}/scop_camera_msg/cpp_types/ZcmCameraBatch.hpp
    ${ZCM_TYPES_DIR}/scop_camera_msg/cpp_types/ZcmCameraFrame.hpp
    ${ZCM_TYPES_DIR}/scop_camera_msg/cpp_types/ZcmCameraMsg.hpp
    ${ZCM_TYPES_DIR}/scop_camera_msg/cpp_types/ZcmScopID.hpp
    )

#========================================================================================
