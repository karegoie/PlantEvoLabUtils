#include <stdio.h>
#include <io.h>
#include <windows.h>

int main()
{
	char strPath[] = {"C:\\Windows\System32\OpenSSH\ssh.exe"};
	
	int nResult = access(strPath, 0);
	
	if (nResult == 0)
	{
		printf("OpenSSH installed\n");
		Sleep(1000);
	}
	
	else if (nResult == -1)
	{
		printf("OpenSSH not installed\n");
		Sleep(1000);
		system("Add-WindowsCapability -Online -Name OpenSSH.Client~~~~0.0.1.0"); // OpenSSH install
		Sleep(1000);
	}
	system("Start-Service sshd");
	system("Start-Service -Name sshd -StartupType 'Automatic'");
	
	printf("Press F10 to sync Desktop to NAS\n");
	printf("It Syncs the directory where program exits\n\n")
	printf("Press ESC to quit\n");
	
	while(1)
	{
		if(GetKeyState(27)<0)
		{
			printf("Quit\n");
			Sleep(3000);
			return 0; // exit program
		}
		
		else if(GetKeyState(VK_F10)<0)
		{
			printf("Sync Start......\n");
			Sleep(1000);
			system("cd %~dp0");
			system("scp -r .\\ Hyunsu@147.47.212.48:/NAS/HyunsuLim") // Change it individually 
			Sleep(1000);
			
			printf("Sync finished\n");
			Sleep(3000);
			return 0;
		}
	}
	
	return 0;
}

