#ifndef B2_WORLD_H
#define B2_WORLD_H

// world类管理所有物理实体、动态模拟
// 和异步查询。world也包含高效率的内存管理工具

#include "b2_api.h"
#include "b2_math.h"

struct b2AABB;
struct b2BodyDef;
struct b2Color;
struct b2JointDef;
class b2Body;
class b2Draw;
class b2Fixture;
class b2Joint;

// 导出动态库，导出符号为B2_API，B2world是不对外暴露的
// 被B2_API修饰的world类可以外部调用，里面所有的函数、数据
// 都可以被外部调用。
class B2_API b2World
{
public:
    b2World(const b2Vec2& gravity);
    ~b2World();

    void SetDebugDraw(b2Draw* debugDraw);

    /// @warning This function is locked during callbacks.
    b2Body* CreateBody(const b2BodyDef* def);

    /// @warning This automatically deletes all associated shapes and joints.
    /// @warning This function is locked during callbacks.
    void DestroyBody(b2Body* body);


    /// @warning This function is locked during callbacks.
    b2Joint* CreateJoint(const b2JointDef* def);


    /// @warning This function is locked during callbacks.
    void DestroyJoint(b2Joint* joint);

    // Take a time step. This performs collision detection, integration,
    // and constraint solution.
    void Step(float timeStep, int32 velocityIterations, int32 positionInterations);

    // Manually clear the force buffer on all bodies.
    // The purpose of this function is to support sub-stepping.
    // Sub-stepping is used to maintain a fixed sized time step under a variable frame-rate.
    void ClearForces();

    // Call this to draw shapes and other debug draw data. This is intentionally non-const.
    void DebugDraw();

    // Query the world for all fixtures that potentially overlap the
	// provided AABB.
    /// @param callback a user implemented callback class.
	/// @param aabb the query box.
    void QueryAABB(b2QueryCallback* callback, const b2AABB& aabb) const;

    /// @param callback a user implemented callback class.
	/// @param point1 the ray starting point
	/// @param point2 the ray ending point
    void RayCast(b2RayCastCallback* callback, const b2Vec2& point1, const b2Vec2& point2) const;

    /// @return the head of the world body list.
    b2Body* GetBodyList();
    const b2Body* GetBodyList() const;

    /// @return the head of the world joint list.
    b2Joint* GetJointList();
    const b2Joint* GetJointList() const;

    /// @return the head of the world contact list.
    /// @warning contacts are created and destroyed in the middle of a time step.
    /// Use b2ContactListener to avoid missing contacts.
    b2Contact* GetContactList();


    /// Set flag to control automatic clearing of forces after each time step.
    void SetAutoClearForces(bool flag);

    /// Get flag
    bool GetAutoClearForces() const;

    /// Get the contact manager for testing.
    const b2ContactManager& GetContactManager() const;


    /// Dump the world into the log file.
    /// @warning this should be called outside of a time step.
    void Dump();
private:
    friend class b2Body;
    friend class b2Fixture;
    friend class b2ContactManager;
    friend class b2Controller;

    

// pointer object
    b2Body* m_bodyList;
    b2Joint* m_jointList;

    
    bool m_allowSleep;


    b2Draw* m_debugDraw;


    // compute the time step ratio to
    // support a variable time step.
    float m_inv_dt0;

    bool m_newContacts;
    bool m_locked;
    bool m_clearForces;

    // These are for debugging the solver.
    bool m_warmStarting;
    bool m_continuousPhysics;
    bool m_subStepping;

    bool m_stepComplete;



};


#endif