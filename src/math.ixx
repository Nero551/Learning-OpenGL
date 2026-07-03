export module Math;

export struct Vector3 {
  float x, y, z;
};

export struct Util {
  static int Add(int a, int b) { return a + b; }
};


export namespace  MathUtils {
 int Add(int a, int b) { return a + b; }
}