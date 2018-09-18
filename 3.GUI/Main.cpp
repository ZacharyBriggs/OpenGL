#include "GUIApplication.h"
class FileReader
{
public:
	std::string data;
	void ReadFromFile(const char* filename)
	{
		errno_t err;
		FILE *fp;
		err = fopen_s(&fp,filename, "r");
		char buf[500];
		
		while (std::fgets(buf, sizeof buf, fp))
		{
			data.append(buf);
		}
		err = fclose(fp);
	}
};
int main()
{
	Application* app = new GUIApplication();
	app->run("bob", 800, 600, false);
}