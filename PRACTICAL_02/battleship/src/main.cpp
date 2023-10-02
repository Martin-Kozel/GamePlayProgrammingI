#include <iostream>

using namespace std;

typedef struct Position
{
	int x;
	int y;
	void
	print()
	{
		cout << "[ x: " << x << " ]" << "[ y: " << y << " ]" << endl;
	}
} Coordinates;

enum WarHead
{
	EXPLOSIVE,
	NUCLEAR
};

typedef struct Enemy
{
	Coordinates coordinates;
} Target;

struct Missile
{
	WarHead payload;
	Coordinates coordinates;
	Target target;

	bool armed;

	void arm()
	{
		if (armed)
			armed = false;
		else
			armed = true;
	}

	void update()
	{
		coordinates.x += 1;
		coordinates.y += 2;
	}
};

WarHead selectWarhead();

WarHead selectWarhead()
{
	cout << "Choose your warhead" << '\n';
	cout << endl;
	cout << "N = Nuclear" << endl;
	cout << "E = Explosive" << endl;
	cout << endl;

	char input = cin.get();

	WarHead selected = WarHead::EXPLOSIVE;

	if (input == 'n')
	{
		selected = WarHead::NUCLEAR;
		cout << "You have selected Nuclear" << endl;
		cout << endl;
	}
	else if (input == 'e')
	{
		cout << "You have selected Explosive" << endl;
		cout << endl;
	}
	return selected;
}


int main()
{
	
	// Create a new Enemy
	Enemy *e = new Enemy();

	cout << "Enter your coordinates" << endl;
	
	cout << endl;

	// Set Enemy Position / Target
	e->coordinates.x = 2;
	e->coordinates.y = 2;

	// Create a new Missile
	Missile *m = new Missile();

	// Set Missile Payload
	m->payload = selectWarhead();

	// Set Missile Target by dereferencing Enemy pointer
	m->target = *e;

	// Set Initial Position
	cout << "Where are you shooting?" << endl;

	cout << "X" << endl;
	cin >> m->coordinates.x;

	cout << "Y" << endl;
	cin >> m->coordinates.y;
	

	// Print Position
	cout << "Print Missile Position" << endl;
	m->coordinates.print();

	// Update Position
	m->update();

	// Print Missile Position
	cout << "Print Missile Position after an Update" << endl;
	m->coordinates.print();


	// Print Missile target
	cout << "Print Missile Target Position" << endl;
	m->target.coordinates.print();

	cin.get();
}