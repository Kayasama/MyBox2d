#include ".\include\box2d\b2_math.h"
#include <stdio.h>
int main()
{
    b2Mat22 myMat(1.0, 1.0, 3.0, 5.0);
    
    b2Mat22 anoMat = myMat.GetInverse();
    float x = 1, y = 2.0, z = 3.0;
    b2Vec3 myVec = b2Vec3(x,y,z);
    b2Vec3 negVec = -(myVec);
    
    b2Vec2 myVec2 = b2Vec2(1,2);
    b2Vec2 myVec2_1 = b2Vec2(1,2);
    /*！
      @note 向量的连续算术操作

      @attention 分析连续操作需要的子步骤
    */
    myVec2 += myVec2_1 += myVec2_1 += myVec2_1;
    // myVec += negVec;

    // printf("%f, %f \n %f, %f",
    //              anoMat.ex.x, anoMat.ey.x, anoMat.ex.y, anoMat.ey.y);
    // printf("%f, %f, %f", negVec.x, negVec.y, negVec.z);
    printf("\n %f, %f", myVec2.x, myVec2.y);
    printf("\n %f, %f", myVec2_1.x, myVec2_1.y);

#pragma region 自由落体运动模拟
    // double g = 9.8;
    // double h = 10;
    // double v = 0;
    // double t = 0, dt = 0.000001;// 百万分之一秒 = 1微秒
    // while(h>0)
    // {
    //     h = h - v*dt;
    //     v = v + g*dt;
    //     t = t + dt;
    //     printf("h=%f, v=%f, t=%f\n", h, v, t);
        
    // }
#pragma endregion

    return 0;
}