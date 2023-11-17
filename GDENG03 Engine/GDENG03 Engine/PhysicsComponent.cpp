#include"PhysicsComponent.h"
#include"SystemManager.h"
#include"PhysicsSystem.h"
#include"AGameObject.h"
#include"Vector3D.h"

PhysicsComponent::PhysicsComponent(std::string name, AGameObject* owner) : AComponent::AComponent(name, PHYSICS, owner) {
	PhysicsSystem* physicsSystem = SystemManager::getInstance()->getPhysicsSystem();
	physicsSystem->registerComponent(this);
	reactphysics3d::PhysicsCommon* physicsCommon = physicsSystem->getPhysicsCommon();
	reactphysics3d::PhysicsWorld* physicsWorld = physicsSystem->getPhysicsWorld();

	Vector3D scale = this->getOwner()->getLocalScale();
	reactphysics3d::Transform transform; transform.setFromOpenGL(this->getOwner()->getPhysicsMatrix());
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
	float physics_matrix[16];
	transform.getOpenGLMatrix(physics_matrix);

	this->getOwner()->updateLocalMatrix(physics_matrix);
}

RigidBody* PhysicsComponent::getRigidBody() {
	return mRigidBody;
}