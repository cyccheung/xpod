#include "Pod.h"
#include <cassert>
#include <iostream>

using namespace std;

void testCtor() {
    Pod pod("Aero");
    assert(pod.getName() == "Aero");
    vector<int> tempInventory;
    tempInventory.push_back(0);
    tempInventory.push_back(1); //1
    tempInventory.push_back(1);
    tempInventory.push_back(2);
    tempInventory.push_back(1);
    tempInventory.push_back(0); //5
    tempInventory.push_back(2);
    tempInventory.push_back(3);
    tempInventory.push_back(0);
    tempInventory.push_back(0);
    tempInventory.push_back(0); //10
    tempInventory.push_back(0);
    tempInventory.push_back(0);
    tempInventory.push_back(1);
    tempInventory.push_back(2);
    tempInventory.push_back(2); //15
    tempInventory.push_back(0);
    tempInventory.push_back(2);
    tempInventory.push_back(0);
    tempInventory.push_back(2);
    tempInventory.push_back(0); //20
    tempInventory.push_back(0);
    tempInventory.push_back(0);
    tempInventory.push_back(1);
    tempInventory.push_back(2);
    tempInventory.push_back(0); //25
    tempInventory.push_back(0);
    tempInventory.push_back(0);
    tempInventory.push_back(0);
    tempInventory.push_back(0);
    tempInventory.push_back(2); //30
    tempInventory.push_back(1);
    tempInventory.push_back(1);
    tempInventory.push_back(0);
    tempInventory.push_back(1);
    tempInventory.push_back(0); //35
    tempInventory.push_back(2);
    tempInventory.push_back(2);
    tempInventory.push_back(1);
    tempInventory.push_back(0);
    tempInventory.push_back(0); //40
    tempInventory.push_back(0);
    tempInventory.push_back(0);
    tempInventory.push_back(0); //43
    for(int i = 44; i < 77; ++i) {
        tempInventory.push_back(0);
    }
    assert(tempInventory == pod.getInventory());
    cout << "testCtor pass\n";
}

void testPlanSheet() {
    Pod pod("Aero");
    std::vector<Unit> testVec;
    testVec = pod.getPlanSheet();
    for(int i = 0; i < (int)testVec.size(); ++i) {
        testVec.at(i).printInfo();
    }
    cout << "testPlanSheet pass\n";
}

int main() {
    testCtor();
    //testPlanSheet();
    return 0;
}
