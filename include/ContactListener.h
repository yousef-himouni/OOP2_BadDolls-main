#include "GameObject.h"
#include "CollisionHandling.h"

class ContactListener : public b2ContactListener
{


public:

	// Called when two fixtures begin to touch
	virtual void BeginContact(b2Contact* contact) override;
};




