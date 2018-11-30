#include <game/components/PhysicsComponent.h>
#include <engine/DebugPrint.h>
#include <engine/physics/World.h>

PhysicsComponent::PhysicsComponent(std::string _gameObjectName, Vec2f _originPosition, Vec2_ui32 _originSize, b2BodyType _bodyType, bool _fixedRotation) 
{
    gameObjectName = _gameObjectName;
    originPosition = _originPosition;
    originSize = _originSize;
    bodyType = _bodyType;
    fixedRotation = _fixedRotation;

    initBody();
}

PhysicsComponent::~PhysicsComponent()
{
    ANRI_DE debugPrint("PhysicsComponent destructor fired.");

    if(body && world) 
    {
        ANRI_DE debugPrint("[Box2D]: destroying body %s", body->GetUserData());
        world->DestroyBody(body);
    }
}

void PhysicsComponent::update() 
{

}

void PhysicsComponent::initBody() 
{
    ANRI_DE debugPrint("[Box2D] Initializing body for %s", gameObjectName.c_str());

    b2BodyDef myBodyDef;
    myBodyDef.type = bodyType; 
    myBodyDef.position.Set(originPosition.x + (originSize.x / 2.f), originPosition.y + (originSize.y / 2.f)); 
    myBodyDef.angle = 0;
    myBodyDef.gravityScale = 1.0;
    myBodyDef.fixedRotation = fixedRotation;

    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(originSize.x / 2.f, originSize.y / 2.f);      

    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &polygonShape; //this is a pointer to the shape above
    myFixtureDef.density = 1.f;
    myFixtureDef.friction = 0.8f;
    
    body = world->CreateBody(&myBodyDef);
    char* ud = new char[10];
    ud = "HABA BABA";
    body->SetUserData(ud);
    body->CreateFixture(&myFixtureDef); //add a fixture to the body
}

void PhysicsComponent::setVelocity(Vec2f& velocity)
{

}

void PhysicsComponent::applyForce(Vec2f& force, float deltaTime) 
{
    b2Vec2 forceVec(force.x * body->GetMass() / deltaTime, force.y * body->GetMass() / deltaTime);

    body->ApplyForceToCenter(forceVec, true);
}

void PhysicsComponent::setLinearVelocity(Vec2f velocity)
{
    //debugPrint("set linear");
    b2Vec2 vel(velocity.x, velocity.y);
    body->SetLinearVelocity(vel);
}

b2Vec2* PhysicsComponent::getBodyVertices()
{
    b2Vec2 *verts = nullptr;

    if(body != nullptr)
    {
        b2Fixture *fixture = body->GetFixtureList();
        
        if(fixture != nullptr)
        {
            b2PolygonShape *poly = (b2PolygonShape*) fixture->GetShape();
            verts = (b2Vec2*) malloc((size_t) POLYGON_VERTICES_COUNT * sizeof(b2Vec2));

            for(int i = 0; i < POLYGON_VERTICES_COUNT; i++)
            {
                verts[i] = body->GetWorldPoint(poly->m_vertices[i]);
            }
        }
    }

    return verts;
}

void PhysicsComponent::applyLinearImpulse(Vec2f impulse)
{
    debugPrint("APPLY LINEAR! [%.5f, %.5f]", impulse.x, impulse.y);
    b2Vec2 b2imp(impulse.x, impulse.y * body->GetMass());

    body->ApplyLinearImpulseToCenter(b2imp, true);
}

float PhysicsComponent::getRotationAngleDegrees()
{
    return body->GetAngle() * (180.0 / M_PI);
}

Vec2_ui32 PhysicsComponent::getPosition()
{
    Vec2_ui32 pos{body->GetPosition().x, body->GetPosition().y};
    
    return pos;
}

Vec2f PhysicsComponent::getVelocity() 
{
    Vec2f vel{body->GetLinearVelocity().x, body->GetLinearVelocity().y};

    return vel;
}

void PhysicsComponent::setBodyType(b2BodyType _bodyType) 
{
    bodyType = _bodyType;
    hasBodyType = true;
}

bool PhysicsComponent::isBodyTypeSet()
{
    return hasBodyType;
}

void PhysicsComponent::setTransform(Vec2f _transform, float _angle) 
{
    b2Vec2 b2t(body->GetPosition().x + _transform.x, body->GetPosition().y + _transform.y);

    body->SetTransform(b2t, _angle);
}