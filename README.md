## Text Area Management Library

### **Purpose**
This library is designed for automatic stacking and rendering of strings in an IMGUI environment. It prevents overlapping of text strings at the same planar coordinates, which can cause display issues. By default, it stacks text upwards automatically, adjusting positions based on the size of the text. For detailed implementation, refer to the reference code provided.

中文说明请戳[这里](README.zh-CN.md)

## **How to Use**

1. **Clone the Project**
   - Clone the repository to your local machine.

2. **Integrate the Library**
   - Move the `YC.h` file into your project directory and include it in your main source file.

---

## **Example Usage**

```cpp
#include "YC.h" // Replace with the actual library header file

int main() {
    std::vector<Point> storage; // Define a collection to store points

    // Dimensions of the text area
    float textWidth = 10.0f;  
    float textHeight = 5.0f;  

    // Example: Adding multiple text areas
    addToEnd(storage, 5.5f, 2.0f, 0, textWidth, textHeight, true);
    addToEnd(storage, 3.9f, 2.1f, 0, textWidth, textHeight, true);
    addToEnd(storage, 0.0f, 2.2f, 0, textWidth, textHeight, true);
    addToEnd(storage, 65.5f, 2.2f, 0, textWidth, textHeight, true);
    addToEnd(storage, 1.5f, 2.0f, 0, textWidth, textHeight, true);
    addToEnd(storage, 1.9f, 2.0f, 0, textWidth, textHeight, true);
    addToEnd(storage, 1.5f, 2.2f, 0, textWidth, textHeight, true);
    addToEnd(storage, 5.5f, 2.2f, 0, textWidth, textHeight, true);

    // Print the coordinates of the points in storage
    for (const auto& point : storage) {
        std::cout << "x: " << point.x << ", y: " << point.y << std::endl; // Output the coordinates of each point
    }

    return 0;
}
```

---

## **Code Explanation**

### **Key Functional Functions**

1. **`readLastPoint` Function**
   - **Description**: Reads the coordinates of the last point from the `storage` vector.
   - **Usage**: Writes the X and Y coordinates of the last point into specified variables.

2. **`matchSpace2D` Function**
   - **Description**: Detects overlapping in a 2D space.
   - **Usage**: Returns whether the new area overlaps with any existing area.

3. **`matchSpace3D` Function**
   - **Description**: Detects overlapping in a 3D space.
   - **Usage**: Returns whether the new area overlaps with any existing area in a 3D context.

4. **`adjustPosition` Function**
   - **Description**: Adjusts the Y-coordinate to prevent overlapping.
   - **Usage**: Moves the Y-coordinate to ensure the new text area does not overlap with existing areas.

5. **`addToEnd2D` Function**
   - **Description**: Adds a point to the 2D space.
   - **Usage**: If overlapping is detected, it recursively checks and adjusts the coordinates to ensure no overlap.

6. **`addToEnd3D` Function**
   - **Description**: Adds a point to the 3D space.
   - **Usage**: Similar to `addToEnd2D`, but operates in a 3D environment.

7. **`addToEnd` Function**
   - **Description**: Unified interface that calls the appropriate adding function based on the context.
   - **Usage**: Simplifies the process of adding points in both 2D and 3D spaces.

### **Overall Functionality**

- **Preventing Text Overlap**: The library ensures that text areas do not overlap, providing better text placement management.
- **Support for 2D and 3D Spaces**: Whether it's a simple 2D layout or a more complex 3D environment, the library effectively manages text areas.

---

## **Usage Methods**

### **Usage in a Loop**

```cpp
#include "your_library.h" // Replace with the actual library header file

std::vector<Point> storage;
while (true) {
    storage.clear(); // Clear the storage
    for (int i = 0; i < count; i++) {
        // Retrieve data, e.g., x, y
        float x, y;
        // ...code to retrieve x and y...
        addToEnd(storage, x, y, 0, textWidth, textHeight, true);
        
        // Get the coordinates of the last added point
        float x2, y2;
        readLastPoint(storage, x2, y2);
        std::cout << "x: " << x2 << ", y: " << y2 << std::endl;
    }
}
```

### **Non-Loop Usage**

```cpp
#include "YC.h" // Replace with the actual library header file

std::vector<Point> storage;

float textWidth = 10.0f;  // Width of the text
float textHeight = 5.0f;  // Height of the text

// Example of adding multiple points
addToEnd(storage, 5.5f, 2.0f, 0, textWidth, textHeight, true);
addToEnd(storage, 3.9f, 2.1f, 0, textWidth, textHeight, true);
// ...other texts...

// Print the coordinates of the points in storage
for (const auto& point : storage) {
    std::cout << "x: " << point.x << ", y: " << point.y << std::endl; // Output the coordinates of each point
}
```

---

## **Important Considerations**

1. **Obtaining Text Dimensions**
   - **Recommendation**: Use functions provided by the graphics library (such as ImGui's `ImGui::CalcTextSize`) to dynamically obtain the size of the text to ensure the validi
