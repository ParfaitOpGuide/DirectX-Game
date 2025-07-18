#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(String name, AGameObject* owner): AComponent(name, Physics, owner)
{
    BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
    PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
    PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();

    Vector3D scale = this->getOwner()->getLocalScale();
    Transform transform;
    transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());
    BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2));
    this->rigidBody = physicsWorld->createRigidBody(transform);
    this->rigidBody->addCollider(boxShape, transform);
    this->rigidBody->updateMassPropertiesFromColliders();
    this->rigidBody->setMass(this->mass);
    this->rigidBody->setType(BodyType::DYNAMIC);

    transform = this->rigidBody->getTransform();
    float matrix[16];
    transform.getOpenGLMatrix(matrix);

    this->getOwner()->setLocalMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
    AComponent::~AComponent();
    BaseComponentSystem::getInstance()->getPhysicsSystem()->unregisterComponent(this);
}

void PhysicsComponent::perform(float deltaTime)
{
    const Transform transform = this->rigidBody->getTransform();
    float matrix[16];
    transform.getOpenGLMatrix(matrix);

    this->getOwner()->setLocalMatrix(matrix);
}

RigidBody* PhysicsComponent::getRigidBody()
{
    return this->rigidBody;
}
