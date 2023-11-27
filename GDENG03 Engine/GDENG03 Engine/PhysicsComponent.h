#pragma once
#include"AComponent.h"
#include"Vector3D.h"
#include<reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent : public AComponent
{
public:
	PhysicsComponent(std::string name);
	~PhysicsComponent();

	virtual void attachOwner(AGameObject* owner) override;
	void perform(float delta_time) override;

	RigidBody* getRigidBody();

	void reset(Vector3D position, Vector3D rotation);
	void setMass(float object_mass);

private:
	float mMass = 1000.f;
	RigidBody* mRigidBody;
};