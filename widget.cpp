#include "widget.h"
#include "ui_widget.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QFileDialog>
#include <QString>
#include <iostream>
using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{


    cv::VideoCapture cap("C:\\redwalk.mp4");  // "input_video.mp4" 대신 사용할 입력 비디오 파일 경로를 지정하세요.

    // Check if the video file opened successfully
    if (!cap.isOpened()) {
        std::cerr << "Error: Could not open input video file." << std::endl;

    }

    double fps = cap.get(cv::CAP_PROP_FPS);  // Get the frames per second of the input video
    int frame_width = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_WIDTH));
    int frame_height = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_HEIGHT));

    // Define the codec and create VideoWriter object
    cv::VideoWriter videoWriter("output_video.mp4", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, cv::Size(frame_width, frame_height));
    if (!videoWriter.isOpened()) {
        std::cerr << "Error: Could not create output video file." << std::endl;

    }

    int frame_count = static_cast<int>(cap.get(cv::CAP_PROP_FRAME_COUNT));
    int frames_per_capture = static_cast<int>(fps) * 2;  // Capture 2 frames per second


    cv::Mat frame;


    for (int second = 0; second < frame_count * 2 / fps; ++second) {
        // Capture a frame at the current time
        cap.set(cv::CAP_PROP_POS_FRAMES, static_cast<double>(second) * fps / 2 );
        cap >> frame;

        if (!frame.empty()) {
            // Create a file name for the captured frame
            std::stringstream ss;
            ss << "camwalk_" << second << ".jpg";

            // Save the frame as an image file
            cv::imwrite(ss.str(), frame);
        }
    }

    // Release the video object
    cap.release();



}
void Widget::on_pushButton_2_clicked()
{
    cv::VideoCapture cap("C:\\video1.avi");

    // Check if the camera opened successfully
    if (!cap.isOpened())
    {
        std::cerr << "Error: Could not open camera." << std::endl;

    }

    int frameCount = 0;
    int frameRate = 2; // Capture 2 frames per second
    int delay = 1000 / frameRate; // Delay in milliseconds

    while (true)
    {
        cv::Mat frame;

        // Capture a frame from the camera
        cap >> frame;

        // Check if the frame was captured successfully
        if (frame.empty())
        {
            std::cerr << "Error: Could not read frame." << std::endl;
            break;
        }

        // Save the captured frame to a file
        std::string filename = "frame" + std::to_string(frameCount) + ".jpg";
        cv::imwrite(filename, frame);

        // Display the saved filename
        std::cout << "Saved: " << filename << std::endl;

        frameCount++;

        // Delay to achieve the desired frame rate
        cv::waitKey(delay);

        // Exit after capturing a certain number of frames
        if (frameCount >= 100) // Stop after 100 frames
            break;
    }

    // Release the camera
    cap.release();

}

