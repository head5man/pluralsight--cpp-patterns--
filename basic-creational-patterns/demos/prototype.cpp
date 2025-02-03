#include <iostream>
#include <vector>

// Abstract base class - This is our prototype which contains a "clone" method
class CoffeeMachine {
	public:
		virtual CoffeeMachine* clone() = 0;
		virtual void brew() = 0;
};

// Concrete implementations of the prototype - in practice, these would be "complex" objects that cost a lot to instantiate
class SimpleCoffeeMachine : public CoffeeMachine {
	public:
		CoffeeMachine*   clone() {
			return new SimpleCoffeeMachine;
		}

		void brew() {
			std::cout << "Brewing simple coffee!\n";
		}
};

class ComplexCoffeeMachine : public CoffeeMachine {
	public:
		CoffeeMachine*   clone() {
			return new ComplexCoffeeMachine; 
		}

		void brew() {
			std::cout << "Brewing complex coffee!\n";
		}
};

class EspressoMachine : public CoffeeMachine {
	public:
		CoffeeMachine*   clone() {
			return new EspressoMachine;
		}

		void brew() {
			std::cout << "Brewing espresso!\n";
		}
};

// Helper, management class which can abstract the creation of objects via their type.
class CoffeeMachineManager {
	public:
		static CoffeeMachine* createMachine( int machineType );
		~CoffeeMachineManager(){}

	private:
		static CoffeeMachine* machines[3];
};

// The management class contains already instantiated objects so that new objects requested are simply cloned!
CoffeeMachine* CoffeeMachineManager::machines[] =  {
	new SimpleCoffeeMachine, new ComplexCoffeeMachine, new EspressoMachine
};

// This helper method will ensure that new machines are not created from scratch but are simply cloned instead
CoffeeMachine* CoffeeMachineManager::createMachine( int machineType ) 
{
   return machines[machineType]->clone();
}

int main() {
	// Each call to the "createMachine" method clones the right CoffeeMachine object
	std::vector<CoffeeMachine*> myMachines(3);
	CoffeeMachine* simpleMachine = CoffeeMachineManager::createMachine(0);
	CoffeeMachine* complexMachine = CoffeeMachineManager::createMachine(1);
	CoffeeMachine* espressoMachine = CoffeeMachineManager::createMachine(2);

	myMachines[0] = simpleMachine;
	myMachines[1] = complexMachine;
	myMachines[2] = espressoMachine;

   for (int i = 0; i < myMachines.size(); i++) {
		myMachines[i]->brew();
   }

   // Easily create a copy! 
   CoffeeMachine* clonedMachine = simpleMachine->clone();
   clonedMachine->brew();

	// Clean up!
	for (int i = 0; i < myMachines.size(); i++) {
		delete myMachines[i];
	}

	delete clonedMachine;

   return 0;

}
