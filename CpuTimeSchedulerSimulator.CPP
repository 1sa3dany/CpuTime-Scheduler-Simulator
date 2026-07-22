#include <iostream>
using namespace std;
class MajorQueue{
    public:
        struct ProcessNode {
        ProcessNode *next;
        char pid;
        int arrivalTime;
        int burstTime;
        int remainingTime;
        int completionTime;
        int waitingTime;

    ProcessNode(){
         next = nullptr;
         pid =' ';
         arrivalTime = 0;
         burstTime = 0;
         remainingTime = burstTime;
        }
        
    };
    
    private:
        ProcessNode *front ;
        ProcessNode *rear;
        int processCounter = 0;

    public:
        MajorQueue(){
            front = nullptr;
            rear = nullptr;
        }
        ~MajorQueue(){
            ProcessNode* temp = front;
            while (temp != nullptr){
                ProcessNode* next = temp->next;
                delete temp;
                temp = next;
            }
        }
        
    void  enqueue (char name, int arrive , int burst,int remaining){
        ProcessNode* newProcess = new ProcessNode();
        newProcess->pid = name ;
        newProcess->arrivalTime = arrive ;
        newProcess->burstTime = burst;
        newProcess->remainingTime = remaining;
        if (front == nullptr){
            front = newProcess;
            rear = newProcess;
            processCounter++;
        } else {
            rear->next = newProcess;
            rear = newProcess;
            processCounter++;
        }
    }
    ProcessNode* getFront() 
    { 
        return front;
    }

    void insertByArrival (char name, int arrive , int burst,int remaining){
        ProcessNode* newProcess = new ProcessNode();
        newProcess->pid = name ;
        newProcess->arrivalTime = arrive ;
        newProcess->burstTime = burst;
        newProcess->remainingTime = remaining;
        //  if queue isempty == insert :-
        if (front == nullptr){
            front = newProcess;
            rear = newProcess;
            processCounter++;
        } 
        // if queue not empty and new process is first  == insert at first :-
        else if (front != nullptr && newProcess -> arrivalTime <= front -> arrivalTime ){
            newProcess -> next = front ;
            front = newProcess;
            processCounter++;
        }
        // if queue not empty and new process is not the first == find the right place then insetr :-
        else {
            ProcessNode* temp = front ;
            while (temp -> next != nullptr && temp -> next -> arrivalTime <= newProcess -> arrivalTime) {
                temp = temp -> next;
            }
            newProcess -> next = temp -> next;
            temp -> next = newProcess;
            if (rear == temp){
                rear = newProcess;
            }
            processCounter++;
        }
        
    } 
    
    ProcessNode* DequeueProcess (){
        if (front != nullptr){
            ProcessNode *temp = front;
            if (front == rear ){
                rear = nullptr;
            }
            front = front -> next;
            processCounter--;
            return temp;
        }
        else {
            return nullptr;
        }
    }
    
   bool isempty (){
    return (processCounter == 0);
   }
   int getProcessCounter(){
    return processCounter;
   }
    

};
class CpuScheduler{
    
    private:
    int currentTime;
    
    public:
    CpuScheduler(){
        currentTime = 0 ;
    }
    
    void checkArrivedprocess(MajorQueue *StaticQueue, MajorQueue *ReadyQueue){
        while(!StaticQueue -> isempty() &&  StaticQueue -> getFront() -> arrivalTime <= currentTime){
                    MajorQueue::ProcessNode* tempProcess = StaticQueue -> DequeueProcess();
                    ReadyQueue -> enqueue(tempProcess -> pid,tempProcess ->arrivalTime,tempProcess ->burstTime,tempProcess ->remainingTime);
                    delete tempProcess;

                }
    }
    void RoundRobin (MajorQueue * RR_StaticQueue, MajorQueue * RR_ReadyQueue,int quantum){
        currentTime = 0;
        if (RR_ReadyQueue -> isempty() && !RR_StaticQueue -> isempty()){
            for (int i = 0 ; i < RR_StaticQueue -> getFront() -> arrivalTime ; i++){
                currentTime++;
            }
        }
        checkArrivedprocess(RR_StaticQueue , RR_ReadyQueue);
        while (!RR_ReadyQueue -> isempty() || !RR_StaticQueue -> isempty()){   
            if (!RR_ReadyQueue -> isempty()){     
            MajorQueue::ProcessNode* currentProcess = RR_ReadyQueue ->DequeueProcess();
            if (currentProcess -> remainingTime <= quantum){
                int StartTime = currentTime;
                int  tempItreator = currentProcess -> remainingTime;
                for (int i = 0 ; i < tempItreator; i++){
                    currentProcess -> remainingTime--;
                    currentTime++ ;
                    // check if any process arrived during this process time 
                    checkArrivedprocess(RR_StaticQueue, RR_ReadyQueue);
            }
                currentProcess -> completionTime = currentTime;
                currentProcess -> waitingTime = currentProcess -> completionTime - currentProcess -> burstTime - currentProcess -> arrivalTime;   
                cout << "\n==================================================\n";
                cout << " [Round Robin] Process ( " << currentProcess->pid << " ) Completed!\n";
                cout << "==================================================\n";
                cout << "  Running Time    : " << StartTime << " -> " << currentTime << "\n";
                cout << "  Completion Time : " << currentProcess->completionTime << "\n";
                cout << "  Turnaround Time : " << currentProcess->completionTime - currentProcess->arrivalTime << "\n";
                cout << "  Waiting Time    : " << currentProcess->waitingTime << " Time Cycles\n";
                cout << "==================================================\n"; 
                // delete finished node  
                MajorQueue::ProcessNode* deletenode = currentProcess;
                delete deletenode;
        }
        else { 
            int StartTime = currentTime;
            for (int i = 0 ; i < quantum ; i++){
                currentProcess -> remainingTime--;
                currentTime++;
                // check if any process arrived during this process time 
                checkArrivedprocess(RR_StaticQueue,RR_ReadyQueue);
            }
            
            cout << " [Round Robin] Running Process ( " << currentProcess->pid << " ) from " << StartTime << " -> " << currentTime << endl;
            if (currentProcess -> remainingTime != 0){
                RR_ReadyQueue -> enqueue(currentProcess->pid, currentProcess->arrivalTime, currentProcess->burstTime,currentProcess->remainingTime);
                delete currentProcess; // delete the current process after enqueueing it
            }
        }
    }
    else {
        currentTime++;
        checkArrivedprocess(RR_StaticQueue,RR_ReadyQueue);
        }
      }
    }

    void fcfs (MajorQueue* FCFS_ReadyQueue , MajorQueue* FCFS_StaticQueue){
        currentTime = 0;
        if (FCFS_ReadyQueue -> isempty() && !FCFS_StaticQueue -> isempty()){
            for (int i = 0 ; i < FCFS_StaticQueue -> getFront() -> arrivalTime ; i++){
                currentTime++;
            }
        }
            while(!FCFS_StaticQueue->isempty() || !FCFS_ReadyQueue->isempty()){
                checkArrivedprocess(FCFS_StaticQueue,FCFS_ReadyQueue);
                if(!FCFS_ReadyQueue->isempty()){
                    MajorQueue::ProcessNode* currentProcess = FCFS_ReadyQueue ->DequeueProcess();
                    int StartTime = currentTime;
                    int tempItreator = currentProcess -> remainingTime;
                    for (int i = 0 ; i < tempItreator ; i++){
                        currentProcess -> remainingTime--;
                        currentTime++;
                        checkArrivedprocess(FCFS_StaticQueue,FCFS_ReadyQueue);
                    }
                    currentProcess -> completionTime = currentTime;
                    currentProcess -> waitingTime = currentProcess -> completionTime - currentProcess -> burstTime - currentProcess -> arrivalTime; 
                    cout << "\n==================================================\n";
                    cout << " [FCFS] Process ( " << currentProcess->pid << " ) Completed!\n";
                    cout << "==================================================\n";
                    cout << "  Running Time    : " << StartTime << " -> " << currentTime << "\n";
                    cout << "  Completion Time : " << currentProcess->completionTime << "\n";
                    cout << "  Turnaround Time : " << currentProcess->completionTime - currentProcess->arrivalTime << "\n";
                    cout << "  Waiting Time    : " << currentProcess->waitingTime << " Time Cycles\n";
                    cout << "==================================================\n"; 
                    // delete finished node  
                    MajorQueue::ProcessNode* deletenode = currentProcess;
                    delete deletenode;
                }
                else {
                    currentTime++;
                    checkArrivedprocess(FCFS_StaticQueue,FCFS_ReadyQueue);
                }
            }
            

    }

        
    
};

 class inputHandler {
    public:
    void InputMethod (MajorQueue* MainQueue1 , MajorQueue* MainQueue2 ){
        char catchPid;
        int catchBurst;
        int catchArrival;
        cout << "\n=== CPU Scheduler Simulator ===\n";
        cout << "Type The Number Of Processes : ";
        int numberOfProcesses;
        cin >> numberOfProcesses;
        
        for (int i = 0 ; i < numberOfProcesses ; i++){
        cout << "\n--- Process " << i + 1 << " ---\n";
        cout << "Enter The Name Of Process (Char) : ";
        cin >> catchPid;
        cout << "Type Burst Time : ";
        cin >> catchBurst;
        cout << "Type Arrival Time : "; 
        cin >> catchArrival;
        MainQueue1 -> insertByArrival(catchPid,catchArrival,catchBurst,catchBurst);
        MainQueue2 -> insertByArrival(catchPid,catchArrival,catchBurst,catchBurst);
        }
    }
 };
    int main (){
    
    MajorQueue RR_StaticQueue;
    MajorQueue FCFS_StaticQueue;
    MajorQueue RR_ReadyQueue;
    MajorQueue FCFS_ReadyQueue;
    inputHandler Inputt;
    Inputt.InputMethod(&RR_StaticQueue,&FCFS_StaticQueue);


        CpuScheduler Cpu;
        Cpu.RoundRobin(&RR_StaticQueue,&RR_ReadyQueue,2);
        Cpu.fcfs(&FCFS_ReadyQueue,&FCFS_StaticQueue);
    return 0;
    }
    
