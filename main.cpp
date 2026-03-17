#include <iostream>
#include <string>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
void nothing(int x, void* data) {}
void brightness(Mat img) {
  namedWindow("image");
  int slider = 100;
  createTrackbar("val","image",&slider,150,nothing);
  Mat hsv;
  while (true) {
    cvtColor(img, hsv, COLOR_BGR2HSV);
    float val = getTrackbarPos("val","image");
    val=val/100.0;
    Mat channels[3];
    split(hsv,channels);
    Mat H = channels[0];
    H.convertTo(H,CV_32F);
    Mat S = channels[1];
    S.convertTo(S,CV_32F);
    Mat V = channels[2];
    V.convertTo(V,CV_32F);
    for (int i=0; i < H.size().height; i++){
      for (int j=0; j < H.size().width; j++){
  // scale pixel values up or down for channel 1(Saturation)
        S.at<float>(i,j) *= val;
        if (S.at<float>(i,j) > 255)
          S.at<float>(i,j) = 255;
  // scale pixel values up or down for channel 2(Value)
        V.at<float>(i,j) *= val;
        if (V.at<float>(i,j) > 255)
          V.at<float>(i,j) = 255;
      }
    }
    H.convertTo(H,CV_8U);
    S.convertTo(S,CV_8U);
    V.convertTo(V,CV_8U);
    vector<Mat> hsvChannels{H,S,V};
    Mat hsvNew;
        merge(hsvChannels,hsvNew);
        Mat res;
        cvtColor(hsvNew,res,COLOR_HSV2BGR);
        imshow("original",img);
        imshow("image",res);
        if (waitKey(1) == 'q')
          break;
    }
  destroyAllWindows();
}

int main() {

    cv::Mat img = cv::imread("C:\\Users\\User\\Desktop\\photo_2026-03-15_17-51-05.jpg"); //загружаем изображение
    
    //если не загрузилось, создаем простое изображение
    if (img.empty()) {
        img = Mat(400, 600, CV_8UC3, Scalar(226, 100, 80));
        rectangle(img, Point(200, 150), Point(450, 250), Scalar(226, 92, 60), -1);
        putText(img, "good vibes", Point(250, 220), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 255, 255), 2);
    }
    
    if (img.cols > 800) {
        resize(img, img, cv::Size(800, 600));
    }
    
    cout << "Программа запущена. Нажмите 'q' для выхода" << std::endl;
    brightness(img);
    
    return 0;
}