// Submitted by: Annshine Wu, Justin Lee
// It uses a recursive backtracking function to schedule all patients to a doctor.
// Then, modifies the schedule to display the schedule (which doctors look at which patients)

#include "DoctorsWithoutOrders.h"
#include "map.h"
#include "set.h"
#include <climits>
#include <iostream>
using namespace std;

/* * * * Doctors Without Orders * * * */

bool availableDoctor(Vector<Doctor> &, Vector<Patient> &, Map<string, Set<string>>&, int, int);

/**
 * Given a list of doctors and a list of patients, determines whether all the patients can
 * be seen. If so, this function fills in the schedule outparameter with a map from doctors
 * to the set of patients that doctor would see.
 *
 * @param doctors  The list of the doctors available to work.
 * @param patients The list of the patients that need to be seen.
 * @param schedule An outparameter that will be filled in with the schedule, should one exist.
 * @return Whether or not a schedule was found.
 */

// It calls the helper recursive function and returns the returned value from the helper fucntion
bool canAllPatientsBeSeen(Vector<Doctor> &doctors, Vector<Patient> &patients, Map<string, Set<string>>& schedule) {
    (void)(doctors, patients, schedule);
    Vector<Doctor> doctorsCopy = doctors;
    Vector<Patient> patientsCopy = patients;
    return availableDoctor(doctorsCopy, patientsCopy, schedule, 0, 0);
}

// availableDoctor returns true if it is possible to scheule all the patients in, false otherwise.
// if the patientIndex >= patients.size(), it returns true to signify that all patients have been scheduled
// if the doctorIndex <= doctors.size(), it means there are not enough doctors. Thus, not all patients have been scheduled
// it goes through option one in which:
//      1. it deducts the patient's needed hours from a doctor's free hours. then it sets the patient's needed hours to 0
//      3. adds the appointment in the schedule
//      2. calls the helper function with the next patient "in line" to be schedules
// it goes through option two if option one fails:
//      1. adds back the original doctor's used hours
//      2. uses the next doctor in line to look at the patient by calling the recursive helper function again
// returns true if either attempt works (false otherwise)
bool availableDoctor(Vector<Doctor> &doctors, Vector<Patient> &patients, Map<string, Set<string>>& schedule, int doctorIndex, int patientIndex){
    if(patientIndex >= patients.size()){
        return true;
    }
    if(doctorIndex >= doctors.size()){
        return false;
    }
    doctors[doctorIndex].hoursFree -= patients[patientIndex].hoursNeeded;
    int hoursNeeded = patients[patientIndex].hoursNeeded;
    patients[patientIndex].hoursNeeded = 0;
    string doctorName = doctors[doctorIndex].name;
    string patientName = patients[patientIndex].name;
    Set<string> currentDoctor = schedule.get(doctorName);
    bool optionOne = false;
    if(doctors[doctorIndex].hoursFree >= 0){
        currentDoctor.add(patientName);
        schedule[doctorName] = currentDoctor;
        optionOne = availableDoctor(doctors, patients, schedule, 0, patientIndex+1);
    }
    bool optionTwo = false;
    if(!optionOne){
        doctors[doctorIndex].hoursFree += hoursNeeded;
        patients[patientIndex].hoursNeeded = hoursNeeded;
        currentDoctor.remove(patientName);
        schedule[doctorName] = currentDoctor;
        optionTwo = availableDoctor(doctors, patients, schedule, doctorIndex+1, patientIndex);
    }
    return optionOne || optionTwo;
}
