class Bar
{
  public:
    explicit Bar();
    virtual ~Bar();

    virtual void Update();
    virtual void SetSomething(const int s);
    virtual int GetSomething() const;

  private:
    int a_;
    int b_;
};
