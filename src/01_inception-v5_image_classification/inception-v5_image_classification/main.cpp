#include<opencv2/opencv.hpp>
#include<opencv2/dnn.hpp>
#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;
using namespace cv;
using namespace cv::dnn;

String label_file = "./../../../model_files/inception_v5/imagenet_comp_graph_label_strings.txt";
String tf_pbfile = "./../../../model_files/inception_v5/tensorflow_inception_graph.pb";
vector<String> read_class_names(String model_label_file);

//input size
const int w = 224;
const int h = 224;

int main(int argc, char**argv)
{
	Mat input_image = imread("zebra.jpg");
	if (input_image.empty())
	{
		cout << "read image failed!" << endl;
		return -1;
	}

	//show input image
	namedWindow("input_image", WINDOW_AUTOSIZE);
	imshow("input_image", input_image);
	//BGR-->RGB
	cvtColor(input_image, input_image, COLOR_BGR2RGB);

	//read labels
	vector<String> labels = read_class_names(label_file);

	//load cnn model
	Net cnn_net = readNetFromTensorflow(tf_pbfile);
	if (cnn_net.empty())
	{
		cout << "load net failed!" << endl;
		return -1;
	}
	//show layers names
	vector<String> layer_names = cnn_net.getLayerNames();
	for (int i = 0; i < layer_names.size(); i++)
	{
		int id = cnn_net.getLayerId(layer_names[i]);
		auto layer = cnn_net.getLayer(id);
		cout << "layerIndex:" << id << " " 
			<< "type:" << layer->type.c_str() << " "
			<< "name:" << layer->name.c_str() << endl;
	}

	//get input of the net
	Mat input_blob = blobFromImage(input_image, 1.0f, Size(h, w),
		Scalar(), true, false);
	input_blob -= 117.0;

	Mat prob;
	//set input
	cnn_net.setInput(input_blob, "input");
	//forward the net until "softmax2"
	prob = cnn_net.forward("softmax2");
	Mat probMat = prob.reshape(1, 1);
	Point classNumber;
	double classProb;
	minMaxLoc(probMat, NULL, &classProb, NULL, &classNumber);
	int classidx = classNumber.x;
	cout << "classification:" << labels.at(classidx).c_str() << endl
		<< "score:" << fixed << setprecision(2) << classProb;

	//show result
	cvtColor(input_image, input_image, COLOR_RGB2BGR);
	putText(input_image, "result:"+labels.at(classidx), 
		Point(20, 20), FONT_HERSHEY_COMPLEX, 1.0, 
		Scalar(0, 255, 0), 2, 8);
	putText(input_image, "score:"+to_string(classProb),
		Point(20, 50), FONT_HERSHEY_COMPLEX, 1.0, 
		Scalar(0, 255, 0), 2, 8);
	imshow("result", input_image);
	waitKey(0);
	return 0;
}

vector<String> read_class_names(String model_label_file)
{
	vector<String> class_names;
	ifstream fp(model_label_file);
	if (!fp.is_open())
	{
		cout << "open label file failed!" << endl;
		exit(-1);
	}
	string name;
	while (!fp.eof())
	{
		getline(fp, name);
		if (name.length())
			class_names.push_back(name);
	}
	fp.close();
	return class_names;
}