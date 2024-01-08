#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;


class Player {
protected:
	string playerName;
	string classType = "None";
	int xpValue;
	int level;
	int health;
	int attDam = 0;

public:
	Player(string PlayerName) {
		playerName = PlayerName;
		level = 1;
	}

	void getcharInfo() {
		cout << "Name: " << playerName << endl;
		cout << "Level: " << level << endl;
		cout << "Health: " << health << endl;
		cout << "Attack Damage: " << attDam << endl;
		cout << endl;

	}
	virtual void Attack() = 0;

	string getName() {
		return playerName;
	}
	int getAttackDam() {
		return attDam;
	}
	int getHealth() {
		return health;
	}
};
class MeleePlayer : public Player {
public:
	MeleePlayer(string PlayerName):Player(PlayerName) {
		playerName = PlayerName;
		health = 200;
		attDam = 20;
		level = 1;
	}

	void Attack() {
		string leeOptions[3] = { "swings sword twice, ", "stabs sword in an upward motion, ", "deflects incoming attacks, " };
		srand(time(0));
		int r = rand() % 3;
		cout << playerName << " " << leeOptions[r] << "deals " << attDam << " damage." << endl << endl;
		
	}
	

};
class MagePlayer : public Player {
public:
	MagePlayer(string PlayerName):Player(PlayerName) {
		playerName = PlayerName;
		health = 100;
		attDam = 12;
		level = 1;
	}

	void Attack() {
		string mageOptions[3] = { "slams staff on floor creates fire bolt, ", "throws poisonous potions, ", "reverses monster atatck, " };
		srand(time(0));
		int r = rand() % 3;
		cout << playerName << " " << mageOptions[r] << "deals " << attDam << " damage." << endl << endl;
	}

	
}; 
class HunterPlayer : public Player {
public:
	HunterPlayer(string PlayerName):Player(PlayerName) {
		playerName = PlayerName;
		health = 85;
		attDam = 25;
		level = 1;
	}

	void Attack() {
		string hunterOptions[3] = { "shoots volley of arrows, ", "charges arrow, ", "dodges and shoot poison dart, " };
		srand(time(0));
		int r = rand() % 3;
		cout << playerName << " " << hunterOptions[r] << "deals " << attDam << " damage." << endl << endl;
	}
};

class Enemy {

protected:
	int health;
	int attDam;
	int level = 9999;
	string eName;
public:
	Enemy(bool fight) {
		eName = "ENEMY";
		health = 99999;
		attDam = 99999;
	}
	void getenemyInfo() {
		cout << "Name: " << eName << endl;
		cout << "Level: " << level << endl;
		cout << "Health: " << health << endl;
		cout << "Attack Damage: " << attDam << endl;
		cout << endl;
	}
	virtual void eAttack() = 0;

	string geteName() {
		return eName;
	}
	int geteAttackDam() {
		return attDam;
	}
	int geteHealth() {
		return health;
	}

};
class Ninja : public Enemy {

public:
	Ninja(bool fight):Enemy(fight) {
		cout << "A ninja has appeared. What will you choose to do? " << endl;
		eName = "Ninja James";
		level = 1;
		health = 90;
		attDam = 10;
	}
	void eAttack() {
		string ninjaOptions[3] = { "throws shuriken, ", "slashes sword, ", "dashes through you, " };
		srand(time(0));
		int r = rand() % 3;
		cout << eName << " " << ninjaOptions[r] << "deals " << attDam << " damage." << endl << endl;
	}
};
class Zombie : public Enemy {

public:
	Zombie(bool fight) :Enemy(fight) {
		cout << "A Zombie has appeared. What will you choose to do? " << endl;
		eName = "Zombie Bob";
		level = 1;
		health = 100;
		attDam = 15;
	}
	void eAttack() {
		string zombieOptions[3] = { "scratches, ", "spits, ", "lunges, " };
		srand(time(0));
		int r = rand() % 3;
		cout << eName << " " << zombieOptions[r] << "deals " << attDam << " damage." << endl << endl;
	}

};

void ClassSelect();
bool fight = true;

void Combat(Player &p1, Enemy &e1, string classType, string pName, int pHealth = 999, int eHealth = 999) {
	if (pHealth == 999) {
		pHealth = p1.getHealth();
	}
	if (eHealth == 999) {
		eHealth = e1.geteHealth();
	}

	
	int npHealth = 1;
	int neHealth = 1;
	int eDam = e1.geteAttackDam();
	int pDam = p1.getAttackDam();
	while (fight == true) {
		string decision;
		cout << "\n\n1.Fight \n2.Dodge" << endl;
		cin >> decision;
		cout << endl;
		int n = 2;

		if (decision == "1") {
			//Player attacks 
			e1.eAttack();
			npHealth = pHealth - eDam;
			cout << p1.getName() << " has " << npHealth << " left." << endl << endl;
			p1.Attack();
			neHealth = eHealth - pDam;
			cout << e1.geteName() << " has " << neHealth << " left." << endl << endl;
			pHealth = npHealth;
			eHealth = neHealth;
		}
		else if (decision == "2") {

			e1.eAttack();
			cout << p1.getName() << " dodges the attack. Health remains the same." << endl;
		}
		else {
			cout << "Enter a valid number. ";
		}

		if (npHealth <= 0) {
			cout << "Player died. Game Over" << endl;
			fight = false;
			break;
		}
		else if (neHealth <= 0) {
			cout << "Monster defeated!!!!!\n\n";
			string enemyOptions[2] = { "ninja", "zombie" };
			srand(time(0));
			int r = rand() % 2;
			if (r == 0) {
				Ninja e2(fight);
				e1 = e2;
				e1.getenemyInfo();
				Combat(p1, e1, classType, pName, npHealth, 999);
			}
			else {
				Zombie e2(fight);
				e1 = e2;
				e1.getenemyInfo();
				Combat(p1, e1, classType, pName, npHealth, 999);
			}
		}
	}

}
void ClassSelect() {
	
	string classType;
	string pName;
	cout << "Choose your class : ";
	cin >> classType;
	cout << endl;
	cout << "Player Name: ";
	cin >> pName;
	cout << endl;
	transform(classType.begin(), classType.end(), classType.begin(), ::tolower);
	
	if (classType == "melee") {

		MeleePlayer p1(pName);
		p1.getcharInfo();

		bool fight = true;
		string enemyOptions[2] = { "ninja", "zombie" };
		srand(time(0));
		int r = rand() % 2;
		if (r == 0) {
			Ninja e1(fight);
			e1.getenemyInfo();
			Combat(p1,e1, classType, pName);
		}
		else {
			Zombie e1(fight);
			e1.getenemyInfo();
			Combat(p1, e1, classType, pName);
		}
		

	}
	else if (classType == "mage") {
		
		MagePlayer p1(pName);
		p1.getcharInfo();

		bool fight = true;
		string enemyOptions[2] = { "ninja", "zombie" };
		srand(time(0));
		int r = rand() % 2;
		if (r == 0) {
			Ninja e1(fight);
			e1.getenemyInfo();
			Combat(p1, e1, classType, pName);
		}
		else {
			Zombie e1(fight);
			e1.getenemyInfo();
			Combat(p1, e1, classType, pName);
		}
		
	}
	else if (classType == "hunter") {
		
		HunterPlayer p1(pName);
		p1.getcharInfo();

		bool fight = true;
		string enemyOptions[2] = { "ninja", "zombie" };
		srand(time(0));
		int r = rand() % 2;
		if (r == 0) {
			Ninja e1(fight);
			e1.getenemyInfo();
			Combat(p1, e1, classType, pName);
		}
		else {
			Zombie e1(fight);
			e1.getenemyInfo();
			Combat(p1, e1, classType, pName);
		}
		

	}else{
		cout << "Choose valid class." << endl;
		
		ClassSelect();
	}

}




int main()
{//Game
	while (true) {

		cout << "Welcome to TexFighter 1.0 " << endl <<
			"\nIn this game you will have a choice between three class types: Mage, Melee, Hunter. The\n"
			"the point of this text based game is to fight monsters and gain xp,each moster killed\n"
			"will randomly provide the playter with 10 to 15 xp.\n\n"
			"Players will have the option to Attack or Dodge \n\nAttacking will deal damage based on the selected class and dodging will allow the player to negate all damage." << endl;


		cout << "---------------------------------------------------------------------------------------------" << endl;
		
		ClassSelect();

		

		break;
	}
	
	
		
	
	system("pause>0");
}


/*
	int npHealth;
	int neHealth;
	int pHealth;
	int eHealth;
	int eDam;
	int pDam
	bool fight = true;
	if (test == true) {
	npHealth;
	neHealth;
	pHealth = p1.getHealth();
	eHealth = e1.geteHealth();
	eDam = e1.geteAttackDam();
	pDam = p1.getAttackDam();
	}
	*/