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

int main()
{
	// Create a new Enemy
	Enemy *e = new Enemy();

	// Set Enemy Position / Target
	e->coordinates.x = 2;
	e->coordinates.y = 2;

	// Print Enemy Position
	cout << "Print Enemy Position" << endl;
	e->coordinates.print();

	// Create a new Missile
	Missile *m = new Missile();

	// Set Missile Payload
	m->payload = WarHead::EXPLOSIVE;

	// Set Missile Target by dereferencing Enemy pointer
	m->target = *e;

	// Set Initial Position
	m->coordinates.x = 0;
	m->coordinates.y = 0;

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