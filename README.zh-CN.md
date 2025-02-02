# 文本区域管理库
用于IMGUI字串自动叠加渲染，防止两串文字叠加在同一平面坐标上显示不清晰，默认为向上自动叠加，根据文字大小自动调整，具体请使用参考代码进行标注。

Please click [here](README.md) for the English description.

## How to use
1.克隆此项目
2.将`YC.h`文件移动到你的项目，在主文件中导入这个头文件

## 示例用法

```cpp
#include "YC.h" // 请替换为实际的库头文件

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
```

## 代码说明

### 主要功能函数

1. **`readLastPoint` 函数**
   - **描述**: 从 `寄存空间` 中读取最后一个点的坐标。
   - **用途**: 将最后一个点的 X 和 Y 坐标写入指定的变量。

2. **`matchSpace2d` 函数**
   - **描述**: 检测二维区域的重叠。
   - **用途**: 返回是否与现有区域重叠。

3. **`matchSpace3d` 函数**
   - **描述**: 检测三维区域的重叠。
   - **用途**: 返回是否与现有区域重叠。

4. **`adjustPosition` 函数**
   - **描述**: 调整 Y 坐标以避免重叠。
   - **用途**: 通过移动 Y 坐标来防止新添加的文本区域与现有区域重叠。

5. **`addToEnd2D` 函数**
   - **描述**: 在二维空间中添加点。
   - **用途**: 如果检测到重叠，调用递归检查并调整坐标以确保不重叠。

6. **`addToEnd3D` 函数**
   - **描述**: 在三维空间中添加点。
   - **用途**: 类似于 `addToEnd2D`，但适用于三维空间。

7. **`addToEnd` 函数**
   - **描述**: 统一接口，根据不同的条件调用相应的添加函数。
   - **用途**: 简化二维和三维空间点的添加过程。

### 整体作用

- **确保文本区域不重叠**: 通过有效的匹配与调整，为用户提供更好的文本位置管理。
- **支持二维和三维空间**: 无论是简单的 2D 布局还是更复杂 3D 环境，都能有效管理文本区域。

## 使用方法

### 循环中使用

```cpp
#include "your_library.h" // 请替换为实际的库头文件

std::vector<Point> 寄存空间;
while (true) {
    寄存空间.clear(); // 清空寄存空间
    for (int i = 0; i < count; i++) {
        // 获取数据，例如 x, y
        float x, y;
        // ...代码...
        addToEnd(寄存空间, x, y, 0, textWidth, textHeight, true);
        
        // 获取最后添加的点坐标
        float x2, y2;
        readLastPoint(寄存空间, x2, y2);
        std::cout << "x: " << x2 << ", y: " << y2 << std::endl;
    }
}
```

### 非循环使用

```cpp
#include "your_library.h" // 请替换为实际的库头文件

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

## 注意事项

1. **文本宽高的获取**
   - **建议**: 使用图形库提供的函数（如 ImGui 的 `ImGui::CalcTextSize`）动态获取文本尺寸，以确保 `textWidth` 和 `textHeight` 的有效性。

2. **数据有效性检查**
   - **建议**: 在调用 `addToEnd` 或其他添加函数之前，确保传入的坐标数据（`x`, `y`, `m`）是有效的。例如，检查它们是否为数字，以避免未定义行为。

3. **重叠容忍度**
   - **建议**: 根据应用场景调整 `matchSpace2
