#include<iostream>
#include<opencv2/opencv.hpp>
#include <chrono>
#include <thread>

int main() {
	cv::VideoCapture cap(0);
	if (!cap.isOpened())
	{
		std::cerr << "erreur d'ouverture."<<std::endl;
		return -1;
	}

	cv::namedWindow("Grayframe", cv::WINDOW_AUTOSIZE);

	std::string Colorscale = "@%#*+=-:. ,;:!~^'\"`.";		
												//@%#*+=-:.
	int width = 120;								//@%#*+=-:. ,;:!~^'\"`.
	int height = 40;


	while (true) {
		cv::Mat frame;
		

		cap >> frame;
		if (frame.empty())

		{
			std::cerr << "erreur : frame capturée vide" << std::endl;
			break;
		}
		//cv::imshow("flux vidéo", frame);
		
		cv::Mat grayframe;
		cv::cvtColor(frame, grayframe, cv::COLOR_BGR2GRAY );
		cv::imshow("Grayframe", grayframe );

		cv::Mat resizedFrame;
		cv::resize(grayframe, resizedFrame, cv::Size(width, height));


		std::string asciiart = "";
		for (int i = 0; i < resizedFrame.rows; i++)
		{
			for (int j = 0; j < resizedFrame.cols; j++)
			{
				int pixel = (int)resizedFrame.at<uchar>(i, j);
				asciiart += Colorscale[pixel * Colorscale.length()/256 ] ;
				
			}
			//asciiart = '\n';
			cv::imshow("Grayframe", grayframe);
		
		}

		std::cout << "\033[H\033[J"; 
		std::cout << asciiart << std::flush;

		std::this_thread::sleep_for(std::chrono::milliseconds(30));
		
		if (cv::waitKey(1) >= 0)
		
		{
			break;
		}
		
	}
	std::cout << "\033[H\033[J"; // Efface l'écran avant de quitter
	cap.release();
	cv::destroyAllWindows();

	return 0;
}