#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define MAX_QUEUE_LENGTH 100
#define NUM_DOCTORS 5


typedef struct {
    int id;
    int urgency; 
    int serviceTime;
} Patient;


typedef struct {
    int id;
    int isAvailable;
} Server;


int availableServers = NUM_DOCTORS;
Patient *patientQueue[MAX_QUEUE_LENGTH];
int queueLength = 0;
Server doctors[NUM_DOCTORS];


Patient* generatePatientData(int id) {
    Patient *newPatient = (Patient*)malloc(sizeof(Patient));
    newPatient->id = id;
    newPatient->urgency = rand() % 4; 
    newPatient->serviceTime = rand() % 10 + 1; 
    return newPatient;
}


void handlePatientArrival(Patient *newPatient) {
    if (queueLength < MAX_QUEUE_LENGTH) {
        
        int i;
        for (i = queueLength - 1; (i >= 0 && patientQueue[i]->urgency > newPatient->urgency); i--) {
            patientQueue[i + 1] = patientQueue[i];
        }
        patientQueue[i + 1] = newPatient;
        queueLength++;
        printf("Patient %d added to the queue with urgency %d\n", newPatient->id, newPatient->urgency);
    } else {
        printf("Queue is full. Patient %d redirected to another hospital.\n", newPatient->id);
    }
}


void processPatients() {
    for (int i = 0; i < availableServers && queueLength > 0; i++) {
        if (doctors[i].isAvailable) {
            
            Patient *nextPatient = patientQueue[0];
            printf("Doctor %d serving patient %d with urgency %d\n", doctors[i].id, nextPatient->id, nextPatient->urgency);
            
            
            for (int j = 0; j < queueLength - 1; j++) {
                patientQueue[j] = patientQueue[j + 1];
            }
            queueLength--;
            
            
            doctors[i].isAvailable = 0;
            sleep(nextPatient->serviceTime);
            doctors[i].isAvailable = 1;
            printf("Doctor %d finished with patient %d\n", doctors[i].id, nextPatient->id);
            
            free(nextPatient); 
        }
    }
}


void simulatePatientArrivals(int simulationTime) {
    srand(time(0));
    for (int t = 0; t < simulationTime; t++) {
        if (rand() % 100 < 30) { 
            Patient *newPatient = generatePatientData(t);
            handlePatientArrival(newPatient);
        }
        processPatients();
    }
}


void HybridRobustStochasticScheduler() {
    
    printf("Hybrid scheduler active...\n");
    for (int i = 0; i < availableServers; i++) {
        doctors[i].isAvailable = 1; 
    }
}


void mainSimulation(int simulationTime) {
    while (simulationTime > 0) {
        simulatePatientArrivals(simulationTime);
        HybridRobustStochasticScheduler();
        simulationTime--;
    }
}

int main() {
    
    for (int i = 0; i < NUM_DOCTORS; i++) {
        doctors[i].id = i + 1;
        doctors[i].isAvailable = 1; 
    }

    
    int maxQueueLength = MAX_QUEUE_LENGTH;
    
    
    int simulationTime = 20; 
    mainSimulation(simulationTime);

    return 0;
}
 