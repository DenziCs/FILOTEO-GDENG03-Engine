#include"PhysicsComponent.h"
#include"SystemManager.h"
#include"PhysicsSystem.h"
#include"AGameObject.h"
#include"Vector3D.h"
#include<iostream>

PhysicsComponent::PhysicsComponent(std::string name, AGameObject* owner) : AComponent::AComponent(name, PHYSICS, owner) {
	PhysicsSystem* physicsSystem = SystemManager::getInstance()->getPhysicsSystem();
	physicsSystem->registerComponent(this);
	std::cout << this->getComponentName() << " registered." << std::endl;

	reactphysics3d::PhysicsCommon* physicsCommon = physicsSystem->getPhysicsCommon();
	reactphysics3d::PhysicsWorld* physicsWorld = physicsSystem->getPhysicsWorld();
	
	Vector3D position = this->getOwner()->getLocalPosition();
	Vector3D rotation = this->getOwner()->getLocalRotation();
	Vector3D scale = this->getOwner()->getLocalScale();

	reactphysics3d::Transform transform;
	transform.setPosition(Vector3(position.x, position.y, position.z));
	transform.setOrientation(Quaternion::fromEulerAngles(rotation.x, rotation.y, rotation.z));

	reactphysics3d::BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.x / 2.f, scale.y / 2.f, scale.z / 2.f));
	mRigidBody = physicsWorld->createRigidBody(transform);

	mRigidBody->addCollider(boxShape, transform);
	mRigidBody->updateMassPropertiesFromColliders();
	mRigidBody->setMass(mMass);
	mRigidBody->setType(reactphysics3d::BodyType::DYNAMIC);

	transform = mRigidBody->getTransform();

	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->updateLocalMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent() {
	SystemManager::getInstance()->getPhysicsSystem()->unregisterComponent(this);
	AComponent::~AComponent();
}

void PhysicsComponent::perform(float delta_time) {
	const Transform transform = mRigidBody->getTransform();
	float physicsMatrix[16];
	transform.getOpenGLMatrix(physicsMatrix);

	this->getOwner()->updateLocalMatrix(physicsMatrix);
}

RigidBody* PhysicsComponent::getRigidBody() {
	return mRigidBody;
}

void PhysicsComponent::setMass(float object_mass) {
	mMass = object_mass;
}

void PhysicsComponent::setRigidBodyType(BodyType rigid_body_type) {
	mRigidBody->setType(rigid_body_type);
}

void PhysicsComponent::enableGravity(bool is_affected_by_gravity) {
	mRigidBody->enableGravity(is_affected_by_gravity);
}