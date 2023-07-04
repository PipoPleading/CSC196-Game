#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include <iostream>
//#include <chrono>
// "#" is preprocessor directive
using namespace std;


int main() 
{
	kiko::g_memoryTracker.DisplayInfo();
	int* p = new int; //overload
	kiko::g_memoryTracker.DisplayInfo();
	delete p;
	kiko::g_memoryTracker.DisplayInfo();

	kiko::Time timer;
	for (int i = 0; i < 1000000; i++) {}
	cout << timer.GetElapsedMilliseconds() << endl;

	//auto i = true;
	//auto start = chrono::high_resolution_clock::now();
	//for (int i = 0; i < 1000000; i++) {}
	//auto end = std::chrono::high_resolution_clock::now();

	//cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << endl;



	//cout << kiko::getFilePath() << endl;
	//kiko::setFilePath("Assets"); //not case sensitive "../"
	//cout << kiko::getFilePath() << endl;
	//size_t size = 0;
	//kiko::getFileSize("game.txt", size);
	//cout << "Size: " << size << endl;

	//std::string s;
	//kiko::readFile("game.txt", s);
	//cout << s << endl;


	//kiko::seed_random((unsigned int)time(nullptr));
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << kiko::random(10, 20) << endl;
	//}
}
