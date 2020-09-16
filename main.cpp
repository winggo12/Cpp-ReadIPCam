#include "opencv2/opencv.hpp"



//I/O
#include <iostream>
#include <vector>

//Time
#include <chrono>
#include <time.h>

//Thread
#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>

#define IPCAMFPS 16

std::vector<std::thread> th_list;
string rtsp_link1, rtsp_link2, rtsp_link3, rtsp_link4;

//cv::namedWindow("TEST", CV_WINDOW_AUTOSIZE);

cv::Mat frame1, frame2, frame3, frame4;

void camera_thread(string rtsp_link, cv::Mat* frame)
{	
	cv::VideoCapture capture(rtsp_link);
	while(capture.isOpened()) 
	{
		auto mainloop_start = std::chrono::high_resolution_clock::now();
		//capture >> frame;
		capture.grab();
		capture.retrieve(frame);

		if (frame.empty())
		{	
			std::cout << "frame is empty" << std::endl;
			break;
		}
		//string display_name = std::to_string();
		
		cv::imshow(rtsp_link, frame);

		double ipcam_fps = IPCAMFPS;
		double waittime = (double)1000/ipcam_fps;
		auto mainloop_end = std::chrono::high_resolution_clock::now();
		auto mainloop_duration = duration_cast<milliseconds>(mainloop_end - mainloop_start);

		std::cout << "mainloop_duration.count(): " << mainloop_duration.count() << std::endl;

		if(mainloop_duration.count() < waittime){
		waittime = (waittime - mainloop_duration.count());
		}
		
		cv::waitKey(waittime);
		std::cout << "waittime: " << waittime << std::endl;
		std::cout << "FPS: " << (double)1/((waittime+mainloop_duration.count())* pow(10.0, -3)) << endl;

	}


}

int main(){


	th_list.push_back(std::thread(camera_thread, rtsp_link1, &frame1));	
	th_list.push_back(std::thread(camera_thread, rtsp_link2, &frame2));
	th_list.push_back(std::thread(camera_thread, rtsp_link3, &frame3));
	th_list.push_back(std::thread(camera_thread, rtsp_link4, &frame4));

	for(std::thread& th : th_list)
	{
		// if(th.joinable())
		// 	th.join();
		if(th.joinable())
			th.detach();
	}

}


