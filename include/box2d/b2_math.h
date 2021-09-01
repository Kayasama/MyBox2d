/*
 数学库
*/

#ifndef B2_MATH_H
#define B2_MATH_H

#include <math.h>

#include "b2_api.h"
#include "b2_settings.h"

#define b2_eplison 0

/// This function is used to ensure that a floating point number is not a NaN or infinity.
inline bool b2IsValid(float x)
{
    return isfinite(x);
}

#define b2Sqrt(x) sqrtf(x)
#define b2Atan2(y, x) atan2f(y,x)


/// A 2D column vector.
struct B2_API b2Vec2
{

    b2Vec2() {}

    /// Construct using coordinates.
    b2Vec2(float xIn, float yIn) : x(xIn), y(yIn) {}

    /// Set this vector to all zeros.
    void SetZero() { x = 0.0f; y = 0.0f; }

    /// Set this vector to some specified coordinates.
    // 指定坐标系
    void Set(float x_, float y_) { x = x_; y = y_; }

    /// 负向量
    b2Vec2 operator -() const { b2Vec2 v; v.Set(-x, -y); return v; }

    /// 读取索引元素
    float operator () (int32 i) const{
        return (&x)[i];
    }

    /// Write to an indexed element.
    float& operator () (int32 i)
    {
        return (&x)[i];
    }

    /// Add vector
    b2Vec2& operator += (const b2Vec2& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    /// MyAdd vector，应用引用即可实现临时对象的相加
    b2Vec2 operator + (const b2Vec2& v)//const对象与调用操作符的对象要区别开
    {
        // 两个以上连加要创建临时对象
        b2Vec2 tempVec2 = *this;
        tempVec2 += v;
        return tempVec2;
    }

    /// Sub vector
    void operator -= (const b2Vec2& v)
    {
        x -= v.x;
        y -= v.y;
    }

    /// Times a constant
    void operator *= (float a)
    {
        x *= a;
        y *= a;
    }

    /// get the length of vector
    float Length() const
    {
        return b2Sqrt(x*x + y*y);
    }

    /// get the length squared 
    float LengthSquared() const 
    {
        return x * x + y*y;
    }

    /// get the vector normalized
    float Normalize()
    {
        float length = Length();
        if(length < b2_eplison)
        {
            return 0.0f;
        }
        float invLength = 1.0/length;
        x *= invLength;
        y *= invLength;

        return length;
    }

    /// 判断向量值是否有效
    bool IsValid() const
    {
        return b2IsValid(x) && b2IsValid(y);
    }

    b2Vec2 skew() const
    {
        return b2Vec2(-y, x);
    }

    float x, y;
};

/// A 2D column vector with 3 elements.
struct B2_API b2Vec3
{
    b2Vec3() {}
    b2Vec3(float xIn, float yIn, float zIn) : x(xIn), y(yIn), z(zIn) {}

    void SetZero() { x = 0.0f; y = 0.0f; z = 0.0f; }

    void Set(float x_, float y_, float z_) { x = x_; y = y_; z = z_; }

    // Negative vector，可能要重用原来的向量，不能修改
    b2Vec3 operator-() const
    {
        b2Vec3 v;
        v.Set(-x, -y, -z);
        return v;
    }

    // +=符号将改变左值原值
    b2Vec3& operator += (const b2Vec3& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;// 为了两项以上的算术操作
    }

    // 同上
    b2Vec3& operator -=(const b2Vec3& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    // 同上
    b2Vec3& operator *= (float s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }
    float x, y, z;

};

struct B2_API b2Mat22
{
    b2Mat22() {}
    b2Mat22(const b2Vec2& c1, const b2Vec2& c2) : ex(c1), ey(c2) {}

    b2Mat22(float a11, float a21, float a12, float a22){
         ex.x = a11;
         ex.y = a21;
         ey.x = a12;
         ey.y = a22;
    }

    void Set(const b2Vec2& c1, const b2Vec2& c2)
    {
        ex = c1;
        ey = c2;
    }

    void SetIndentity()
    {
        ex.x = 1.0f;
        ex.y = 0.0f;
        ey.x = 0.0f;
        ey.y = 1.0f;
    }

    void SetZero()
    {
        ex.x = ex.y = ey.x = ey.y = 0;
    }

    // Inverse matrix
    b2Mat22 GetInverse() const
    {
        // if(this != nullptr)
        // {
        //     void* temp = malloc(sizeof(b2Mat22));
        //     temp = this;
        //     free(temp);
        // }
        return b2Mat22(ex.x, ey.x, ex.y, ey.y);
    }

    /// A * x = b; 求x
    b2Vec2 Solve(const b2Vec2& b)
    {
        float a11 = ex.x, a12 = ey.x, a21 = ex.y, a22 = ey.y;
        float det = a11 * a22 - a21 * a12;
        if(det != 0.0f)
        {
            det = 1.0 / det;
        }
        b2Vec2 x;
        x.x = det * (b.x * a22 - a12 * b.y);
        x.y = det * (a11 * b.y - b.x * a21);
        return x;
    }


    b2Vec2 ex, ey;
};

struct B2_API b2Rot
{
    b2Rot() {}
    explicit b2Rot(float angle)
    {
        s = sinf(angle);
        c = cosf(angle);
    }

    void SetRot(float angle)
    {
        s = sinf(angle);
        c = cosf(angle);
    }

    // 设置单位rot
    void SetIdentity()
    {
        s = 0.0f;
        c = 1.0f;
    }

    // 获取角度
    float GetAngle() const
    {
        return b2Atan2(s,c);
    }

    // 获取X轴
    b2Vec2 GetXAxis() const
    {
        return b2Vec2(c, s);
    }


    // 获取Y轴
    b2Vec2 GetYAxis() const
    {
        return b2Vec2(-s, c);
    }
    // sin, cosine
    float s, c;
};

struct B2_API b2Transform
{
    b2Transform() {}
    b2Transform(const b2Vec2& position, const b2Rot& rotation) : p(position), q(rotation) {}

    void SetIdentity()
    {
        p.SetZero();
        q.SetIdentity();
        
    }

    void Set(const b2Vec2& position, const float angle)
    {
        p = position;
        q.SetRot(angle);
    }

    b2Vec2 p;
    b2Rot q;
};



// template<typename __TP>// 作用范围有限，相当于类
// struct remove_tp{
// typedef __TP type;

// }
// #ifdef MY_OPINION

// typedef int* INT_PTR;
// void passArgm(INT_PTR beca)
// {
//     INT_PTR why = beca;
// }
// #endif

// 生产力是必然的部分（涉及设计），再回到支撑自己的“过程”中
// 画自己经验、想象中的事物？
// 绘画会沉浸进去，好像是因为一直使用右脑
// 现实中需要偶尔使用左脑
#endif