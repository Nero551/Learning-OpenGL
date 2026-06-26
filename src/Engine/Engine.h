class Engine {
public:
  bool Running;

public:
  double Time;

public:
  void Start();

public:
  void Process(double delta);

public:
  void Stop();
};