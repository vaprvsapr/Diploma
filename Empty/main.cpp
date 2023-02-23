#include <iostream>
#include <sstream>
#include <filesystem>

using namespace std;

int main()
{
	string dir_path = "C:/Users/Mi/Pictures/Gimp";
	filesystem::path gimp(dir_path);

	cout << gimp << endl;

	for (auto iter : filesystem::directory_iterator{ gimp })
	{
		cout << iter.path() << endl;

	}
}
	