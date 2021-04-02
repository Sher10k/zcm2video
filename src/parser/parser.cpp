//=======================================================================================

// STD
#include <utility>
#include <vector>
#include <iostream>
#include <set>
#include <iterator>
#include <opencv2/core.hpp>        // Basic OpenCV structures (cv::Mat)
#include <opencv2/highgui.hpp>    // Video write

// ZCM
#include "ZcmCameraBatch.hpp"
#include "ZcmCameraFrame.hpp"
#include "ZcmCameraMsg.hpp"
#include <zcm/zcm-cpp.hpp>

//=======================================================================================

class VideoParser 
{
    
private:
    std::vector< cv::Mat > imgs_;
    std::vector< std::string > names_file_;
    zcm::LogFile *zcm_log_;
    std::string output_filename_ {""};
    std::string param_ {""};
    int id_ {-1};
    double fps_ {5}; 
    bool list_ {false};
    size_t batch_size {1};
    
    void get_names( const ZcmCameraBatch& msg_ )
    {
        for ( size_t i = 0, j = 0; i < batch_size; i++, j++ )
        {
            if (id_ != -1) j = id_;
            
            names_file_[i] = output_filename_
                    + "_p"+ std::to_string(msg_.camera_batch[j].id_scop.id_pillar)
                    + "_c"+ std::to_string(msg_.camera_batch[j].id_scop.id_camera)
                    + "_t"+ std::to_string(msg_.camera_batch[j].id_scop.type)
                    + ".avi";
            
            if (id_ != -1) return;
        }
    }
    
    void decode_frame( const ZcmCameraBatch& msg_ )
    {
        for ( size_t i = 0, j = 0; i < batch_size; i++, j++ )
        {
            if (id_ != -1) j = id_;
            
            if ( msg_.camera_batch[j].frame.format == "JPEG" )
                imgs_[i] = cv::imdecode( msg_.camera_batch[j].frame.data, cv::IMREAD_COLOR );
            else
            {
                imgs_[i] = cv::Mat( msg_.camera_batch[j].frame.height,
                                    msg_.camera_batch[j].frame.width,
                                    CV_8UC3 );
                std::memcpy( imgs_[i].data, msg_.camera_batch[j].frame.data.data(), 
                             size_t(msg_.camera_batch[j].frame.data_size) * sizeof(u_int8_t) );
            }
            
            if (id_ != -1) return;
        }
    }
    
public:
    VideoParser( const std::string & input_filename, 
                 std::string  output_filename, 
                 std::string  param,
                 int id_camera,
                 double fps,
                 bool list )
        : output_filename_{ std::move(output_filename) }
        , param_{ std::move(param) }
        , id_{ std::move(id_camera) }
        , fps_{ std::move(fps) }
        , list_{ std::move(list) }
    {
        zcm_log_ = new zcm::LogFile(input_filename, "r");
        if ( !zcm_log_->good() )
        {
            std::cout << "Bad zcm log: " << input_filename << std::endl;
            exit(0);
        }
        
        if (id_ != -1) id_--;
    }
    
    void Run()
    {
        int codec = cv::VideoWriter::fourcc('X', '2', '6', '4');
        std::vector< cv::VideoWriter > writers;
        
        std::set < std::string > zcm_list;
        bool first_time = true;
        while (1)
        {
            const zcm::LogEvent* event = zcm_log_->readNextEvent();
            if (!event)
                break;
            if ( (event->channel == param_) && ( !list_ ) )
            {
                ZcmCameraBatch zcm_msg;
                zcm_msg.decode( event->data, 0, static_cast< unsigned >(event->datalen) );
                
                if ( first_time )
                {
                    if (id_ == -1) batch_size = zcm_msg.msg_size;
                    else batch_size = 1;
                    writers.resize( batch_size );
                    imgs_.resize( batch_size );
                    names_file_.resize( batch_size );
                    
                    decode_frame( zcm_msg );
                    get_names( zcm_msg );
                    
                    // --- Open video writer for each output files
                    for ( size_t i = 0; i < batch_size; i++ )
                    {
                        bool isColor = ( imgs_[i].type() == CV_8UC3 );
                        writers[i].open( names_file_[i], codec, fps_, imgs_[i].size(), isColor );
                        if (!writers[i].isOpened()) 
                        {
                            std::cout << "Could not open the output video file for write!" << std::endl;
                            exit(0);
                        }
                        else 
                            std::cout << "Writer opened for file: \t" << names_file_[i] << "\n";
                    }
                    first_time = false;
                }
                
                decode_frame( zcm_msg );
                
                // --- Push frame in video writer
                for ( size_t i = 0; i < batch_size; i++ )
                    writers[i] << imgs_[i];
            }
            zcm_list.insert( event->channel );
        }
        std::cout << "zcm_list: " << std::endl;
        for(auto i : zcm_list)
            std::cout << "\t" << i << std::endl;

        for ( auto& writer : writers )
            writer.release();
        
        if ( !list_ ) std::cout << "Finished writing" << std::endl;
    }
};

//=======================================================================================
