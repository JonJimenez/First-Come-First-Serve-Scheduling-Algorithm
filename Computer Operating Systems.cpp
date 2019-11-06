#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
vector <vector<int>> process{{ 5, 27, 3, 31, 5, 43, 4, 18, 6, 22, 4, 26, 3, 24, 4 },
							{ 4, 48, 5, 44, 7, 42, 12, 37, 9, 76, 4, 41, 9, 31, 7, 43, 8 },
							{ 8, 33, 12, 41, 18, 65, 14, 21, 4, 61, 15, 18, 14, 26, 5, 31, 6 },
							{ 3, 35, 4, 41, 5, 45, 3, 51, 4, 61, 5, 54, 6, 82, 5, 77, 3 },
							{ 16, 24, 17, 21, 5, 36, 16, 26, 7, 31, 13, 28, 11, 21, 6, 13, 3, 11, 4 },
							{ 11, 22, 4, 8, 5, 10, 6, 12, 7, 14, 9, 18, 12, 24, 15, 30, 8 },
							{ 14, 46, 17, 41, 11, 42, 15, 21, 4, 32, 7, 19, 16, 33, 10 },
							{ 4, 14, 5, 33, 6, 51, 14, 73, 16, 87, 6 } };
int totalTime=-1, currentProcess, cpuUtili = 0,q=0;
int p[8][3] = { { 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 },{ 0,0,0 } };
int main() {
	vector<int> readyList;//holds which process is next by row of vector
	//inititate values
	for (int j = 0; j < process.size(); j++) {
		readyList.push_back(j);
	}
	currentProcess = readyList.front();//Sets the CurrentProcess
	readyList.erase(readyList.begin());//Erases the Copy in the first Element
	while (!process[0].empty()|| !process[1].empty()|| !process[2].empty() || !process[3].empty() || !process[4].empty() || !process[5].empty() || !process[6].empty() || !process[7].empty()) {//Continues until all Processes are empty
		for (int i = 0; i < process.size(); i++) {//cant do .size()>0 since it checks if the I/O burst and if its only 1 CPU burst left it will casue error
			for (int j = 0; j < readyList.size();j++) {
				if (i == readyList[j]) {
					p[i][0]++;//Keeps track of Wait Time
				}
			}
				if (process[i].size() > 2) {//checks to see if CPU burst is done and that its not decrementing the CPU burst
					if (process[i].front() == 0) {//I/O Burst
						process[i][1]--;
					}
				}
				//If CPU and IO burst finished
				if (process[i].size() > 1) {//2 or More CPU bursts left
					if (process[i].front() == 0 && process[i][1] == 0) {//if CPU and I/O are 0				
						process[i].erase(process[i].begin());//erase CPU
						process[i].erase(process[i].begin());//erase I/O
						readyList.push_back(i);//Queues up next process
					}
				}
				if (process[i].size() == 1 && process[i].front() == 0) {//Erases Last CPU
					p[i][1] = totalTime + 1;
					process[i].erase(process[i].begin());//erase I/O
				}
		}
		if (!process[currentProcess].empty()) {//checks if there are still a CPU burst 
			if (process[currentProcess].front() > 0) {//checks if process still is going through CPU Burst
				process[currentProcess][0]--;//decrements the CPU process from the process vector
				cpuUtili++;
				if (q < process.size()&&currentProcess==q) {//Response TIme
					p[q][2] = totalTime+1;
					q++;
				}
			}
			if (process[currentProcess].front() == 0 && readyList.size()>0) {//if ready list has 1 or more queued
				cout << "Time:" << totalTime + 1<< "\nCurrent Process is completed: Process " << currentProcess + 1;
				currentProcess = readyList.front();//Sets Current Process
				readyList.erase(readyList.begin());//erase first element		
				cout << "\nProcess switched to: Process" << currentProcess + 1 << endl;
				for (int p = 0; p < process.size(); p++) {
					if (process[p].size()>1&&process[p].front()==0) {
						cout << "Process" << p + 1 << " I/O Burst:" << process[p][1] << endl;
					}
				
				}
			}			
		}
		else if (process[currentProcess].empty()&&!readyList.empty()) {//Cathes last bit of CPU bursts to put in Current Process
			currentProcess = readyList.front();	
			readyList.erase(readyList.begin());
		}
		totalTime++;
	}//Calculations and Final OutPut values
	float CPUave = (float)cpuUtili / (float)totalTime;
	float AveWait=0, Ttr=0, Tr=0;
	CPUave = CPUave * 100;
	for (int i = 0; i < process.size(); i++) {
		cout << "P" << i + 1 << " Wait Time:" << p[i][0] << endl;
		cout <<"P"<<i+1<<" Turn around Time:" <<p[i][1] << endl;	
		cout << "P" << i + 1 << "Response Time:" << p[i][2] << endl;
		AveWait += p[i][0];
		Ttr += p[i][1];
		Tr += p[i][2];
	}
	AveWait = AveWait / (float)process.size();
	Ttr = Ttr / (float)process.size();
	Tr = Tr / (float)process.size();
	cout << setprecision(4) <<"CPU Utilization: " <<CPUave << "%" << endl;
	cout << setprecision(5) <<"Average Wait Time:"<< AveWait <<endl;
	cout << setprecision(5) <<"Average Turn Around Time: " <<Ttr << endl;
	cout << setprecision(4) <<"Average Response Time: " <<Tr << endl;
	return 0;
}
