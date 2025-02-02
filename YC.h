//
// Created by 洋葱落日 on 2024/8/21.
//

#include <iostream>
#include <vector>
#include <cmath>

// 定义 Point 结构体，用于存储点的坐标
struct Point {
    float x; // 点的 X 坐标
    float y; // 点的 Y 坐标
    float m; // 三维坐标或其他用途，当前代码中主要为0
};

// 函数：读取最后一个点的坐标
void readLastPoint(const std::vector<Point>& points, float& a, float& b) {
    if (!points.empty()) {
        const Point& lastPoint = points.back(); // 获取最后一个点
        a = lastPoint.x; // 将最后一个点的 X 坐标赋值给 a
        b = lastPoint.y; // 将最后一个点的 Y 坐标赋值给 b
    }
}

// 函数：检查二维空间中的重叠
bool matchSpace2d(const std::vector<Point>& points, float x, float y, float width, float height) {
    for (const auto& point : points) {
        // 检查当前点与集合中每个点的重叠情况
        if (std::abs(point.x - x) < width && std::abs(point.y - y) < height) {
            return true; // 若有重叠，返回 true
        }
    }
    return false; // 否则返回 false
}

// 函数：检查三维空间中的重叠
bool matchSpace3d(const std::vector<Point>& points, float x, float y, float m, float width, float height) {
    for (const auto& point : points) {
        // 检查当前点与集合中每个点的重叠情况 
        if (std::abs(point.x - x) < width && std::abs(point.y - y) < height && std::abs(point.m - m) <= 5) {
            return true; // 若有重叠，返回 true
        }
    }
    return false; // 否则返回 false
}

// 函数：调整 Y 坐标位置
void adjustPosition(float& x, float& y, float offset) {
    y -= offset; // 将 Y 坐标偏移一定的值以避免重叠
}

// 函数：在二维空间中添加点
void addToEnd2D(std::vector<Point>& points, float& x, float& y, float width, float height) {
    if (matchSpace2d(points, x, y, width, height)) {
        for (const auto& point : points) {
            // 检查与当前点的重叠情况
            if (std::abs(point.x - x) < width && std::abs(point.y - y) < height) {
                // 将新的 x 坐标调整为与重叠点相同
                x = point.x; 
                adjustPosition(x, y, 5); // 向下移动 y 坐标
                break; // 退出循环以重新检查新位置的重叠情况
            }
        }
        addToEnd2D(points, x, y, width, height); // 递归查找新的位置
        return; // 退出函数
    }
    points.push_back({x, y, 0}); // 添加新的点，m值设置为0
}

// 函数：在三维空间中添加点
void addToEnd3D(std::vector<Point>& points, float& x, float& y, float& m, float width, float height) {
    if (matchSpace3d(points, x, y, m, width, height)) {
        for (const auto& point : points) {
            if (std::abs(point.x - x) < width && std::abs(point.y - y) < height && std::abs(point.m - m) <= 5) {
                // 调整 x 坐标和 y 坐标
                x = point.x; 
                adjustPosition(x, y, 5); // 向下移动 y 坐标
                break; // 退出循环以重新检查新位置的重叠情况
            }
        }
        addToEnd3D(points, x, y, m, width, height); // 递归查找新的位置
        return; // 退出函数
    }
    points.push_back({x, y, m}); // 添加新的点
}

// 函数：根据类型调用不同的添加函数
void addToEnd(std::vector<Point>& points, float x, float y, float m, float textWidth, float textHeight, bool t) {
    if (t) {
        addToEnd2D(points, x, y, textWidth, textHeight); // 添加二维点
    } else {
        addToEnd3D(points, x, y, m, textWidth, textHeight); // 添加三维点
    }
}


/****** 示例用法 ******/
/*
int main() {
    std::vector<Point> 寄存空间; // 定义存储点的集合

    // 文本区域的宽度和高度
    float textWidth = 10.0;  
    float textHeight = 5.0;  

    // 示例用法，添加多个文本区域
    addToEnd(寄存空间, 5.5, 2.0, 0, textWidth, textHeight, true);
    addToEnd(寄存空间, 3.9, 2.1, 0, textWidth, textHeight, true);
    addToEnd(寄存空间, 0, 2.2, 0, textWidth, textHeight, true);
    addToEnd(寄存空间, 65.5, 2.2, 0, textWidth, textHeight, true);
    addToEnd(寄存空间, 1.5, 2.0, 0, textWidth, textHeight, true);
    addToEnd(寄存空间, 1.9, 2.0, 0, textWidth, textHeight, true);
    addToEnd(寄存空间, 1.5, 2.2, 0, textWidth, textHeight, true);
    addToEnd(寄存空间, 5.5, 2.2, 0, textWidth, textHeight, true);

    // 打印寄存空间中的点
    for (const auto& point : 寄存空间) {
        std::cout << "x: " << point.x << ", y: " << point.y << std::endl; // 输出每个点的坐标
    }

    return 0;
}
*/

/*
### 代码说明：

1. **`readLastPoint` 函数**：
   - 从 `寄存空间` 中读取最后一个点的坐标 
   - 将最后一个点的 X 和 Y 坐标写入指定的变量 

2. **`matchSpace2d` 函数**：
   - 检测二维区域的重叠 
   - 返回是否与现有区域重叠 

3. **`matchSpace3d` 函数**：
   - 检测三维区域的重叠 
   - 返回是否与现有区域重叠 

4. **`adjustPosition` 函数**：
   - 调整 Y 坐标以避免重叠 

5. **`addToEnd2D` 函数**：
   - 在二维空间中添加点 
   - 如果重叠，调用递归检查并调整坐标 

6. **`addToEnd3D` 函数**：
   - 在三维空间中添加点 
   - 如果重叠，调用递归检查并调整坐标 

7. **`addToEnd` 函数**：
   - 统一接口，根据不同的条件调用添加函数 

### 整体作用：
- 确保添加的文本区域在二维或三维空间中不重叠 
- 通过有效的匹配与调整，为用户提供更好的文本位置管理 

### 使用方法:
- **循环中使用**：

```cpp
   std::vector<Point> 寄存空间;
   while (1)
   {
       // 清空寄存空间
       寄存空间.clear();
       for (int i = 0; i < count; i++)
       {
           // 获取数据例如 x, y
           // ...代码...
           addToEnd(寄存空间, x, y, 0, textWidth, textHeight, true);
        
           // 获取最后添加的点坐标
           readLastPoint(寄存空间, x2, y2);
           std::cout << "x: " << x2 << ", y: " << y2 << std::endl;
       }    
   }
```

- **非循环使用**：

```cpp
   std::vector<Point> 寄存空间;

   float textWidth = 10.0;  // 文本的宽度
   float textHeight = 5.0;  // 文本的高度

   // 示范添加多个点
   addToEnd(寄存空间, 5.5, 2.0, 0, textWidth, textHeight, true);
   addToEnd(寄存空间, 3.9, 2.1, 0, textWidth, textHeight, true);
   // ...其他文本...
   // 打印寄存空间中的点
   for (const auto& point : 寄存空间) {
       std::cout << "x: " << point.x << ", y: " << point.y << std::endl; // 输出每个点的坐标
   }
```

### 注意事项：
1. **关于文本宽高的获取**：
   - 确保 `textWidth` 和 `textHeight` 是有效的文本大小 
   - 可以使用图形库获取文本尺寸（如 ImGui 提供的 `ImGui::CalcTextSize`
   
2. **数据有效性检查**：
   - 在调用 `addToEnd` 或者其他添加函数之前，确保传入的坐标数据（`x`, `y`, `m`）是有效的 例如，检查它们是否为数字（未初始化的情况下可能会有未定义行为） 

3. **重叠容忍度**：
   - 调整 `matchSpace2d` 和 `matchSpace3d` 函数中的重叠检测容忍度（例如，当前的宽度和高度使用绝对值比较） 不同的应用场景可能需要不同的重叠检测逻辑 

4. **Y坐标调整的灵活性**：
   - `adjustPosition` 函数当前的实现是简单的向下移动 `y` 坐标 可以考虑使 `offset` 更具动态性，以适应不同文本大小和间距的需求 

5. **三维空间的 m 坐标**：
   - 目前重叠检测中对 `m` 的处理相对简单（只考虑 ±5 的范围） 对于更复杂的三维空间应用，可能需要根据具体需求调整这一范围 

6. **递归性能**：
   - 在 `addToEnd2D` 和 `addToEnd3D` 函数中使用了递归 如果点的数量较多，可能导致栈溢出或性能问题 考虑使用循环代替递归以提高稳定性和效率 

7. **合理的文本区域大小**：
   - 确保定义的 `textWidth` 和 `textHeight` 大小符合实际文本内容的尺寸 可以使用图形库中的相关函数动态获取文本尺寸以增加灵活性 

8. **多线程安全**：
   - 如果代码中可能存在多线程使用 `寄存空间` 的情况，应考虑对数据结构的访问进行适当的同步保护，以避免数据竞争和不一致问题 

9. **清空寄存空间**：
   - 在使用 `寄存空间.clear()` 时，确保在所有对其的操作完成之后再进行清空，避免出现访问已释放内存的情况, 或者在循环中出现问题


10. **清空寄存空间**：
   - 在使用 `addToEnd` 时，确保你填写的 `t` 是可用的或是你选择的模式, true 为二维, false 为三维
*/