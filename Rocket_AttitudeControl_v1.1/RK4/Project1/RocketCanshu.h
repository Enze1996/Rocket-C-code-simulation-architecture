
#pragma once
//使用了 #pragma once 来避免头文件被多次包含。这样可以确保头文件只会被包含一次，避免重复定义。


//


struct RocketCanshu {


     //const 修饰符表示该变量是常量，即在程序运行过程中，g 的值不能被修改

 const double m = 5000.0;  // 火箭质量，单位：kg

 const double g = 9.81;    // 重力加速度，单位：m/s^2

 const double I_x = 1000.0; // 火箭的惯性矩，单位：kg·m^2

 const double I_y = 1000.0; // 火箭的惯性矩，单位：kg·m^2

 const double I_z = 1000.0; // 火箭的惯性矩，单位：kg·m^2
};

// 声明全局实例，其他文件都可以访问 -- 2024-11-27
// 如果不声明 extern ，则 RocketCanshu  不能在diff_fun.cpp 和main1.cpp中被同时调用
//在 main.cpp 和其他文件中都创建了 RocketCanshu 类型的实例 RockCanshu，并且在每个文件中都包含了 RocketCanshu.h，
// 这可能导致 链接错误 或 重复定义 错误。




extern RocketCanshu RockCanshu;