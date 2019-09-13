Qt Creator 4.10.0
Qt 5.13.1
GCC 5.3.1

Скопировать папки:
    camera_basler/
    service/
в папку zcm_types/ рядом с main.cpp
Собрать проект, на выходе исходник ./zcm2video

запустить исходник с параметром -h, там все расписанно
    ./zcm2video -h

для преобразования запустить следующее:
    ./zcm2video -i <путь к zcm логу> -o <путь к полученному файлу (результат работы)>

zcm log parameters:
    Lastochka:
        	FLLidarSickScanData
        	FRLidarSickScanData
        	LLZcmCameraBaslerJpegFrame
        	RailsSegmentation
        	RailsSegmentationLong
        	SLZcmCameraBaslerJpegFrame
        	SRZcmCameraBaslerJpegFrame
        	ZcmDisparityMap
        	human_mask
        	long_mono_obstacles
        	short_stereo_obstacles
    Loco:
        	BLidarLuxScanData
	        BRZcmCameraBaslerJpegFrame
	        BZcmFusionPredictedObstacle
	        BZcmLidarClustersList
	        BZcmLidarDataFusion
	        BZcmNeuralObstacles
	        FLRailDetection
	        FLZcmCameraBaslerJpegFrame
	        FLZcmTrackDetectTracksMask
	        FLidarScalaScanData
	        FRZcmCameraBaslerJpegFrame
	        FZcmFusionPredictedObstacle
	        FZcmLidarClustersList
	        FZcmLidarDataFusion
	        FZcmNeuralObstacles
	        ZcmAccFXOS8700
	        ZcmNavFilter
	        ZcmNavNV08CNavGw
	        ZcmSauglBrakeDiagnostics
	        ZcmSauglDiagnostics
	        ZcmSauglMssduInfo
	        ZcmSauglMssduInfoAck
	        ZcmSauglMssduTimestamp
	        ZcmSauglOduInfoAck
	        ZcmSauglState


