#include <utility>
#include <vector>
#include <iostream>
#include <zcm/zcm-cpp.hpp>
#include <set>
#include <iterator>
#include <opencv2/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2//highgui.hpp>  // Video write

#include "ZcmCameraBaslerJpegFrame.hpp"

class VideoParser {
    
private:
    cv::Mat img_;
    zcm::LogFile *zcm_log_;
    std::string output_filename_;
    
public:
    VideoParser(const std::string & input_filename, std::string  output_filename)
        : output_filename_{std::move(output_filename)}
    {
        zcm_log_ = new zcm::LogFile(input_filename, "r");
        if (!zcm_log_->good())
        {
            std::cout << "Bad zcm log: " << input_filename << std::endl;
            exit(0);
        }
    }

    void Run()
    {
        int codec = cv::VideoWriter::fourcc('X', '2', '6', '4');
        cv::VideoWriter writer;
        
        std::set < std::string > zcm_list;
        bool first_time = true;
        while (1)
        {
            const zcm::LogEvent* event = zcm_log_->readNextEvent();
            if (!event)
                break;
            if (event->channel == "FRZcmCameraBaslerJpegFrame") //FLZcmCameraBaslerJpegFrame	SLZcmCameraBaslerJpegFrame
            {
                ZcmCameraBaslerJpegFrame zcm_msg;
                zcm_msg.decode( event->data, 0, static_cast< unsigned >(event->datalen) );
                img_ = cv::imdecode(zcm_msg.jpeg, cv::IMREAD_COLOR);
                if (first_time)
                {
                    bool isColor = (img_.type() == CV_8UC3);
                    writer.open(output_filename_, codec, 8, img_.size(), isColor);
                    if (!writer.isOpened()) {
                        std::cout << "Could not open the output video file for write!" << std::endl;
                        exit(0);
                    }
                    first_time = false;
                }
                writer << img_;
            }
            zcm_list.insert( event->channel );
        }
        std::cout << "zcm_list: " << std::endl;
        for(auto i : zcm_list)
            std::cout << "\t" << i << std::endl;

        writer.release();
        std::cout << "Finished writing" << std::endl;
    }
};
