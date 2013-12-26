#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int main(int argc, const char** argv)
{
	int mode = 0;

	if (argc < 2)
	{
		cout << "Usage: ./hexvew [filename] [hex|dec]" << endl;
		return 1;
	}

	if (argc == 3)
	{
		if (string(argv[2]) == "dec")
		{
			mode = 1;
		}
	}

	const int BUF_SIZE = 8192;
	unsigned char input_buffer[BUF_SIZE];

	int input_file = open(argv[1], O_RDONLY);

	while(1)
	{
		int bytesRead = read(input_file, input_buffer, BUF_SIZE);
		if (bytesRead == 0)
		{
			// done with file.
			break;
		}

		if (mode == 0)
		{
			for(int i = 0;i < bytesRead;++i)
			{
				cout << setw(4) << hex 
				     << static_cast<unsigned int>(input_buffer[i]); 

				if ((i % 16) == 15)
				{
					cout << "  (" << dec << i << ")" <<  endl;
				}
			}
		}

		else
		{
			for(int i = 0;i < bytesRead;++i)
			{
				cout << setw(8) << static_cast<unsigned int>(input_buffer[i]); 

				if ((i % 8) == 7)
				{
					cout << endl;
				}
			}
		}
	}

	cout << endl;
	close(input_file);
	return 0;
}
