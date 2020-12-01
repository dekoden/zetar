#ifndef __QuadrocopterBrain__Main__
#define __QuadrocopterBrain__Main__

struct Color32
{
	uchar r;
	uchar g;
	uchar b;
	uchar a;
};

extern "C"
{
	__declspec(dllexport) int getImages(Color32** raw, int width, int height, int numOfImg); // , bool isShow);
	__declspec(dllexport) void processImage(unsigned char* data, int width, int height);
}

#endif /* defined(__QuadrocopterBrain__Main__) */
